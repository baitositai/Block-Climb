#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Fader.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Manager/SoundManager.h"
#include "../Level/LevelManager.h"
#include "../Block/Block3.h"
#include "Moon3.h"

Moon3::Moon3()
{
	level_ = nullptr;
}

Moon3::~Moon3()
{
}

void Moon3::Reset()
{	
	Moon::Reset();

	int i = static_cast<int>(MOON_TYPE::DEAD);
	float posX = level_->GetGameCenter().x + SIZE_X + GetRand(SIZE_X * level_->GetFieldSize().x);
	firstPos_[i] = { posX,-SIZE_Y };
	pos_[i] = firstPos_[i];
	isMoon_[i] = false;
	darkState_ = DARK_MOVE::DOWN;
	move_ = MOVE_SPEED;
	drawSize_ = 1.0f;
	alpha_ = Fader::FADE_MAX;

}

void Moon3::Update()
{
	auto& snd = SoundManager::GetInstance();
	int i = static_cast<int>(MOON_TYPE::DEAD);

	if (Block3::CREAL_LINE > Block3::CREAL_LINE - level_->GetCntLine())
	{
		switch (darkState_)
		{
		//ƒCƒ“ƒ^[ƒoƒ‹(ˆÚ“®’âŽ~)
		case DARK_MOVE::STOP:
			cnt_++;
			if (cnt_ > respawn_)
			{
				drawSize_ = 1.0f;
				darkState_ = DARK_MOVE::DOWN;
				float posX = level_->GetGameCenter().x + SIZE_X + GetRand(SIZE_X * level_->GetFieldSize().x);
				pos_[i] = { posX, -SIZE_Y };
				downCnt_ = 1 + rand() % CREATE_RAND_MAX_SECOND;
				snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::DARK_MOON_RESPAWN));
			}

			break;

		//—Ž‰ºˆ—
		case DARK_MOVE::DOWN:
			pos_[i].y += move_;
			if (pos_[i].y >= Application::SCREEN_SIZE_Y + SIZE_Y / 2)
			{
				downCnt_--;
				if (downCnt_ < 0) {
					darkState_ = DARK_MOVE::STOP;
					respawn_ = INTERVAL * (1 + rand() % CREATE_RAND_MAX_SECOND);
				}
				else
				{
					float posX = level_->GetGameCenter().x + SIZE_X + GetRand(SIZE_X * level_->GetFieldSize().x);
					pos_[i] = { posX,-SIZE_Y };
					snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::DARK_MOON_RESPAWN));
				}
			}
			break;

		//Õ“ËŽž‚Ì‘å‚«‚­‚È‚éˆ—
		case DARK_MOVE::FADE_BIG:
			drawSize_+= EXPANSION_SPEED;
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
		}
	}
}

void Moon3::Draw()
{
	Vector2 cameraPos = level_->GetCameraPos().ToVector2();
	int i = static_cast<int>(MOON_TYPE::DEAD);	

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	DrawRotaGraph(pos_[i].x + cameraPos.x,
		pos_[i].y + cameraPos.y,
		drawSize_,		//Šg‘å
		0.0f,			//‰ñ“]
		images_[i],
		true,			//“§‰ß
		false);			//”½“]
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
