#include "Level2.h"

#include "../../../Application.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Utility/Collision.h"

#include "../Block/BlockBase.h"
#include "../Block/Block2.h"
#include "../PlayerBase.h"
#include "../BackGround.h"
#include "../Moon/Moon2.h"
#include "../Camera/Camera.h"
#include "../Side/SideBase.h"
#include "../Side/Side2.h"

Level2::Level2(void)
{
	moon_ = nullptr;
}

Level2::~Level2(void)
{
}

void Level2::AddInit()
{	
	moon_ = new Moon2();
	moon_->Init(this);

	//�u���b�N�̓ǂݍ���
	block_ = new Block2();
	block_->Init(this);

	side_ = new Side2();
	side_->Init(this);

	player_->SetParam(PlayerBase::MAX_MOVE_SPEED, PlayerBase::MAX_JUMP_POW * PLAYER_JUMP_BUFF);

}

void Level2::Update(void)
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

}

void Level2::Draw(void)
{
	// �U��
	if (hitStopCnt_ > 0)
	{
		// �`���̃X�N���[����ݒ� �q�b�g�X�g�b�v���́A
		SetDrawScreen(tmpScreen_);
	}
	backGround_->Draw();
	block_->Draw();
	player_->Draw();
	camera_->Draw();
	moon_->Draw();
	side_->Draw();
	DebagDraw();
	CameraShake();
}

void Level2::Release(void)
{
	side_->Release();
	delete side_;

	block_->Release();
	delete block_;

	moon_->Release();
	delete moon_;

	LevelManager::Release();
}

void Level2::SetParam()
{	
	// �t�B�[���h�ƒn�ʂ̃T�C�Y��ݒ�
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };
	groundSize_ = { GROUND_WIDTH, GROUND_HEIGHT };

	// �X�e�[�W�T�C�Y��ݒ�
	stageSize_ = {
		groundSize_.x,
		fieldSize_.y + STAGE_EXTRA_HEIGHT
	};

	float fieldY = static_cast<float>(fieldSize_.y);  // �t�B�[���h�̏c�T�C�Y���v�Z�Ɏg������ float �ɕϊ�

	// �v���C���[�̏����ʒu��ݒ�
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2 - PLAYER_OFFSET_X,
		BlockBase::BLOCK_SIZE_Y * (fieldY - PLAYER_OFFSET_Y_BLOCK) - PLAYER_PIXEL_ADJUST_Y
	};

	// �J�����̏����ʒu��ݒ�
	firstCameraPos_ = {
		0,
		-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + CAMERA_OFFSET_BLOCK_Y)
	};

	// �S�[���̍��W��ݒ�
	goalPos_ = {
		Application::SCREEN_SIZE_X / 2 + GOAL_OFFSET_X,
		GOAL_POS_Y
	};

	// �`�撆�S�̈ʒu���v�Z���Đݒ�
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- stageSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2,
		0
	};

}

void Level2::HitMoon()
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
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::CREATE_MOON_HIT));
		moon_->SetIsMoon(Moon::MOON_TYPE::CREATE, true);
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

Moon* Level2::GetMoonInstans()
{
	return moon_;
}
