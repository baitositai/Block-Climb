#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Scene/GameScene.h"
#include "SceneSelect.h"

SceneSelect::SceneSelect()
{
	cnt_ = 0;
	font_ = 0;
	game_ = nullptr;
	imgNewRecode_ = 0;
	imgBoard_ = 0;
	imgPause_ = 0;
	isNewRecode_ = false;
	isStick_ = false;
	size_ = 0.0f;
	sleFont_ = 0;
	state_ = CHANGE::MAX;
}

SceneSelect::~SceneSelect()
{
}

void SceneSelect::Init(GameScene* parent)
{
	//インスタンス取得
	game_ = parent;

	//画像読み込み
	imgPause_ = LoadGraph((Application::PATH_IMAGE + "UI/Pause.png").c_str());
	imgBoard_ = LoadGraph((Application::PATH_IMAGE + "UI/Board.png").c_str());
	imgNewRecode_ = LoadGraph((Application::PATH_IMAGE + "UI/NewRecode.png").c_str());

	//初期化処理
	Reset();

	//テキスト設定
	SetText();

	//フォント設定
	SetFont();
}

void SceneSelect::Reset()
{
	size_ = 0;
	cnt_ = 0;
	state_ = static_cast<CHANGE>(cnt_);
	isNewRecode_ = false;
	isStick_ = false;
}

void SceneSelect::Update()
{
	//板の拡大処理
	if (size_ <= BOARD_SIZE_MAX) { BoardExpansion(); }
	//選択処理
	else { Select(); }
}

void SceneSelect::Draw()
{
	//板の描画
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
				Application::SCREEN_SIZE_Y / 2, 
				size_,
				0.0f,
				imgBoard_,
				true);

	//ポーズUIの描画
	if (game_->GetState() == GameScene::STATE::PAUSE)
	{
		Vector2 pPos = { Application::SCREEN_SIZE_X / 2,
						Application::SCREEN_SIZE_Y / 2 - 200};

		float amplitude = 0.3f;// 揺らす周波数（Hz）
		float frequency = 5.0f;// 揺らす振幅（ピクセル）

		pPos = AsoUtility::SinShake(pPos, amplitude, frequency);

		DrawRotaGraph(pPos.x,
			pPos.y,
			size_,
			0.0f,
			imgPause_,
			true);
	}

	if (size_ >= BOARD_SIZE_MAX)
	{
		for (int i = 0; i < static_cast<int>(CHANGE::MAX); i++)
		{
			int fontIntevel = FONT_SIZE * i * 1.7;
			int color = 0xffffff;
			int fontType = font_;

			//座標の設定
			Vector2 pos = { (Application::SCREEN_SIZE_X / 2) - (static_cast<int>(text_[i].length() * FONT_SIZE) / 4),
							250 + fontIntevel };

			//フォントの設定
			if (i == static_cast<int>(state_))
			{
				color = 0x00ffff;
				fontType = sleFont_;
			}
			//選択テキストの表示
			DrawStringToHandle(pos.x, pos.y, text_[i].c_str(), color, fontType);
		}
	}
	
}

void SceneSelect::Release()
{
	DeleteFontToHandle(sleFont_);
	DeleteFontToHandle(font_);
	DeleteGraph(imgNewRecode_);
	DeleteGraph(imgBoard_);
	DeleteGraph(imgPause_);
}

void SceneSelect::SetText()
{
	text_[static_cast<int>(CHANGE::RETRY)] = "リトライ";
	text_[static_cast<int>(CHANGE::MENU)] = "メニューへ";
	text_[static_cast<int>(CHANGE::TITLE)] = "タイトルへ";
}

void SceneSelect::SetFont()
{
	font_ = CreateFontToHandle("ベストテンDOT", FONT_SIZE, 3);
	sleFont_ = CreateFontToHandle("ベストテンDOT", SELECT_FONT_SIZE, 3);
}

void SceneSelect::Select()
{
	InputManager& ins = InputManager::GetInstance();
	SoundManager& snd = SoundManager::GetInstance();
	int stickY = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;

	//カウントのバックアップを保持
	CHANGE preState = state_;

	//ステージの選択処理
	if (ins.IsTrgDown(KEY_INPUT_UP) || stickY < 0 && !isStick_) 
	{
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
		cnt_--; 
		isStick_ = true;
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN) || stickY > 0 && !isStick_) 
	{
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
		cnt_++; 
		isStick_ = true;
	}

	//ステージ選択の制限
	if (cnt_ < 0) { cnt_ = static_cast<int>(CHANGE::TITLE); }
	if (cnt_ >= static_cast<int>(CHANGE::MAX)) { cnt_ = 0; }

	//数値から変換
	state_ = static_cast<CHANGE>(cnt_);

	//状態遷移
	if (ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		snd.StopEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::GAME_OVER));
		Change();
	}

	if (stickY == 0) { isStick_ = false; }
}

void SceneSelect::BoardExpansion()
{
	//板の拡大
	size_ += EXPANSION_SPEED;
}

void SceneSelect::NewRecodeDraw()
{
	DrawRotaGraph(Application::SCREEN_SIZE_X / 4,
		Application::SCREEN_SIZE_Y / 5,
		size_,
		0.0f,
		imgNewRecode_,
		true,
		false);
}

void SceneSelect::SetIsNewRecode(bool value)
{
	isNewRecode_ = value;
}

bool SceneSelect::IsNewRecode()
{
	return isNewRecode_;
}

void SceneSelect::Change()
{
	auto& snd = SoundManager::GetInstance();
	switch (state_)
	{
	case CHANGE::RETRY:
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::TITLE_SCENE_CHANGE));
		game_->Retry();
		break;

	case CHANGE::MENU:
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::TITLE_SCENE_CHANGE));
		game_->ChangeScene(SceneManager::SCENE_ID::MENU);
		break;

	case CHANGE::TITLE:
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SCENE_CHANGE));
		game_->ChangeScene(SceneManager::SCENE_ID::TITLE);
		break;

	default:
		break;
	}	
	
	//初期化しとく
	Reset();
}