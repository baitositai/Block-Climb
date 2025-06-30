#include "../../../Application.h"
#include "../../../Manager/InputManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Utility/Collision.h"
#include "Level3.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../Block/Block3.h"
#include "../BackGround.h"
#include "../Camera/Camera.h"
#include "../Side/SideBase.h"
#include "../Side/Side3.h"
#include "../Gimic/Blast.h"
#include "../Moon/Moon3.h"

Level3::Level3(void)
{
	isBlast_ = false;
	moon_ = nullptr;
}

Level3::~Level3(void)
{
}

void Level3::AddInit()
{
	//�u���b�N�̓ǂݍ���
	block_ = new Block3();
	block_->Init(this);

	side_ = new Side3();
	side_->Init(this);

	moon_ = new Moon3();
	moon_->Init(this);
}

void Level3::Update(void)
{
	//�q�b�g�X�g�b�v����
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}

	//�Q�[���I�[�o�[�`�F�b�N
	GameOverCheck();

	//�Q�[���N���A�`�F�b�N
	GameClearCheck();

	//�u���b�N����(�������͍s��Ȃ�)
	if (!isBlast_) { block_->Update(); }

	//�v���C���[
	player_->Update();

	//�w�i�X�N���[��
	backGround_->Update();

	//�J����
	camera_->Update();

	//�T�C�h���(�X�R�A�֌W)
	side_->Update();

	//��
	moon_->Update();

	//�t�B�[���h�Ƀu���b�N���Ȃ���Ԃ̎�����
	//���̃X�e�[�g��FADE_BIG����Ȃ��Ƃ�
	//���̃X�e�[�g��STOP�ɂ��Ă���
	if (!block_->IsBlock() && moon_->GetDarkMove() != Moon::DARK_MOVE::FADE_BIG)
	{
		moon_->SetDarkMove(Moon::DARK_MOVE::STOP);
	}

	//���Ƃ̏Փ˔���
	HitMoon();

	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		//����������
		blast->Update();

		//�������ĂȂ��Ƃ�
		if (blast->GetState() == Blast::STATE::NONE)
		{
			isBlast_ = false;
		}

		//�������̏���
		if (blast->GetState() == Blast::STATE::BLAST)
		{
			isBlast_ = true;
			//�Փ˔���
			if (!player_->IsDeath() &&
				Collision::IsCollisionCircle(player_->GetPos().ToVector2(),
					player_->GetSize().x / 2,
					blast->GetPos(),
					blast->GetRadius()))
			{
				SetStopCnt(HIT_STOP_CNT);
				player_->SetIsDeath(true);
			}
		}	
	}

	//�N���A�������C������������N���A����ɂ���
	if (block_->GetLineCount() >= Block3::CREAL_LINE)
	{
		SetGameClear(true);
	}
}

void Level3::Draw(void)
{
	// �U��
	if (hitStopCnt_ > 0)
	{
		// �`���̃X�N���[����ݒ� �q�b�g�X�g�b�v���́A
		SetDrawScreen(tmpScreen_);
	}

	backGround_->Draw();
	block_->Draw();
	LevelManager::Draw();
	moon_->Draw();
	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		blast->Draw();
	}
	player_->Draw();
	camera_->Draw();
	side_->Draw();

	CameraShake();

	DebagDraw();
}

void Level3::Release(void)
{
	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		blast->Release();
	}
	moon_->Release();
	delete moon_;
	
	side_->Release();
	delete side_;
	
	block_->Release();
	delete block_;
	
	LevelManager::Release();
	
}

void Level3::SetParam()
{
	// �t�B�[���h�ƒn�ʂ̃T�C�Y��ݒ�
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };
	groundSize_ = { FIELD_WIDTH, GROUND_HEIGHT };

	// �X�e�[�W�T�C�Y��ݒ�
	stageSize_ = {
		fieldSize_.x,
		fieldSize_.y + groundSize_.y
	};

	float fieldY = static_cast<float>(fieldSize_.y);  // �t�B�[���h�̏c�T�C�Y�� float �ɕϊ����Čv�Z

	// �v���C���[�̏������W��ݒ�
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2,
		BlockBase::BLOCK_SIZE_Y * (fieldY - PLAYER_START_BLOCK_OFFSET_Y) - PLAYER_PIXEL_OFFSET_Y
	};

	// �J�����̏������W��ݒ�
	firstCameraPos_ = {
		0,
		-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + CAMERA_BLOCK_OFFSET_Y)
	};

	// �S�[�����W��ݒ�
	goalPos_ = {
		Application::SCREEN_SIZE_X / 2 + GOAL_OFFSET_X,
		GOAL_POS_Y
	};

	// �`��ʒu����ʂ̒��S�ɍ��킹�Ē���
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- fieldSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2,
		0
	};

	//���������false��
	isBlast_ = false;
}

void Level3::HitMoon()
{
	//�v���C���[���̎擾
	Vector2 pPos = player_->GetPos().ToVector2();
	Vector2 pSize = player_->GetSize();			//�v���C���[��x���W�̔����𔼌a�Ƃ���
	int pRadius = pSize.x / 2;

	//���̎擾
	Vector2 mPos = moon_->GetPos(Moon::MOON_TYPE::DEAD).ToVector2();

	if (!isBlast_ &&
		Collision::IsCollisionCircle(pPos, pRadius, mPos, Moon::RADIUS) && 
		moon_->IsMoon(Moon::MOON_TYPE::DEAD) == false)
	{
		StopBGM();
		moon_->SetDarkMove(Moon::DARK_MOVE::FADE_BIG);
		SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::DARK_MOON_HIT));
		block_->AllDeleteLine();
	}
}