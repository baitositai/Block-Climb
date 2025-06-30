#include "../../../Application.h"
#include "../../../Manager/InputManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Utility/Collision.h"
#include "Level5.h"
#include "../Block/BlockBase.h"
#include "../Block/Block5.h"
#include "../PlayerBase.h"
#include "../BackGround.h"
#include "../Moon/Moon2.h"
#include "../Camera/Camera.h"
#include "../Side/SideBase.h"
#include "../Side/Side5.h"
#include "../Gimic/FireBall.h"

Level5::Level5(void)
{
	fireCnt_ = -1;
	moon_ = nullptr;
	fire_.clear();
}

Level5::~Level5(void)
{
}

void Level5::AddInit()
{	
	moon_ = new Moon2();
	moon_->Init(this);

	//�u���b�N�̓ǂݍ���
	block_ = new Block5();
	block_->Init(this);

	side_ = new Side5();
	side_->Init(this);

	//�΂̋ʂ̏�����
	for (auto fire : fire_)
	{
		fire->SetState(FireBall::STATE::NONE);
	}

	player_->SetParam(PlayerBase::MAX_MOVE_SPEED, PlayerBase::MAX_JUMP_POW * PLAYER_JUMP_POW);

}

void Level5::Update(void)
{
	//�q�b�g�X�g�b�v����
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}

	LevelManager::Update();
	moon_->Update();
	HitMoon();
	//�΂̋ʏ���
	FireBallUpdate();

}

void Level5::Draw(void)
{
	// �U��
	if (hitStopCnt_ > 0)
	{
		// �`���̃X�N���[����ݒ� �q�b�g�X�g�b�v���́A
		SetDrawScreen(tmpScreen_);
	}
	backGround_->Draw();
	block_->Draw();	
	moon_->Draw();
	player_->Draw();
	for (auto fire : fire_)
	{
		fire->Draw();
	}
	camera_->Draw();
	side_->Draw();
	DebagDraw();
	CameraShake();
}

void Level5::Release(void)
{
	for (auto fire : fire_)
	{
		fire->Release();
	}
	side_->Release();
	delete side_;

	block_->Release();
	delete block_;

	moon_->Release();
	delete moon_;
	
	LevelManager::Release();
}

void Level5::SetParam()
{	
	// �t�B�[���h�T�C�Y��ݒ�
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };

	// �n�ʃT�C�Y��ݒ�
	groundSize_ = { GROUND_WIDTH, GROUND_HEIGHT };

	// �X�e�[�W�T�C�Y��ݒ�
	stageSize_ = {
		groundSize_.x,
		fieldSize_.y + STAGE_GROUND_EXTRA_Y
	};

	float fieldY = static_cast<float>(fieldSize_.y);  // �t�B�[���h�̏c�T�C�Y�� float �ɕϊ����Ďg�p

	// �v���C���[�̏������W��ݒ�
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2 - PLAYER_OFFSET_X,
		BlockBase::BLOCK_SIZE_Y * (fieldY - PLAYER_OFFSET_BLOCK_Y) - PLAYER_PIXEL_ADJUST_Y
	};

	// �J�����̏������W��ݒ�
	firstCameraPos_ = {
		0,
		-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + CAMERA_OFFSET_BLOCK_Y)
	};

	// �S�[���̍��W��ݒ�
	goalPos_ = {
		Application::SCREEN_SIZE_X / 2 + GOAL_OFFSET_X,
		GOAL_POS_Y
	};

	// �`�撆�S�̍��W���v�Z���Đݒ�
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- stageSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2,
		0
	};

}

void Level5::HitMoon()
{
	auto& snd = SoundManager::GetInstance();
	//�v���C���[���̎擾
	Vector2 pPos = player_->GetPos().ToVector2();
	Vector2 pSize = player_->GetSize();			//�v���C���[��x���W�̔����𔼌a�Ƃ���
	int pRadius = pSize.x / 2;

	//�Ԃ����̎擾
	Vector2 rPos = moon_->GetPos(Moon::MOON_TYPE::CREATE).ToVector2();

	if (Collision::IsCollisionCircle(pPos, pRadius, rPos, Moon::RADIUS) && moon_->IsMoon(Moon::MOON_TYPE::CREATE) == false)
	{
		moon_->SetIsMoon(Moon::MOON_TYPE::CREATE, true);
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::CREATE_MOON_HIT));
		block_->ResetMino();
	}

	//�����̎擾
	Vector2 bPos = moon_->GetPos(Moon::MOON_TYPE::CHANGE).ToVector2();
	bool Hit = Collision::IsCollisionCircle(pPos, pRadius, bPos, Moon::RADIUS);
	bool isBlue = moon_->IsMoon(Moon::MOON_TYPE::CHANGE);

	if (Hit && !isBlue)
	{
 		moon_->SetIsMoon(Moon::MOON_TYPE::CHANGE, true);
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::CHANGE_MOON_HIT));
		block_->ChangeNextBlock();
	}
	else if (!Hit && isBlue)
	{
		moon_->SetIsMoon(Moon::MOON_TYPE::CHANGE, false);
	}
}

void Level5::FireBallUpdate()
{

	auto& snd = SoundManager::GetInstance();
	//�΂̋ʂ̐���
	CreateFireBall();

	//�΂̋ʂ̏���
	for (auto fire : fire_)
	{
		fire->Update();

		Vector2 fPos = fire->GetPos().ToVector2();
		Vector2 fSize = { FireBall::SIZE_X,
						  FireBall::SIZE_Y };

		//�v���C���[�Ƃ̏Փ˔���
		if (fire->GetState() == FireBall::STATE::FIRE &&
			Collision::IsCollisionBoxCircle(player_->GetPos().ToVector2(),
				player_->GetSize(),
				fire->GetPos().ToVector2(),
				FireBall::RADIUS))
		{
			fire->SetState(FireBall::STATE::BLAST);
			SetStopCnt(HIT_STOP_CNT);
			player_->SetIsDeath(true);
		}

		//�u���b�N�Ƃ̏Փ˔���
		if (fire->GetState() == FireBall::STATE::FIRE &&
			IsHitField(fPos))
		{
			fire->SetState(FireBall::STATE::BLAST);
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::FIRE_BALL_HIT));
		}
		else if (fire->GetState() == FireBall::STATE::FIRE &&
			IsHitMino(fPos, fSize))
		{
			fire->SetState(FireBall::STATE::BLAST);
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::FIRE_BALL_HIT));
		}

	}
}

void Level5::CreateFireBall()
{
	//��莞��
	int createSecond = 5 * SceneManager::DEFAULT_FPS;

	if (fireCnt_ % createSecond == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			FireBall* fire = GetValidFireBall();

			//�����̐���
			fire->Create(this, 3);
		}
	}

	//�J�E���g
	fireCnt_++;
}

FireBall* Level5::GetValidFireBall()
{
	FireBall* fire = new FireBall();
	fire_.push_back(fire);
	return fire;
}


Moon* Level5::GetMoonInstans()
{
	return moon_;
}
