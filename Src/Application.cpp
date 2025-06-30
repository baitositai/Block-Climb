#include <DxLib.h>
#include "Manager/InputManager.h"
#include "Manager/SceneManager.h"
#include "Manager/SoundManager.h"
#include "Common/Data.h"
#include "Application.h"

Application* Application::instance_ = nullptr;

const std::string Application::FONT_DOT = "ベストテンDOT";
const std::string Application::FONT_BOKUTATI = "ぼくたちのゴシック";

const std::string Application::PATH_MOVIE = "Data/Movie/";
const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_CSV = "Data/Csv/";
const std::string Application::PATH_FONT = "Data/Font/";
const std::string Application::PATH_SOUND = "Data/Sound/";
const std::string Application::PATH_BLOCK = "Data/Image/Block/";

void Application::CreateInstance(void)
{
	//インスタンスがあるとき
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	instance_->Init();
}

Application& Application::GetInstance(void)
{
	return *instance_;
}

void Application::Init(void)
{
	// アプリケーションの初期設定
	SetWindowText("坂田桃侍_BLOCK_CLIMB");

	// ウィンドウサイズ
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, COLOR_BIT_DEPTH);
	ChangeWindowMode(true);

	// DxLibの初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		isInitFail_ = true;
		return;
	}

	// キー制御初期化
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();
	Data::CreateInstance();

	// シーン管理初期化	
	SoundManager::CreateInstance();
	SceneManager::CreateInstance();

	// フォント初期化
	// フォントをシステムに登録
	fontPath_[0] = "ベストテンDOT.otf";
	fontPath_[1] = "bokutachi.otf";
	for (int i = 0; i < FONT_TYPES; i++)
	{
		if (AddFontResourceEx(
			(Application::PATH_FONT + fontPath_[i]).c_str(),
			FR_PRIVATE,
			NULL)
			== -1)
		{
			return;
		}
	}
}

void Application::Run(void)
{

	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& soundManager = SoundManager::GetInstance();

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		inputManager.Update();
		sceneManager.Update();

		sceneManager.Draw();

		ScreenFlip();

	}

}

void Application::Release(void)
{
	// フォント登録解除
	for (int i = 0; i < FONT_TYPES; i++)
	{
		if (RemoveFontResourceEx(
			(Application::PATH_FONT + fontPath_[i]).c_str(),
			FR_PRIVATE,
			NULL)
			== -1)
		{
			return;
		}
	}

	// DxLib終了
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}
}

bool Application::IsInitFail(void) const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void) const
{
	return isReleaseFail_;
}

Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
}

Application::~Application(void)
{
	delete instance_;
}
