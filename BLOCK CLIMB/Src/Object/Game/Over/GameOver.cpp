#include <DxLib.h> 
#include "../../../Utility/AsoUtility.h"
#include "../../../Application.h"
#include "../../../Manager/InputManager.h"
#include "../../../Scene/GameScene.h"
#include "GameOver.h"

GameOver::GameOver(void)
{
	/*imgOver_ = 0;*/
}

GameOver::~GameOver(void)
{
}

void GameOver::Init(GameScene* parent)
{
	gameScene_ = parent;

	//‰æ‘œ“Ç‚İ‚İ
	imgOver_ = LoadGraph((Application::PATH_IMAGE + "UI/GameOver.png").c_str());

	pos_.x = Application::SCREEN_SIZE_X / 2 - SIZE_X / 2;
	pos_.y = Application::SCREEN_SIZE_Y / 2 - SIZE_Y / 2;
}

void GameOver::Update(void)
{
	InputManager& ins = InputManager::GetInstance();

	//À•W‚Ìİ’è
	pos_.x = Application::SCREEN_SIZE_X / 2 - SIZE_X / 2;
	pos_.y = Application::SCREEN_SIZE_Y / 2 - SIZE_Y / 2;

	//—h‚ç‚·—p•Ï”
	float amplitude = 1.0f;// —h‚ç‚·ü”g”iHzj
	float frequency = 10.0f;// —h‚ç‚·U•iƒsƒNƒZƒ‹j

	//ã‰º—h‚ç‚µ‚Ìˆ—
	pos_ = AsoUtility::SinShake(pos_, amplitude, frequency);

}

void GameOver::Draw(void)
{
	//‰æ‘œ‚Ì•`‰æ
	DrawGraph(pos_.x, pos_.y, imgOver_, true);
}

void GameOver::Release(void)
{
	DeleteGraph(imgOver_);
}