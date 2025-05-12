#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Scene/GameScene.h"
#include "GameStart.h"

GameStart::GameStart(void)
{
	angle_ = 0.0f;
	cnt_ = 0;
	expansion_ = 0.0f;
	gameScene_ = nullptr;
	imgStart_ = 0;
	state_ = STATE::NONE;
}

GameStart::~GameStart(void)
{
}

void GameStart::Init(GameScene* parent)
{
	gameScene_ = parent;

	Reset();

	SetImage();
}

void GameStart::Update(void)
{
	Vector2 startPos = { Application::SCREEN_SIZE_X / 2,
						  Application::SCREEN_SIZE_Y / 2 };
	Vector2 stopPos = { Application::SCREEN_SIZE_X + size_.x / 2,
						-size_.y / 2 };
	int moveSpeed;

	switch (state_)
	{
	case STATE::UP:
		expansion_ += EXPANSION;
		if (expansion_ >= EXPANSION_MAX)
		{
			expansion_ = EXPANSION_MAX;
			state_ = STATE::WAIT;
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::START));
		}
		break;

	case STATE::WAIT:
		cnt_++;
		if (cnt_ >= WAIT_SECOND * SceneManager::DEFAULT_FPS)
		{
			state_ = STATE::EXIT;
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::START_GO_OUT));
		}
		break;

	case STATE::EXIT:
		moveSpeed = (stopPos.y - startPos.y /
						stopPos.x - startPos.x) * MOVE_SPEED;
		 
		pos_.x -= moveSpeed;
		pos_.y += moveSpeed;

		angle_ += ROTATION;

		if (pos_.x >= stopPos.x &&
			pos_.y <= stopPos.y)
		{
			gameScene_->ChangeState(GameScene::STATE::GAME);
		}
		break;

	default:
		break;
	}
}

void GameStart::Draw(void)
{
	DrawRotaGraph(pos_.x, pos_.y,
		expansion_,
		angle_,
		imgStart_,
		true,
		false);
}

void GameStart::Release(void)
{
	DeleteGraph(imgStart_);
}

void GameStart::Reset()
{
	//初期状態
	state_ = STATE::UP;

	//大きさ
	expansion_ = 0.0f;

	//待ちカウント初期化
	cnt_ = 0;

	//回転値
	angle_ = 0.0f;

	//初期座標
	pos_ = { Application::SCREEN_SIZE_X / 2,
			 Application::SCREEN_SIZE_Y / 2 };
}