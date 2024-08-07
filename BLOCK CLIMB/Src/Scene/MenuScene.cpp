#include <Dxlib.h>
#include "../Application.h"
#include "../Common/Scroll.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Common/Data.h"
#include "MenuScene.h"
#include "../Object/Menu/Challenge.h"
#include "../Object/Menu/Manual.h"
#include "../Object/Menu/TagPlay.h"
#include "../Object/Menu/Credit.h"
#include "../Object/Menu/Text.h"
#include "../Object/Game/PlayerBase.h"
#include "../Object/Game/Block/BlockBase.h"
#include "../Object/Game/Block/BlockShower.h"
#include "../Object/Menu/MenuPlayer.h"

MenuScene::MenuScene(void)
{
	challenge_ = nullptr;
	credit_ = nullptr;
	imgBack_ = 0;
	imgPoint_ = 0;
	isStick_ = false;
	manual_ = nullptr;
	menuCnt_ = 0;
	player_ = nullptr;
	scroll_ = nullptr;
	sleState_ = STATE::MARASON;
	state_ = STATE::NONE;
	step_ = 0;
	tag_ = nullptr;
	text_ = nullptr;
}

MenuScene::~MenuScene(void)
{
}

void MenuScene::Init(void)
{
	//レベルセレクトの読み込み
	challenge_ = new Challenge();
	challenge_->Init(this);

	//マニュアルの読み込み
	manual_ = new Manual();
	manual_->Init(this);

	//対戦用セレクトの読み込み
	tag_ = new TagPlay();
	tag_->Init(this);

	//テキストの読み込み
	text_ = new Text();
	text_->Init(this);

	//プレイヤーの読み込み
	player_ = new MenuPlayer();
	player_->Init(this);

	//クレジットの読み込み
	credit_ = new Credit();
	credit_->Init(this);

	//画像読み込み
	Load();
	
	//変数の初期化
	Reset();
	
	//背景画像の設定
	SetBackImage();

	//bgmの再生
	SoundManager::GetInstance().PlayBgmSound(SoundManager::BGM::MENU, 70, true);
}

void MenuScene::Update(void)
{
	//背景の処理
	scroll_->Update();

	switch (state_)
	{
	case STATE::SELECT:
		challenge_->Update();
		break;

	case STATE::MANYUAL:
		manual_->Update();
		break;

	case STATE::MARASON:

		break;

	case STATE::TAG:
		tag_->Update();
		break;

	case STATE::CREDIT:
		credit_->Update();
		break;

	case STATE::NONE:
		MenuUpdate();
		break;

	default:
		break;
	}

	//キャラクターの更新
	player_->Update();

	step_ += SceneManager::GetInstance().GetDeltaTime() * SceneManager::DEFAULT_FPS;

	//落ちてくるブロックの処理
	if(static_cast<int>(step_) % 100 == 0)
	{
		BlockBase* block = GetValidBlock();

		//爆発の生成
		block->Create();
	}

	//ブロックの処理
	for (auto block : blocks_)
	{
		block->Update();

		if (block->IsDelete())
		{
			block->Release();
		}
	}

}

void MenuScene::Draw(void)
{
	//背景の描画
	scroll_->Draw();

	//ブロックの描画
	for (auto block : blocks_)
	{
		block->Draw();
	}

	switch (state_)
	{
	case STATE::SELECT:
		TextBoxDraw();
		challenge_->Draw();
		PointDraw();
		text_->ChallengeText();
		break;

	case STATE::MANYUAL:
		manual_->Draw();
		break;

	case STATE::MARASON:
		break;

	case STATE::TAG:
		tag_->Draw();
		break;

	case STATE::CREDIT:
		credit_->Draw();
		break;

	case STATE::NONE:
		TextBoxDraw();
		text_->MenuText();
		text_->NewRecodeDraw();
		PointDraw();
		break;

	default:
		break;
	}

	if (state_ != STATE::CREDIT) 
{ 
		text_->BottanUIDraw();
		player_->Draw();
	}
}

void MenuScene::Release(void)
{
	for (auto block : blocks_)
	{
		block->Release();
	}
	credit_->Release();
	scroll_->Release();
	player_->Release();
	text_->Release();
	tag_->Release();
	manual_->Release();
	challenge_->Release();
}

void MenuScene::Load(void)
{
	imgBack_ = LoadGraph((Application::PATH_IMAGE + "StageSelect/Brich.png").c_str()); 
	imgPoint_ = LoadGraph((Application::PATH_IMAGE + "StageSelect/Point.png").c_str());
}

void MenuScene::Reset(void)
{
	//スティック用判定
	isStick_ = false;

	//選択しているステート初期状態
	sleState_ = STATE::MARASON;

	//初期状態
	state_ = STATE::NONE;

	//メニューカウント
	menuCnt_ = static_cast<int>(sleState_);

	//ポイントの初期座標
	pointPos_ = { 480 ,225 };
}

void MenuScene::SetBackImage()
{
	//背景画像のサイズ
	Vector2 imgBackSize = { BRICH_SIZE_X, BRICH_SIZE_Y };

	//画像描画数
	int drawNum = 3;

	//スクロールスピード
	float speed = 0.3;

	//背景用の読み込み
	scroll_ = new Scroll;
	scroll_->Init(imgBack_, imgBackSize, drawNum, speed);
}

void MenuScene::MenuUpdate()
{
	auto& ins = InputManager::GetInstance();
	int stickY = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;
	auto& snd = SoundManager::GetInstance();

	//カウントのバックアップを保持
	STATE preState = sleState_;

	//ステージの選択処理
	if (ins.IsTrgDown(KEY_INPUT_UP) || (stickY < 0 && !isStick_))
	{
		menuCnt_--; TextReset();
		isStick_ = true;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN) || (stickY > 0 && !isStick_))
	{
		menuCnt_++; TextReset(); 
		isStick_ = true;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}

	//ステージ選択の制限
	if (menuCnt_ < 0) { menuCnt_ = static_cast<int>(STATE::MANYUAL); }
	if (menuCnt_ > static_cast<int>(STATE::MANYUAL)) { menuCnt_ = 0; }

	//数値から変換
	sleState_ = static_cast<STATE>(menuCnt_);

	//状態遷移
	if (ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{ 
		//ステートの変更
		state_ = sleState_;

		//テキストリセット
		TextReset(); 

		//キャラクターの退出
		SetPlayerState(MenuPlayer::MOVE_STATE::EXIT);

		//効果音再生
		if (state_ == STATE::MARASON) 
		{ 
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SCENE_CHANGE));
			snd.StopBgmSound(SoundManager::BGM::MENU);
		}
		else { snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_DECIDE)); }
	}
	if (ins.IsTrgDown(KEY_INPUT_RETURN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_CANCEL));
		snd.StopBgmSound(SoundManager::BGM::MENU);
	}

	//ポイント座標の設定
	for (int i = 0; i < static_cast<int>(STATE::NONE); i++)
	{
		if(i == static_cast<int>(sleState_))
		{
			int fontIntevel = Text::FONT_SIZE * i * 1.5;
			pointPos_ = { text_->GetMenuTextSize(i) * Text::FONT_SIZE,
						  Text::MENU_FIRST_POS_Y + fontIntevel + 80};
			
		}
	}

	//ステートがマラソンの時、シーンを切り替える
	if (state_ == STATE::MARASON)
	{
		ChangeGameScene(Data::LEVEL::MARASON);
	}
	if (state_ == STATE::TAG)
	{
		state_ = STATE::NONE;
	}

	//スティックの判定を戻す
	if (stickY == 0)
	{
		isStick_ = false;
	}
}

void MenuScene::PointDraw()
{
	DrawRotaGraph(pointPos_.x,
		pointPos_.y,
		1.0f,
		0.0f,
		imgPoint_,
		true);
}

void MenuScene::TextBoxDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	//テキスト描画背景(黒)
	DrawBox(
		0,
		Application::SCREEN_SIZE_Y - 160,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0x000000,
		true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MenuScene::TextReset()
{
	text_->Reset();
}

void MenuScene::SetPointPos(Vector2 pos)
{
	pointPos_ = pos;
}

void MenuScene::SetPlayerState(MenuPlayer::MOVE_STATE state)
{
	player_->SetState(state);
}

MenuScene::STATE MenuScene::GetMenuState()
{
	return state_;
}

void MenuScene::ChangeGameScene(Data::LEVEL level)
{
	//ステージデータを送る
	switch (level)
	{
	case Data::LEVEL::LEVEL1:
		Data::GetInstance().ChangeLevelData(Data::LEVEL::LEVEL1);
		break;

	case Data::LEVEL::LEVEL2:
		Data::GetInstance().ChangeLevelData(Data::LEVEL::LEVEL2);
		break;

	case Data::LEVEL::LEVEL3:
		Data::GetInstance().ChangeLevelData(Data::LEVEL::LEVEL3);
		break;

	case Data::LEVEL::LEVEL4:
		Data::GetInstance().ChangeLevelData(Data::LEVEL::LEVEL4);
		break;

	case Data::LEVEL::LEVEL5:
		Data::GetInstance().ChangeLevelData(Data::LEVEL::LEVEL5);
		break;

	case Data::LEVEL::LEVEL6:
		Data::GetInstance().ChangeLevelData(Data::LEVEL::LEVEL6);
		break;

	case Data::LEVEL::MARASON:
		Data::GetInstance().ChangeLevelData(Data::LEVEL::MARASON);
		break;

	default:
		break;
	}

	//シーンを変える
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
}

BlockBase* MenuScene::GetValidBlock()
{
	BlockBase* block = new BlockShower();
	blocks_.push_back(block);
	return block;
}

void MenuScene::SetState(STATE state)
{
	state_ = state;
}

MenuScene::STATE MenuScene::GetMenuSetState()
{
	return sleState_;
}

Data::LEVEL MenuScene::GetChallengeState()
{
	return challenge_->GetChallengeData();
}