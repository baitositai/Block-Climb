#include <DxLib.h> 
#include "../../../Utility/AsoUtility.h"
#include "../../../Application.h"
#include "GameOver.h"

GameOver::GameOver()
{
	imgOver_ = 0;
	pos_ = {};
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
	//‰æ‘œ“Ç‚İ‚İ
	imgOver_ = LoadGraph((Application::PATH_IMAGE + "UI/GameOver.png").c_str());

	pos_.x = Application::SCREEN_SIZE_X / 2 - SIZE_X / 2;
	pos_.y = Application::SCREEN_SIZE_Y / 2 - SIZE_Y / 2;
}

void GameOver::Update()
{
	//À•W‚Ìİ’è
	pos_.x = POS_X;
	pos_.y = POS_Y;

	//ã‰º—h‚ç‚µ‚Ìˆ—
	pos_ = AsoUtility::SinShake(pos_, AMPLITUDE, FREQUENCY);

}

void GameOver::Draw()
{
	//‰æ‘œ‚Ì•`‰æ
	DrawGraph(pos_.x, pos_.y, imgOver_, true);
}

void GameOver::Release()
{
	DeleteGraph(imgOver_);
}