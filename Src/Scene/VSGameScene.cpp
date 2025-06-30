#include <DxLib.h>
#include "../Common/Data.h"
#include "../Common/Fader.h"
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

#include "VSGameScene.h"
#include "../Object/Game/Level/LevelManager.h"
#include "../Object/Game/Level/Marason.h"

#include "../Object/Game/Start/GameStart.h"
#include "../Object/Game/Over/GameOver.h"

#include "../Object/Game/GameClear.h"
#include "../Object/Game/Pause.h"

VSGameScene::VSGameScene(void)
{
	level_ = nullptr;
	start_ = nullptr;
	over_ = nullptr;
	fader_ = nullptr;
}

VSGameScene::~VSGameScene(void)
{
}

void VSGameScene::Init(void)
{
	LevelLoad();
	level_->Init(this);

	start_->Init(this);

	over_ = new GameOver();
	over_->Init();

	clear_ = new GameClear();
	clear_->Init();

	select_ = new Pause();
	select_->Init(this);

	fader_ = new Fader();
	fader_->Init();

	//初期状態
	state_ = STATE::START;
	cnt_ = 0;
}

void VSGameScene::Update(void)
{
	fader_->Update();

	if (isStateChanging_)
	{
		Fade();
	}
	else
	{
		//ゲームステートごとに更新処理
		switch (state_)
		{
		case STATE::START:
			start_->Update();
			break;

		case STATE::GAME:
			isSelect_ = false;
			level_->Update();
			break;

		case STATE::OVER:
			over_->Update();
			break;

		case STATE::CLEAR:
			clear_->Update();
			break;

		case STATE::PAUSE:
			isSelect_ = true;
			break;

		default:
			break;
		}

		if (isSelect_) { select_->Update(); }

		//一時停止機能
		auto& ins = InputManager::GetInstance();
		if ((ins.IsTrgDown(KEY_INPUT_R) ||
			ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::LEFT)) &&
			(state_ == STATE::GAME || state_ == STATE::PAUSE))
		{
			select_->Reset();
			if (state_ == STATE::PAUSE) { state_ = STATE::GAME; }
			else { state_ = STATE::PAUSE; }
		}

		//ゴール・ゲームオーバー時の選択処理出現カウント処理
		if (state_ == STATE::CLEAR || state_ == STATE::OVER)
		{
			cnt_++;
			if (cnt_ >= 2 * SceneManager::DEFAULT_FPS)
			{
				isSelect_ = true;
				if (Data::LEVEL::MARASON == Data::GetInstance().GetStageData())
				{
					CheckNewRecode();
				}
			}
		}
	}
}

void VSGameScene::Draw(void)
{
	level_->Draw();
	if (state_ == STATE::START) { start_->Draw(); }
	if (state_ == STATE::OVER) { over_->Draw(); }
	if (state_ == STATE::CLEAR) { clear_->Draw(); }
	if (isSelect_) { select_->Draw(); }
	if (select_->IsNewRecode()) { select_->NewRecodeDraw(); }
	fader_->Draw();
}

void VSGameScene::Release(void)
{
	select_->Release();
	delete select_;
	
	level_->Release();
	delete level_;
	
	over_->Release();
	delete over_;
	
	clear_->Release();
	delete clear_;
	
	start_->Release();
	delete start_;
}

void VSGameScene::Reset()
{
	state_ = STATE::START;
	cnt_ = 0;
	start_->Init(this);
	level_->Init(this);
	isSelect_ = false;
}