#include <DxLib.h>
#include "../../Common/Vector2F.h"
#include "../../Application.h"
#include "../../Scene/GameScene.h"
#include "Block/BlockBase.h"
#include "BackGround.h"

BackGround::BackGround(void)
{
}

BackGround::~BackGround(void)
{
}

void BackGround::Init(LevelManager* parent)
{
	level_ = parent;

	Load();

	Reset();
}

void BackGround::Update(void)
{
	//スクロール処理
	for (int i = 0; i < DRAW_IMAGES; i++)
	{
		drawPos_[i].x += scrollSpeed_;
		
		//スクロールの制限
		if (drawPos_[i].x >= SCROLL_MAX)
		{
			drawPos_[i].x = -IMAGE_SIZE_X;
		}
	}
}

void BackGround::Draw(void)
{
	//スクロール1枚目用描画
	DrawGraph(drawPos_[0].x,
		drawPos_[0].y,
		imgSky_[skyType_],
		true);

	//スクロール2枚目用描画
	DrawGraph(drawPos_[1].x,
		drawPos_[1].y,
		imgSky_[skyType_],
		true);
}

void BackGround::Release(void)
{
	for (int i = 0; i < static_cast<int>(TYPE::MAX); i++) { DeleteGraph(imgSky_[i]); }
}

void BackGround::Reset()
{
	drawPos_[0] = { 0,0 };
	drawPos_[0] = { -IMAGE_SIZE_X,0 };
	scrollSpeed_ = 0.5f;

	DATEDATA time;
	GetDateTime(&time);

	//時間ごとで背景を変える
	if (8 <= time.Hour && time.Hour <= 15)
	{
		skyType_ = static_cast<int>(TYPE::SKY);
	}
	else if ((16 <= time.Hour && time.Hour <= 19) ||
		(5 <= time.Hour && time.Hour <= 7))
	{
		skyType_ = static_cast<int>(TYPE::SUNSET);
	}
	else
	{
		skyType_ = static_cast<int>(TYPE::NIGHT);
	}
}

void BackGround::Load()
{
	//背景画像の読み込み
	imgSky_[static_cast<int>(TYPE::SKY)] = LoadGraph((Application::PATH_IMAGE + "Stage/sky.jpg").c_str());
	imgSky_[static_cast<int>(TYPE::NIGHT)] = LoadGraph((Application::PATH_IMAGE + "Stage/night.jpg").c_str());
	imgSky_[static_cast<int>(TYPE::SUNSET)] = LoadGraph((Application::PATH_IMAGE + "Stage/sunset.jpg").c_str());
}