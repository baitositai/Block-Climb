#include <Dxlib.h>
#include "../../Application.h"
#include "../../Common/Scroll.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Common/Data.h"
#include "../../Scene/MenuScene.h"
#include "Challenge.h"

Challenge::Challenge(void)
{
}

Challenge::~Challenge(void)
{
}

void Challenge::Init(MenuScene* parent)
{
	menu_ = parent;

	Load();
	
	//座標の設定
	pointPos_ = { 0,0 };

	//色の設定
	sleCnt_ = { 0,0 };

	//スティック判定
	isStick_ = false;
}

void Challenge::Update(void)
{
	Data::LEVEL preData = sleData_;
	auto& ins = InputManager::GetInstance();
	auto& snd = SoundManager::GetInstance();
	int stickX = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
	int stickY = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;

	//ステージを選ぶ処理	
	if (ins.IsTrgDown(KEY_INPUT_RIGHT) || (stickX > 0 && !isStick_))
	{
		isStick_ = true;
		sleCnt_.x++;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}
	if (ins.IsTrgDown(KEY_INPUT_LEFT) || (stickX < 0 && !isStick_))
	{ 
		sleCnt_.x--; 
		isStick_ = true;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}
	if (ins.IsTrgDown(KEY_INPUT_UP) || (stickY < 0 && !isStick_)) 
	{
		sleCnt_.y--;
		isStick_ = true;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN) || (stickY > 0 && !isStick_))
	{ 
		sleCnt_.y++; 
		isStick_ = true;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}

	//ステージ選択の制限
	if (sleCnt_.x < 0) { sleCnt_.x = STAGE_X - 1; }
	if (sleCnt_.x > STAGE_X - 1) { sleCnt_.x = 0; }
	if (sleCnt_.y < 0) { sleCnt_.y = STAGE_Y - 1; }
	if (sleCnt_.y > STAGE_Y - 1) { sleCnt_.y = 0; }

	//数値から変換
	sleData_ = static_cast<Data::LEVEL>(sleCnt_.x + sleCnt_.y * STAGE_X);

	//決定
	if (ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		menu_->ChangeGameScene(sleData_);
		snd.StopBgmSound(SoundManager::BGM::MENU);
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SCENE_CHANGE));
	}

	//メニューへ戻る
	if (ins.IsTrgDown(KEY_INPUT_RETURN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		menu_->SetState(MenuScene::STATE::NONE); 
		menu_->SetPlayerState(MenuPlayer::MOVE_STATE::ADMISSION);
		menu_->TextReset(); 
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_CANCEL));
	}

	//テキストデータの切り替え
	if (sleData_ != preData)
	{
		menu_->TextReset();
	}

	//スティック判定を戻す
	if (stickX == 0 && stickY == 0)
	{
		isStick_ = false;
	}
}

void Challenge::Draw(void)
{
	for (int i = 0; i < static_cast<int>(Data::LEVEL::MAX); i++)
	{
		//描画位置の設定
		Vector2 pos;
		if (i < static_cast<int>(Data::LEVEL::MAX) / 2)
		{
			pos = { Application::SCREEN_SIZE_X / 4 * (i + 1),
				   Application::SCREEN_SIZE_Y / 8 * 2 };
		}
		if (i >= static_cast<int>(Data::LEVEL::MAX) / 2)
		{
			pos = { Application::SCREEN_SIZE_X / 4 * (i - static_cast<int>(Data::LEVEL::MAX) / 2 + 1),
				   Application::SCREEN_SIZE_Y / 8 * 5 };
		}
		if (i != static_cast<int>(sleData_))
		{
			//揺らす用変数
			float amplitude = 0.5f;// 揺らす周波数（Hz）
			float frequency = 10.0f;// 揺らす振幅（ピクセル）

			//上下揺らしの処理
			pos = AsoUtility::SinShake(pos, amplitude, frequency);
		}

		//画像の描画
		DrawRotaGraph(pos.x,
			pos.y,
			1.2f,
			0.0f,
			imgSle_[i],
			true);

		//ポイント座標の設定
		if (i == static_cast<int>(sleData_))
		{
			//座標設定
			Vector2 pointPos = { pos.x + 75,
								 pos.y + 75 };
			menu_->SetPointPos(pointPos);
			//描画はMenuSceneにて
		}
	}
}

void Challenge::Release(void)
{
	DeleteGraph(imgPoint_);
	for (int i = 0; i < static_cast<int>(Data::LEVEL::MAX); i++)
	{
		DeleteGraph(imgSle_[i]);
	}
	
}

void Challenge::Load()
{
	//画像読み込み
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL1)] = LoadGraph((Application::PATH_IMAGE + "StageSelect/Stage1.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL2)] = LoadGraph((Application::PATH_IMAGE + "StageSelect/Stage2.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL3)] = LoadGraph((Application::PATH_IMAGE + "StageSelect/Stage3.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL4)] = LoadGraph((Application::PATH_IMAGE + "StageSelect/Stage4.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL5)] = LoadGraph((Application::PATH_IMAGE + "StageSelect/Stage5.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL6)] = LoadGraph((Application::PATH_IMAGE + "StageSelect/Stage6.png").c_str());
}

Data::LEVEL Challenge::GetChallengeData()
{
	return sleData_;
}
