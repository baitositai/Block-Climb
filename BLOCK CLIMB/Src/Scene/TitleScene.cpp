#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "TitleScene.h"
#include "../Object/Title/TitlePlayer.h"
#include "../Object/Title/TitleBackGround.h"
#include "../Object/Title/TitleGround.h"
#include "../Object/Game/PlayerBase.h"
#include "../Object/Game/Block/BlockBase.h"
#include "../Object/Game/Block/BlockShower.h"
#include "../Object/Game/RabbitText/RabbitTitle.h"
#include "../Object/FadeText.h"

TitleScene::TitleScene(void)
{
	back_ = nullptr;
	credit_ = nullptr;
	fadetext_ = nullptr;
	font_ = 0;
	ground_ = nullptr;
	imgLogo_ = 0;
	isText_ = false;
	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++) { player_[i] = nullptr; }
	rabbit_ = nullptr;
	step_ = 0;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	//画像読み込み
	imgLogo_ = LoadGraph((Application::PATH_IMAGE + "UI/TitleLogo.png").c_str());

	//キャラクターの読み込み
	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++)
	{
		player_[i] = new TitlePlayer;
		player_[i]->Init(this, static_cast<PlayerBase::PLAYER_TYPE>(i));
	}

	//背景読み込み
	back_ = new TitleBackGround;
	back_->Init(this);

	//地面読み込み
	ground_ = new TitleGround;
	ground_->Init();

	//フェードテキスト
	fadetext_ = new FadeText;
	SetText();

	//ウサギ読み込み
	rabbit_ = new RabbitTitle;
	rabbit_->Init();

	SoundManager::GetInstance().PlayBgmSound(SoundManager::BGM::TITLE, 70, true);
}

void TitleScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT);
	int stickX = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;

	//画面切り替えの処理
	if (ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		auto& snd = SoundManager::GetInstance();
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU,static_cast<int>(SoundManager::MENU::TITLE_SCENE_CHANGE));
		snd.StopBgmSound(SoundManager::BGM::TITLE);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::MENU);
		
	}
	//プレイヤー達の更新処理
	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++)
	{
		player_[i]->Update();
	}
	//背景処理
	back_->Update();
	//テキスト処理
	fadetext_->Update();
	rabbit_->Update();

	//テキストのシェイク処理
	Vector2 pos = textPos_;
	float amplitude = 0.3f;// 揺らす周波数（Hz）
	float frequency = 5.0f;// 揺らす振幅（ピクセル）

	//上下揺らしの処理
	pos = AsoUtility::SinShake(pos, amplitude, frequency);
	fadetext_->SetPos(pos);

	if (isText_)
	{
		step_ += SceneManager::GetInstance().GetDeltaTime() * SceneManager::DEFAULT_FPS;

		//落ちてくるブロックの処理
		if (static_cast<int>(step_) % 200 == 0)
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
}

void TitleScene::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
	back_->Draw();
	//ブロックの描画
	for (auto block : blocks_)
	{
		block->Draw();
	}
	ground_->Draw();

	Vector2 pos = { Application::SCREEN_SIZE_X / 2 - LOGO_SIZE_X / 2,
				   Application::SCREEN_SIZE_Y / 2 - 335 };

	DrawGraph(pos.x,pos.y,imgLogo_,true);	
	RabbitDraw();

	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++)
	{
		player_[i]->Draw();
	}
	if (isText_)
	{
		fadetext_->Draw();
	}
}

void TitleScene::Release(void)
{
	for (auto block : blocks_)
	{
		block->Release();
	}
	rabbit_->Release();
	DeleteFontToHandle(font_);
	fadetext_->Release();
	ground_->Release();
	back_->Release();
	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++)
	{
		player_[i]->Release();
	}
	DeleteGraph(imgLogo_);
}

void TitleScene::SetText()
{
	font_ = CreateFontToHandle("ベストテンDOT", FONT_SIZE, 6);
	int color = 0xffffff;
	int fontSize = 32;
	std::string text = "PLEASE SPACE OR B BUTTON !";
	textPos_ = { (Application::SCREEN_SIZE_X / 2) - (static_cast<int>(text.length() * fontSize) / 4),
					Application::SCREEN_SIZE_Y / 5 * 4, };
	isText_ = false;

	fadetext_->SetText(font_, color, fontSize, textPos_, text);
}

void TitleScene::SetIsText(bool value)
{
	isText_ = value;
}

void TitleScene::RabbitDraw()
{
	Vector2 pos = { 30, Application::SCREEN_SIZE_Y - RabbitText::RABBIT_SIZE_Y };
	rabbit_->RabbitDraw(pos);

	pos = { 40 + RabbitText::RABBIT_SIZE_X, Application::SCREEN_SIZE_Y - RabbitText::SPEECH_SIZE_Y + 5};
	rabbit_->SpeechDraw(pos);

	pos = { 70 + RabbitText::RABBIT_SIZE_X , Application::SCREEN_SIZE_Y - RabbitText::RABBIT_SIZE_Y  + 80};
	rabbit_->TextDraw(pos);
}

BlockBase* TitleScene::GetValidBlock()
{
	BlockBase* block = new BlockShower();
	blocks_.push_back(block);
	return block;
}