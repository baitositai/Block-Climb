#include "../../../Application.h"
#include "../../../Manager/InputManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Utility/Collision.h"
#include "Level4.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../Block/Block4.h"
#include "../BackGround.h"
#include "../Camera/Camera.h"
#include "../Moon/Moon1.h"
#include "../Side/SideBase.h"
#include "../Side/Side4.h"
#include "../Gimic/FireBall.h"

Level4::Level4(void)
{
}

Level4::~Level4()
{
}

void Level4::AddInit()
{
	//�S�[���̓ǂݍ���
	moon_ = new Moon1();
	moon_->Init(this);

	//�u���b�N�̓ǂݍ���
	block_ = new Block4();
	block_->Init(this);

	//�T�C�h�̓ǂݍ���
	side_ = new Side4();
	side_->Init(this);
}

void Level4::Update(void)
{
	//�q�b�g�X�g�b�v����
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}

	LevelManager::Update();

	//�΂̋ʂ̏���
	FireBallCollision();

	//�S�[������
	moon_->Update();

	//�S�[���Ƃ̏Փ˔���
	LevelManager::GoalHit();
}

void Level4::Draw(void)
{
	// �U��
	if (hitStopCnt_ > 0)
	{
		// �`���̃X�N���[����ݒ� �q�b�g�X�g�b�v���́A
		SetDrawScreen(tmpScreen_);
		ClearDrawScreen();				//�`��̈�̃N���A
	}

	backGround_->Draw();
	moon_->Draw();
	block_->Draw();
	player_->Draw();

	//�΂̋ʂ̕`��
	auto fires = block_->GetFireBall();
	for (auto fire : fires)
	{
		fire->Draw();
	}

	camera_->Draw();
	side_->Draw();
	CameraShake();

	DebagDraw();
}

void Level4::Release(void)
{	
	auto fires = block_->GetFireBall();
	for (auto fire : fires)
	{
		fire->Release();
	}
	moon_->Release();
	delete moon_;
	
	block_->Release();
	delete block_;
	
	side_->Release();
	delete side_;
	LevelManager::Release();
}

void Level4::SetParam()
{
	// �t�B�[���h�T�C�Y��ݒ�
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };

	// �n�ʃT�C�Y��ݒ�
	groundSize_ = { FIELD_WIDTH, GROUND_HEIGHT };

	// �X�e�[�W�T�C�Y��ݒ�
	stageSize_ = {
		fieldSize_.x,
		fieldSize_.y + groundSize_.y
	};

	float fieldY = static_cast<float>(fieldSize_.y);  // �t�B�[���h�̏c�T�C�Y�� float �ɕϊ�

	// �v���C���[�̏������W��ݒ�
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2,
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

	// �`�撆�S�̍��W��ݒ�
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- fieldSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2,
		0
	};

}

void Level4::FireBallCollision()
{
	auto& snd = SoundManager::GetInstance();

	//�΂̋ʂ̏���
	auto fires = block_->GetFireBall();
	for (auto fire : fires)
	{
		//����������
		fire->Update();

		Vector2 fPos = fire->GetPos().ToVector2();
		Vector2 fSize = { FireBall::SIZE_X,
						  FireBall::SIZE_Y };

		int pRadius = player_->GetSize().y / 2;

		//�v���C���[�Ƃ̏Փ˔���
		if (fire->GetState() == FireBall::STATE::FIRE &&
			Collision::IsCollisionCircle(player_->GetPos().ToVector2(),
				pRadius,
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
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::FIRE_BALL_HIT));
		}
		else if (fire->GetState() == FireBall::STATE::FIRE &&
			IsHitMino(fPos, fSize))
		{
			fire->SetState(FireBall::STATE::BLAST);
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::FIRE_BALL_HIT));
		}
	}
}

