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

Challenge::Challenge()
{
	imgPoint_ = 0;
	for (int i = 0; i < static_cast<int>(Data::LEVEL::MAX); i++) { imgSle_[i] = 0; }
	pointPos_ = { 0,0 };
	sleCnt_ = { 0,0 };
	scrollCnt_ = 0;
	sleData_ = Data::LEVEL::MAX;
	isStick_ = false;
	menu_ = nullptr;
}

Challenge::~Challenge()
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

void Challenge::Update()
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

void Challenge::Draw()
{
	for (int i = 0; i < static_cast<int>(Data::LEVEL::MAX); i++)
	{
		//描画位置の設定
		Vector2 pos;
		if (i < static_cast<int>(Data::LEVEL::MAX) / 2)
		{
			pos = { SLE_UIS_UP_X * (i + 1),
				   SLE_UIS_UP_Y };
		}
		else
		{
			pos = { SLE_UIS_DOWN_X * (i - static_cast<int>(Data::LEVEL::MAX) / 2 + 1),
				   SLE_UIS_DOWN_Y };
		}

		//選択していないのを揺らす
		if (i != static_cast<int>(sleData_))
		{
			//上下揺らしの処理
			pos = AsoUtility::SinShake(pos, AMPLITUDE, FREQUENCY);
		}

		//画像の描画
		DrawRotaGraph(pos.x,
			pos.y,
			SLE_IMG_RATE,
			0.0f,
			imgSle_[i],
			true);

		//ポイント座標の設定
		if (i == static_cast<int>(sleData_))
		{
			//座標設定
			Vector2 pointPos = { pos.x + POINT_LOCAL_POS,
								 pos.y + POINT_LOCAL_POS };
			menu_->SetPointPos(pointPos);
			//描画はMenuSceneにて
		}
	}
}

void Challenge::Release()
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
	std::string path = Application::PATH_IMAGE + "StageSelect/";
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL1)] = LoadGraph((path + "Stage1.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL2)] = LoadGraph((path + "Stage2.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL3)] = LoadGraph((path + "Stage3.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL4)] = LoadGraph((path + "Stage4.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL5)] = LoadGraph((path + "Stage5.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL6)] = LoadGraph((path + "Stage6.png").c_str());
}

Data::LEVEL Challenge::GetChallengeData()
{
	return sleData_;
}
