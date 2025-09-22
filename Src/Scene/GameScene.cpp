#include <DxLib.h>
#include "../Common/Data.h"
#include "../Common/Fader.h"
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SoundManager.h"
#include "GameScene.h"

#include "../Object/Game/Level/LevelManager.h"
#include "../Object/Game/Level/Level1.h"
#include "../Object/Game/Level/Level2.h"
#include "../Object/Game/Level/Level3.h"
#include "../Object/Game/Level/Level4.h"
#include "../Object/Game/Level/Level5.h"
#include "../Object/Game/Level/Level6.h"
#include "../Object/Game/Level/Marason.h"

#include "../Object/Game/Start/GameStart.h"
#include "../Object/Game/Start/Start1.h"
#include "../Object/Game/Start/Start2.h"
#include "../Object/Game/Start/Start3.h"
#include "../Object/Game/Start/Start4.h"
#include "../Object/Game/Start/Start5.h"
#include "../Object/Game/Start/StartMarason.h"

#include "../Object/Game/Over/GameOver.h"

#include "../Object/Game/GameClear.h"
#include "../Object/Game/Pause.h"



GameScene::GameScene(void)
{
	bgm_ = SoundManager::BGM::MAX;
	clear_ = nullptr;
	cnt_ = 0;
	select_ = nullptr;
	isSelect_ = false;
	isStateChanging_ = false;
	state_ = STATE::START;
	level_ = nullptr;
	start_ = nullptr;
	over_ = nullptr;
	fader_ = nullptr;
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
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
	
	//BGMの再生
	SoundManager::GetInstance().PlayBgmSound(bgm_, BGM_VOLUME, true);
}

void GameScene::Update(void)
{
	auto& snd = SoundManager::GetInstance();

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
			ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::LEFT))&&
			(state_ == STATE::GAME || state_ == STATE::PAUSE))
		{
			select_->Reset();
			//ゲーム中に押した場合
			if (state_ == STATE::PAUSE)
			{ 
				snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_DECIDE));
				snd.PlayBgmSound(bgm_, BGM_VOLUME, false);
				state_ = STATE::GAME; 
			}
			//一時停止中にもう一度押した場合
			else 
			{ 
				snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_CANCEL));
				snd.StopBgmSound(bgm_);
				state_ = STATE::PAUSE; 
			}
		}

		//ゴール・ゲームオーバー時の選択処理出現カウント処理
		if (state_ == STATE::CLEAR || state_ == STATE::OVER)
		{
			cnt_ += SceneManager::GetInstance().GetDeltaTime();
			if (cnt_ >= FINISH_TO_WAIT_TIME)
			{
				isSelect_ = true;
				if(Data::LEVEL::MARASON == Data::GetInstance().GetStageData())
				{
					CheckNewRecode();
				}
			}
		}
	}
}

void GameScene::Draw(void)
{
	level_->Draw();
	if (state_ == STATE::START) { start_->Draw(); }
	if (state_ == STATE::OVER ) { over_->Draw(); }
	if (state_ == STATE::CLEAR) { clear_->Draw(); }
	if (isSelect_) { select_->Draw(); }
	if (select_->IsNewRecode()) { select_->NewRecodeDraw(); }
	fader_->Draw();
}

void GameScene::Release(void)
{
	select_->Release();
	delete select_;
	clear_->Release();
	delete clear_;
	over_->Release();
	delete over_;
	start_->Release();
	delete start_;
	level_->Release();
	delete level_;
}

void GameScene::Reset()
{
	state_ = STATE::START;
	cnt_ = 0;
	start_->Init(this);
	level_->Init(this);
	isSelect_ = false;
	SoundManager::GetInstance().PlayBgmSound(bgm_, BGM_VOLUME, true);
}

void GameScene::LevelLoad()
{
	//ステージ選択の反映
	Data::LEVEL stageData = Data::GetInstance().GetStageData();

	switch (stageData)
	{
	case Data::LEVEL::LEVEL1:
		level_ = new Level1();
		start_ = new Start1();
		bgm_ = SoundManager::BGM::GAME1;
		
		break;
	
	case Data::LEVEL::LEVEL2:
		level_ = new Level2();
		start_ = new Start2();
		bgm_ = SoundManager::BGM::GAME2;
		break;

	case Data::LEVEL::LEVEL3:
		level_ = new Level3();
		start_ = new Start3();
		bgm_ = SoundManager::BGM::GAME3;
		break;

	case Data::LEVEL::LEVEL4:
		level_ = new Level4();
		start_ = new Start4();
		bgm_ = SoundManager::BGM::GAME4;
		break;

	case Data::LEVEL::LEVEL5:
		level_ = new Level5();
		start_ = new Start5();
		bgm_ = SoundManager::BGM::GAME2;
		break;

	case Data::LEVEL::LEVEL6:
		level_ = new Level6();
		start_ = new Start1();
		bgm_ = SoundManager::BGM::TITLE;
		break;

	case Data::LEVEL::MARASON:
		level_ = new Marason();
		start_ = new StartMarason();
		//マラソンのBGMはランダムで決める
		bgm_ = GetRandGameBgm();
		break;

	default:
		break;
	}
}

void GameScene::Retry()
{
	// フェードアウト(暗転)を開始する
	fader_->SetFade(Fader::STATE::FADE_OUT);
	StopBGM();
	isStateChanging_ = true;
}

void GameScene::SetIsSelect(bool value)
{
	isSelect_ = value;
}

void GameScene::ChangeState(STATE state)
{
	STATE preSta = state_;
	state_ = state;

	//ステートが変わるとき効果音をつける
	if (preSta == STATE::GAME) {
		if (state_ == STATE::OVER) {
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::GAME_OVER));
		}
		else if (state_ == STATE::CLEAR) {
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::CLEAR));
		}
	}

}

void GameScene::CheckNewRecode()
{
	int data = Data::GetInstance().GetMarasonData();
	int nowData = level_->GetBlockHeight();
	if (data < nowData)
	{
		select_->SetIsNewRecode(true);
		Data::GetInstance().SetMarasonData(nowData);
	}
}

void GameScene::Fade(void)
{
	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		// 明転中
		if (fader_->IsEnd())
		{
			// 明転が終了したら、フェード処理終了
			fader_->SetFade(Fader::STATE::NONE);
			isStateChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// 暗転中
		if (fader_->IsEnd())
		{
			Reset();
			// 暗転から明転へ
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}
}

SoundManager::BGM GameScene::GetRandGameBgm()
{

	SoundManager::BGM type = SoundManager::BGM::MAX;
	int randNum = static_cast<int>(SoundManager::BGM::GAME1) + rand() % RAND_BGMS - 1;

	switch (static_cast<SoundManager::BGM>(randNum))
	{
	case SoundManager::BGM::GAME1:
		type = SoundManager::BGM::GAME1;
		break;
	case SoundManager::BGM::GAME2:
		type = SoundManager::BGM::GAME2;
		break;
	case SoundManager::BGM::GAME3:
		type = SoundManager::BGM::GAME3;
		break;
	case SoundManager::BGM::GAME4:
		type = SoundManager::BGM::GAME4;
		break;
	default:
		break;
	}
	return type;
}

void GameScene::PlayBGM()
{
	SoundManager::GetInstance().PlayBgmSound(bgm_, BGM_VOLUME, false);
}

void GameScene::StopBGM()
{
	SoundManager::GetInstance().StopBgmSound(bgm_);
}

GameScene::STATE GameScene::GetState()
{
	return state_;
}

int GameScene::GetHeight()
{
	return level_->GetBlockHeight();
}
