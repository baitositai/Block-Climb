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
	blockCreateCnt_ = 0.0f;
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
	InitBackImage();

	//bgmの再生
	SoundManager::GetInstance().PlayBgmSound(SoundManager::BGM::MENU, BGM_VOLUME, true);
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

	//ブロック更新処理
	BlockUpdate();

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
		text_->ButtonUIDraw();
		player_->Draw();
	}
}

void MenuScene::Release(void)
{
	DeleteGraph(imgPoint_);
	DeleteGraph(imgBack_);

	for (int i = 0; i < blocks_.size(); i++)
	{
		blocks_[i]->Release();
		delete blocks_[i];
	}
	credit_->Release();
	delete credit_;
	scroll_->Release();
	delete scroll_;
	player_->Release();
	delete player_;
	text_->Release();
	delete text_;
	tag_->Release();
	delete tag_;
	manual_->Release();
	delete manual_;
	challenge_->Release();
	delete challenge_;
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
	pointPos_ = GetPointPos(0);

	//ブロック生成カウント
	blockCreateCnt_ = BLOCK_CREATE_CNT;
}

void MenuScene::InitBackImage()
{
	//背景画像のサイズ
	Vector2 imgBackSize = { BRICH_SIZE_X, BRICH_SIZE_Y };

	//背景用の読み込み
	scroll_ = new Scroll;
	scroll_->Init(imgBack_, imgBackSize, BACK_DRAW_NUM, BACK_SCROLL_SPEED);
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
			//座標設定
			pointPos_ = GetPointPos(i);
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, TEXT_BOX_ALPHA);

	//テキスト描画背景(黒)
	DrawBox(
		0,
		Application::SCREEN_SIZE_Y - TEXT_BOX_SIZE_Y,
		TEXT_BOX_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0x000000,
		true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MenuScene::TextReset()
{
	text_->Reset();
}

void MenuScene::SetPointPos(const Vector2 pos)
{
	pointPos_ = pos;
}

void MenuScene::SetPlayerState(const MenuPlayer::MOVE_STATE state)
{
	player_->ChangeState(state);
}

MenuScene::STATE MenuScene::GetMenuState()
{
	return state_;
}

void MenuScene::ChangeGameScene(const Data::LEVEL level)
{
	//ゲームレベルを設定
	Data::GetInstance().ChangeLevelData(level);

	//シーンを変える
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
}

BlockBase* MenuScene::GetValidBlock()
{
	BlockBase* block = new BlockShower();
	blocks_.push_back(block);
	return block;
}

Vector2 MenuScene::GetPointPos(const int index)
{
	//描画用間隔
	int interval = static_cast<int>(Text::FONT_SIZE * index * 1.5f);	
	//Y座標微調整
	int addPosY = 80;
	return { text_->GetMenuTextSize(index) * Text::FONT_SIZE,
		Text::MENU_FIRST_POS_Y + interval + addPosY };
}

void MenuScene::BlockUpdate()
{
	//条件を満たす場合ブロックを生成
	if (blockCreateCnt_ <= 0.0f)
	{
		//カウントを戻す
		blockCreateCnt_ = BLOCK_CREATE_CNT;

		//ブロックを受け取る
		BlockBase* block = GetValidBlock();

		//ブロックを生成
		block->Create();
	}

	for (auto it = blocks_.begin(); it != blocks_.end(); )
	{
		//処理するブロックをコピー
		BlockBase* block = *it;

		//更新
		block->Update();

		//条件に達した場合
		if (block->IsDelete())
		{
			//解放して消す
			block->Release();
			//メモリ解放
			delete block;
			//配列からポインタを取り除く
			it = blocks_.erase(it);
		}
		else
		{
			//次のブロックへ
			++it;
		}
	}
}

void MenuScene::SetState(const STATE state)
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