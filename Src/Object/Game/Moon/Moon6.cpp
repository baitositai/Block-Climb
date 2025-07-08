#include <DxLib.h>
#include <cmath>
#include "../../../Application.h"
#include "../../../Common/Fader.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"
#include "../Level/LevelManager.h"
#include "../Block/BlockBase.h"
#include "Moon6.h"

Moon6::Moon6()
{
	level_ = nullptr;
	stopCnt_ = 0.0f;
	downCnt_ = 0;
	respawn_ = 0;
	alpha_ = 0;
	preBlock_ = 0;
	scroll_ = 0.0f;
	scrollSpeed_ = 0.0f;
	scrollMax_ = 0.0f;
	speed_ = {};
}

Moon6::~Moon6()
{
}

void Moon6::Reset()
{
	Moon::Reset();

	//黒い月の初期設定
	int i = static_cast<int>(MOON_TYPE::DEAD);
	darkState_ = RandamDarkMove();
	pos_[i] = ResetPos();
	isMoon_[i] = false;
	
	speed_ = { MOVE_SPEED,MOVE_SPEED };
	drawSize_ = 1.0f;
	alpha_ = Fader::FADE_MAX;
	respawn_ = INTERVAL * SceneManager::DEFAULT_FPS;

	//黄色月の初期設定
	i = static_cast<int>(MOON_TYPE::GOAL);
	firstPos_[i] = { Application::SCREEN_SIZE_X / 2, static_cast<float>( - BlockBase::BLOCK_SIZE_Y * (GOAL_MOON_HEIGHT_OFFSET - level_->GetFieldSize().y))};
	pos_[i] = firstPos_[i];
	isMoon_[i] = false;
	preBlock_ = MOON_GOAL_PRE_BLOCK;
	scroll_ = 0;
	scrollMax_ = 0;
	scrollSpeed_ = MOON_SCROLL_SPEED;
}

void Moon6::Update()
{
	int height = level_->GetBlockHeight();

	if (height > DARK_MOON_TERM_HEIGHT) { DarkMoonUpdate(); }

	if (height > GOAL_MOON_TERM_HEIGHT) { GoalMoonUpdate(); }
}

void Moon6::Draw()
{
	DarkMoonDraw();

	GoalMoonDraw();
}

Moon6::DARK_MOVE Moon6::RandamDarkMove()
{
	constexpr int MOVE_TYES = 2;

	int i = rand() % MOVE_TYES;
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
		posX = rand() % (Application::SCREEN_SIZE_X / DARK_SCREEN_DIVISOR); // 画面の左側ランダム
		break;

	case DARK_MOVE::DIAGONAL_RE:
		posX = Application::SCREEN_SIZE_X + (rand() % SIZE_X); // 画面右外からランダム
		break;

	default:
		break;
	}

	// 初期座標を返す（上方向にオフセット）
	return pos = { posX, -SIZE_Y * DARK_POS_Y_OFFSET };
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
			downCnt_ = RANDAM_MOON_DOWN_MIN + (rand() % RANDAM_MOON_DOWN_MAX);
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
		drawSize_ += EXPANSION_SPEED;
		alpha_--;
		if (drawSize_ >= SIZE_MAX_RATE)
		{
			darkState_ = DARK_MOVE::STOP;
			alpha_ = Fader::FADE_MAX;
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

	//シェイク処理
	pos_[i] = AsoUtility::SinShake(pos_[i].ToVector2(), AMPLITUDE, FREQUENCY).ToVector2F();

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