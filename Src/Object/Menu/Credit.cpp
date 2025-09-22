#include <DxLib.h>
#include "Credit.h"
#include "../../Application.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Scene/MenuScene.h"

Credit::Credit()
{
	menu_ = nullptr;
	movie_ = 0;
	isPlay_ = false;
}

Credit::~Credit()
{
}

void Credit::Init(MenuScene* parent)
{
	menu_ = parent;

	//ìÆâÊì«Ç›çûÇ›
	movie_ = LoadGraph((Application::PATH_MOVIE + "Credit.mp4").c_str());
}

void Credit::Update()
{
	auto& ins = InputManager::GetInstance();
	auto& snd = SoundManager::GetInstance();

	if (menu_->GetMenuState() == MenuScene::STATE::CREDIT &&
		!isPlay_)
	{
		snd.StopBgmSound(SoundManager::BGM::MENU);
		PlayMovieToGraph(movie_);
		isPlay_ = true;
	}

	//ÉÅÉjÉÖÅ[Ç÷ñﬂÇÈ
	if (ins.IsTrgDown(KEY_INPUT_RETURN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN) ||
		GetMovieStateToGraph(movie_) == 0)
	{
		PauseMovieToGraph(movie_);
		SeekMovieToGraph(movie_, 0);
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_CANCEL));
		snd.PlayBgmSound(SoundManager::BGM::MENU, MOVIE_VOLUME, false);
		menu_->SetState(MenuScene::STATE::NONE);
		menu_->SetPlayerState(MenuPlayer::MOVE_STATE::ADMISSION);
		isPlay_ = false;
	}
}

void Credit::Draw()
{
	DrawExtendGraph(0, 0,Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, movie_, false);
}

void Credit::Release()
{
	DeleteGraph(movie_);
}
