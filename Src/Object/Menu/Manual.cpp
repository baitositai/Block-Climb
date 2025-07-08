#include <Dxlib.h>
#include "../../Application.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Scene/MenuScene.h"
#include "Manual.h"

Manual::Manual(void)
{
	for (int i = 0; i < MANUAL_TYPE; i++) { imgManual_[i] = -1; }
	isStick_ = false;
	manuSle_ = -1;
	menu_ = nullptr;
}

Manual::~Manual(void)
{
}

void Manual::Init(MenuScene* parent)
{
	menu_ = parent;
	manuSle_ = 0;

	imgManual_[0] = LoadGraph((Application::PATH_IMAGE + "Manual/マニュアル1.png").c_str());
	imgManual_[1] = LoadGraph((Application::PATH_IMAGE + "Manual/マニュアル2.png").c_str());
	imgManual_[2] = LoadGraph((Application::PATH_IMAGE + "Manual/マニュアル3.png").c_str());
	imgManual_[3] = LoadGraph((Application::PATH_IMAGE + "Manual/マニュアル4.png").c_str());
}

void Manual::Update(void)
{
	auto& ins = InputManager::GetInstance();
	auto& snd = SoundManager::GetInstance();
	int stickX = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;

	//メニューへ戻る
	if (ins.IsTrgDown(KEY_INPUT_RETURN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		menu_->SetState(MenuScene::STATE::NONE);
		menu_->SetPlayerState(MenuPlayer::MOVE_STATE::ADMISSION);
		manuSle_ = 0;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_CANCEL));
	}

	//切り替え
	if (ins.IsTrgDown(KEY_INPUT_RIGHT) ||
		(stickX > 0 && !isStick_))
	{
		isStick_ = true;
		manuSle_++;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
		if (manuSle_ >= MANUAL_TYPE)
		{
			manuSle_ = 0;
		}
	}
	else if (ins.IsTrgDown(KEY_INPUT_LEFT) ||
		(stickX < 0 && !isStick_))
	{
		isStick_ = true;
		manuSle_--;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
		if (manuSle_ < 0)
		{
			manuSle_ = MANUAL_TYPE - 1;
		}
	}

	//スティック判定を戻す
	if (stickX == 0)
	{
		isStick_ = false;
	}
}

void Manual::Draw(void)
{
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2,
		1.0f,
		0.0f,
		imgManual_[manuSle_],
		true,
		false);
}

void Manual::Release(void)
{
	for (int i = 0; i < MANUAL_TYPE; i++)
	{
		DeleteGraph(imgManual_[i]);
	}
}
