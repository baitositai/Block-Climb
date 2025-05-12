#include <DxLib.h>
#include <cmath>
#include "../../../Application.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"
#include "../Level/LevelManager.h"
#include "../Block/BlockBase.h"
#include "Moon6.h"

Moon6::Moon6()
{
	level_ = nullptr;
}

Moon6::~Moon6()
{
}

void Moon6::Reset()
{
	Moon::Reset();

#pragma region 黒い月の初期設定
	int i = static_cast<int>(MOON_TYPE::DEAD);
	darkState_ = RandamDarkMove();
	pos_[i] = ResetPos();
	isMoon_[i] = false;
	
	speed_ = { MOVE_SPEED,MOVE_SPEED };
	drawSize_ = 1.0f;
	alpha_ = 256;
	respawn_ = INTERVAL * SceneManager::DEFAULT_FPS;
#pragma endregion

#pragma region 黄色月の初期設定
	i = static_cast<int>(MOON_TYPE::GOAL);
	firstPos_[i] = { Application::SCREEN_SIZE_X / 2, static_cast<float>( - BlockBase::BLOCK_SIZE_Y * (80 - level_->GetFieldSize().y))};
	pos_[i] = firstPos_[i];
	isMoon_[i] = false;
	preBlock_ = 24;
	scroll_ = 0;
	scrollMax_ = 0;
	scrollSpeed_ = 2.0f;
#pragma endregion

}

void Moon6::Update()
{
	int height = level_->GetBlockHeight();

	if (height > 20) { DarkMoonUpdate(); }

	if (height > 70) { GoalMoonUpdate(); }
}

void Moon6::Draw()
{
	DarkMoonDraw();

	GoalMoonDraw();
}

Moon6::DARK_MOVE Moon6::RandamDarkMove()
{
	int i = rand() % 2;
	if (i == 0) {
		return DARK_MOVE::DIAGONAL;
	}
	else {
		return DARK_MOVE::DIAGONAL_RE;
	}
}

Vector2F Moon6::ResetPos()
{
	Vector2F pos;
	float posX = 0.0f;

	switch (darkState_)
	{
	case DARK_MOVE::DIAGONAL:
		posX = rand() % (Application::SCREEN_SIZE_X / 3);
		break;

	case DARK_MOVE::DIAGONAL_RE:
		posX = Application::SCREEN_SIZE_X + (rand() % SIZE_X);
		break;

	default:
		break;
	}
	return pos = { posX,-SIZE_Y * 1.5 };
}

Vector2F Moon6::ResetSpeed()
{
	float speedX = MOVE_SPEED + (rand() % 10);
	float speedY = MOVE_SPEED + (rand() % 10);
	Vector2F speed = { speedX, speedY };
	return speed;
}

void Moon6::DarkMoonUpdate()
{
	int i = static_cast<int>(MOON_TYPE::DEAD);
	auto& snd = SoundManager::GetInstance();

	switch (darkState_)
	{
		//インターバル(移動停止)
	case DARK_MOVE::STOP:
		stopCnt_++;
		if (stopCnt_ > respawn_)
		{
			stopCnt_ = 0;
			downCnt_ = 2 + (rand() % 4);
			darkState_ = RandamDarkMove();
			pos_[i] = ResetPos();
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC,static_cast<int>(SoundManager::GIMIC::DARK_MOON_RESPAWN));
		}
		break;

		//斜め移動処理
	case DARK_MOVE::DIAGONAL:
		//移動処理
		pos_[i].x += speed_.x;
		pos_[i].y += speed_.x;
		//画面外に出たら
		if (pos_[i].x > Application::SCREEN_SIZE_X + SIZE_X || 
			pos_[i].y > Application::SCREEN_SIZE_Y + SIZE_Y * 2)
		{
			//出現回数がまだある場合
			if(downCnt_ > 0)
			{
				darkState_ = RandamDarkMove();
				pos_[i] = ResetPos();
				speed_ = ResetSpeed();
				downCnt_--;
				snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::DARK_MOON_RESPAWN));
			}
			//0以下の場合
			else 
			{
				darkState_ = DARK_MOVE::STOP;
			}
		}
		break;

	case DARK_MOVE::DIAGONAL_RE:
		//移動処理
		pos_[i].x -= speed_.x;
		pos_[i].y += speed_.y;
		//画面外に出たら
		if (pos_[i].x < 0 ||
			pos_[i].y > Application::SCREEN_SIZE_Y + SIZE_Y * 2)
		{
			//出現回数がまだある場合
			if (downCnt_ > 0)
			{
				darkState_ = RandamDarkMove();
				pos_[i] = ResetPos();
				speed_ = ResetSpeed();
				downCnt_--;
				snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::DARK_MOON_RESPAWN));
			}
			//0以下の場合
			else
			{
				darkState_ = DARK_MOVE::STOP;
			}
		}
		break;

		//衝突時の大きくなる処理
	case DARK_MOVE::FADE_BIG:
		drawSize_ += 0.2f;
		alpha_--;
		if (drawSize_ >= 30.0f)
		{
			darkState_ = DARK_MOVE::STOP;
			alpha_ = 256;
			drawSize_ = 1.0f;
			isMoon_[i] = false;
			pos_[i] = firstPos_[i];
			level_->PlayBGM();
		}
		break;

	default:
		break;
	}
}

void Moon6::GoalMoonUpdate(void)
{
	int i = static_cast<int>(MOON_TYPE::GOAL);

	//座標設定
	pos_[i] = firstPos_[i];

	//シェイク用変数
	float amplitude = 1.0f;// 揺らす周波数（Hz）0.3
	float frequency = 5.0f;// 揺らす振幅（ピクセル）

	//シェイク処理
	pos_[i] = AsoUtility::SinShake(pos_[i].ToVector2(), amplitude, frequency).ToVector2F();

}


void Moon6::DarkMoonDraw()
{
	Vector2 cameraPos = level_->GetCameraPos().ToVector2();
	int i = static_cast<int>(MOON_TYPE::DEAD);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	DrawRotaGraph(pos_[i].x - cameraPos.x,
		pos_[i].y - cameraPos.y,
		drawSize_,		//拡大
		0.0f,			//回転
		images_[i],
		true,			//透過
		false);			//反転
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Moon6::GoalMoonDraw(void)
{
	Vector2 cameraPos = level_->GetCameraPos().ToVector2();
	int i = static_cast<int>(MOON_TYPE::GOAL);
	DrawRotaGraph(pos_[i].x - cameraPos.x,
		pos_[i].y - cameraPos.y,
		1.0f,		//拡大
		0.0f,			//回転
		images_[i],
		true,			//透過
		false);			//反転
}