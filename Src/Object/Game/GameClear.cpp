#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "GameClear.h"

GameClear::GameClear()
{
	imgClear_  = -1;
	pos_ = {};
}

GameClear::~GameClear()
{
}

void GameClear::Init()
{

	//‰æ‘œ“Ç‚İ‚İ
	imgClear_ = LoadGraph((Application::PATH_IMAGE + "UI/ClearUI.png").c_str());
}

void GameClear::Update()
{
	//À•W‚Ìİ’è
	pos_.x = POS_X;
	pos_.y = POS_Y;

	//ã‰º—h‚ç‚µ‚Ìˆ—
	pos_ = AsoUtility::SinShake(pos_, AMPLITUDE, FREQUENCY);

}

void GameClear::Draw()
{
	//‰æ‘œ‚Ì•`‰æ
	DrawGraph(pos_.x, pos_.y, imgClear_, true);
}

void GameClear::Release()
{
	DeleteGraph(imgClear_);
}
