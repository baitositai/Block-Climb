#include <DxLib.h>
#include "Manager/InputManager.h"
#include "Manager/SceneManager.h"
#include "Manager/SoundManager.h"
#include "Common/Data.h"
#include "Application.h"

Application* Application::instance_ = nullptr;

const std::string Application::FONT_DOT = "�x�X�g�e��DOT";
const std::string Application::FONT_BOKUTATI = "�ڂ������̃S�V�b�N";

const std::string Application::PATH_MOVIE = "Data/Movie/";
const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_CSV = "Data/Csv/";
const std::string Application::PATH_FONT = "Data/Font/";
const std::string Application::PATH_SOUND = "Data/Sound/";
const std::string Application::PATH_BLOCK = "Data/Image/Block/";

void Application::CreateInstance(void)
{
	//�C���X�^���X������Ƃ�
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
	// �A�v���P�[�V�����̏����ݒ�
	SetWindowText("��c����_BLOCK_CLIMB");

	// �E�B���h�E�T�C�Y
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, COLOR_BIT_DEPTH);
	ChangeWindowMode(true);

	// DxLib�̏�����
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		isInitFail_ = true;
		return;
	}

	// �L�[���䏉����
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();
	Data::CreateInstance();

	// �V�[���Ǘ�������	
	SoundManager::CreateInstance();
	SceneManager::CreateInstance();

	// �t�H���g������
	// �t�H���g���V�X�e���ɓo�^
	fontPath_[0] = "�x�X�g�e��DOT.otf";
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

	// �Q�[�����[�v
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
	// �t�H���g�o�^����
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

	// DxLib�I��
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
