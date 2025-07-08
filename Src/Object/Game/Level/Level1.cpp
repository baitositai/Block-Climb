#include "../../../Application.h"
#include "../../../Manager/InputManager.h"
#include "../../../Utility/Collision.h"
#include "Level1.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../Block/Block1.h"
#include "../BackGround.h"
#include "../Camera/Camera.h"
#include "../Moon/Moon1.h"
#include "../Side/SideBase.h"
#include "../Side/Side1.h"

Level1::Level1(void)
{
}

Level1::~Level1(void)
{
}

void Level1::AddInit()
{
	//�S�[���̓ǂݍ���
	moon_ = new Moon1();
	moon_->Init(this);

	//�u���b�N�̓ǂݍ���
	block_ = new Block1();
	block_->Init(this);

	//�T�C�h�̓ǂݍ���
	side_ = new Side1();
	side_->Init(this);
}

void Level1::Update(void)
{
	//�q�b�g�X�g�b�v����
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}

	LevelManager::Update();

	//�S�[������
	moon_->Update();

	//�S�[���Ƃ̏Փ˔���
	LevelManager::GoalHit();
}

void Level1::Draw(void)
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
	camera_->Draw();
	
	CameraShake();

	side_->Draw();
	DebagDraw();
}

void Level1::Release(void)
{
	side_->Release();
	delete side_;
	block_->Release();
	delete block_;
	moon_->Release();
	delete moon_;
	LevelManager::Release();
}

void Level1::SetParam()
{
	//�e��T�C�Y�ݒ�
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };                             //�t�B�[���h�T�C�Y
	groundSize_ = { FIELD_WIDTH, GROUND_HEIGHT };                           //�n�ʃT�C�Y
	stageSize_ = { fieldSize_.x, fieldSize_.y + groundSize_.y };            //�X�e�[�W�S�̂̃T�C�Y

	float fieldY = static_cast<float>(fieldSize_.y);                        //�v�Z�p��float�֕ϊ�

	//�v���C���[�̏������W
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2,                                     //��ʒ���
		BlockBase::BLOCK_SIZE_Y * (fieldY - PLAYER_START_OFFSET_Y) - PLAYER_PIXEL_OFFSET_Y //Y���W������2�u���b�N�ځA������
	};

	//�J�����̏������W
	firstCameraPos_ = {
		0,                                                                  //���_
		-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + CAMERA_OFFSET_Y_BLOCKS) //��ʉ������ɂ��炷
	};

	//�S�[�����W
	goalPos_ = {
		Application::SCREEN_SIZE_X / 2 + GOAL_OFFSET_X,                     //��ʒ�������E�ɂ��炷
		GOAL_POS_Y                                                          //�Œ�l
	};

	//�`�撆�S�i��ʍ��킹�p�j
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- fieldSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2 * DRAW_CENTER_BLOCK_OFFSET_X,     
		0
	};

}

