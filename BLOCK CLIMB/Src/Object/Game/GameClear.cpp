#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/InputManager.h"
#include "../../Scene/GameScene.h"
#include "GameClear.h"

GameClear::GameClear(void)
{
}

GameClear::~GameClear(void)
{
}

void GameClear::Init(GameScene* parent)
{
	gameScene_ = parent;

	//‰æ‘œ“Ç‚İ‚İ
	imgClear_ = LoadGraph((Application::PATH_IMAGE + "UI/ClearUI.png").c_str());
}

void GameClear::Update(void)
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

void GameClear::Draw(void)
{
	//‰æ‘œ‚Ì•`‰æ
	DrawGraph(pos_.x, pos_.y, imgClear_, true);
}

void GameClear::Release(void)
{
	DeleteGraph(imgClear_);
}
