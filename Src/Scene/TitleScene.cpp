#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Common/Fader.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Object/Title/TitlePlayer.h"
#include "../Object/Title/TitleGround.h"
#include "../Object/Game/PlayerBase.h"
#include "../Object/Game/Block/BlockBase.h"
#include "../Object/Game/Block/BlockShower.h"
#include "../Object/Game/RabbitText/RabbitTitle.h"
#include "../Object/Game/BackGround.h"
#include "../Object/FadeText.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
	back_ = nullptr;
	fadeText_ = nullptr;
	font_ = 0;
	ground_ = nullptr;
	imgLogo_ = 0;
	isText_ = false;
	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++) { player_[i] = nullptr; }
	rabbit_ = nullptr;
	blockCreateCnt_ = 0;
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
	back_ = new BackGround;
	back_->Init();

	//地面読み込み
	ground_ = new TitleGround;
	ground_->Init();

	//ウサギ読み込み
	rabbit_ = new RabbitTitle;
	rabbit_->Init();

	//BGMの再生
	SoundManager::GetInstance().PlayBgmSound(SoundManager::BGM::TITLE, BGM_VOLUME, true);
	
	//テキストの初期設定
	InitText();

	//ブロックの生成カウントを設定
	blockCreateCnt_ = BLOCK_CREATE_CNT;
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
		//効果音再生
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU,static_cast<int>(SoundManager::MENU::TITLE_SCENE_CHANGE));
		//BGM停止
		snd.StopBgmSound(SoundManager::BGM::TITLE);
		//シーンを遷移
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
	fadeText_->Update();

	//ウサギ処理
	rabbit_->Update();

	//テキスト関係の更新処理
	TextUpdate();

	//ブロック関係の更新処理
	BlockUpdate();
	
}

void TitleScene::Draw(void)
{
	//アルファ値を設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fader::FADE_MAX);

	//背景
	back_->Draw();

	//ブロックの描画
	for (auto & block : blocks_)
	{
		block->Draw();
	}

	//地面
	ground_->Draw();

	//ロゴ
	DrawGraph(LOGO_POS_X, LOGO_POS_Y, imgLogo_, true);

	//ウサギ
	RabbitDraw();

	//プレイヤー描画
	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++)
	{
		player_[i]->Draw();
	}

	//フェードテキスト
	if (isText_)
	{
		fadeText_->Draw();
	}
}

void TitleScene::Release(void)
{
	DeleteFontToHandle(font_);
	DeleteGraph(imgLogo_);

	for (BlockBase* block : blocks_) {
		if (block) 
		{
			block->Release();
			delete block;
		}
	}
	blocks_.clear();
	rabbit_->Release();
	delete rabbit_;
	fadeText_->Release();
	delete fadeText_;
	ground_->Release();
	delete ground_;
	back_->Release();
	delete back_;
	for (auto* player : player_)
	{
		if (player)
		{
			player->Release();
			delete player;
		}
	}
}

void TitleScene::SetIsText(bool value)
{
	isText_ = value;
}

void TitleScene::RabbitDraw()
{
	Vector2 pos = { RAB_POS_X,RAB_POS_Y };
	rabbit_->RabbitDraw(pos);

	pos = { RAB_SPEECH_POS_X, RAB_SPEECH_POS_Y};
	rabbit_->SpeechDraw(pos);

	pos = { RAB_TEXT_POS_X , RAB_TEXT_POS_Y};
	rabbit_->TextDraw(pos);
}

BlockBase* TitleScene::GetValidBlock()
{
	BlockBase* block = new BlockShower();
	blocks_.push_back(block);
	return block;
}

Vector2 TitleScene::GetTitlePosMes(const std::string & mes)
{
	return { Application::SCREEN_SIZE_X / 2 - static_cast<int>(mes.length() * TEXT_FONT_SIZE / 4),
	MES_POS_Y };
}

void TitleScene::InitText()
{
	//フォント
	font_ = CreateFontToHandle("ベストテンDOT", FONT_SIZE, TEXT_FONT_THICK);
	
	//メッセージ
	const std::string mes = "PLEASE SPACE OR B BUTTON !";

	//座標位置
	textPos_ = GetTitlePosMes(mes);

	//テキスト非表示
	isText_ = false;

	//フェードテキスト
	fadeText_ = new FadeText();

	//設定
	fadeText_->SetText(font_, TEXT_COLOR, TEXT_FONT_SIZE, textPos_, mes);
}

void TitleScene::TextUpdate()
{
	//テキストのシェイク処理
	Vector2 pos = textPos_;

	//上下揺らしの処理
	pos = AsoUtility::SinShake(pos, AMPLITUDE, FREQUENCY);
	fadeText_->SetPos(pos);
}

void TitleScene::BlockUpdate()
{
	//条件のテキストが表示されてないときは処理を行わない
	if (!isText_)
	{
		return;
	}

	//ステップ更新
	blockCreateCnt_ -= SceneManager::GetInstance().GetDeltaTime();
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
