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

	//画像読み込み
	imgClear_ = LoadGraph((Application::PATH_IMAGE + "UI/ClearUI.png").c_str());
}

void GameClear::Update()
{
	//座標の設定
	pos_.x = POS_X;
	pos_.y = POS_Y;

	//上下揺らしの処理
	pos_ = AsoUtility::SinShake(pos_, AMPLITUDE, FREQUENCY);

}

void GameClear::Draw()
{
	//画像の描画
	DrawGraph(pos_.x, pos_.y, imgClear_, true);
}

void GameClear::Release()
{
	DeleteGraph(imgClear_);
}
