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
	//画像読み込み
	imgOver_ = LoadGraph((Application::PATH_IMAGE + "UI/GameOver.png").c_str());

	pos_.x = Application::SCREEN_SIZE_X / 2 - SIZE_X / 2;
	pos_.y = Application::SCREEN_SIZE_Y / 2 - SIZE_Y / 2;
}

void GameOver::Update()
{
	//座標の設定
	pos_.x = POS_X;
	pos_.y = POS_Y;

	//上下揺らしの処理
	pos_ = AsoUtility::SinShake(pos_, AMPLITUDE, FREQUENCY);

}

void GameOver::Draw()
{
	//画像の描画
	DrawGraph(pos_.x, pos_.y, imgOver_, true);
}

void GameOver::Release()
{
	DeleteGraph(imgOver_);
}