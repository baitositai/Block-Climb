#include <DxLib.h>
#include "SideBase.h"
#include "../Block/BlockBase.h"
#include " ../../../../../Manager/SceneManager.h"
#include "../Level/LevelManager.h"


SideBase::SideBase(void)
{
	normalFont_ = 0;
	nmlFontSize_ = 0;
	dataFont_ = 0;
	dataFontSize_ = 0;
	drawBlockX = 0;
	drawBlockY = 0;
	sideBlockType_ = 0;
	time_ = 0;
	level_ = nullptr;

	for (int i = 0; i < SIDE_IMAGES; i++)
	{
		imgSideBlock_[i] = 0;
	}
}

SideBase::~SideBase(void)
{
}

void SideBase::Init(LevelManager* parent)
{
	level_ = parent;

	//画像読み込み
	int ret;
	ret = LoadDivGraph(((Application::PATH_IMAGE + "Background/BackGround.png").c_str())
		, SIDE_IMAGES
		, SIDE_IMAGES_X
		, SIDE_IMAGES_Y
		, SIDE_IMAGE_SIZE_X
		, SIDE_IMAGE_SIZE_Y
		, &(imgSideBlock_[0]));

	SetFont();

	Reset();
}

void SideBase::Reset()
{
	//画像描画の設定
	drawBlockX = 8;
	drawBlockY = Application::SCREEN_SIZE_Y / SIDE_IMAGE_SIZE_Y + 2;

	//画像の種類の決定
	sideBlockType_ = 0;
	
	center_ = level_->GetGameCenter();

	//ゲーム画面のサイズ
	gameSize_ = { level_->GetStageSize().x * BlockBase::BLOCK_SIZE_X ,
				  level_->GetStageSize().y * BlockBase::BLOCK_SIZE_Y };

	//右始点
	rightPos_ = { center_.x + gameSize_.x - BlockBase::BLOCK_SIZE_X -5,0 };

	//右サイドサイズ
	rightSideSize_ = { Application::SCREEN_SIZE_X  + SIDE_DRAW_SIZE_X / 2 - rightPos_.x,
					   Application::SCREEN_SIZE_Y};

	//左始点
	leftPos_ = { center_.x + BlockBase::BLOCK_SIZE_X ,0 };

	//左サイドサイズ
	leftSideSize_ = { leftPos_ .x,
					  Application::SCREEN_SIZE_Y };
}

void SideBase::Update(void)
{
}

void SideBase::Draw(void)
{
	//右側の描画
	for (int x = 0; x < drawBlockX; x++)
	{
		for (int y = 0; y < drawBlockY; y++)
		{
			DrawRotaGraph(rightPos_.x + x * SIDE_DRAW_SIZE_X,
				rightPos_.y + y * SIDE_DRAW_SIZE_Y,
				1.0f,	//拡大
				0.0f,	//回転
				imgSideBlock_[sideBlockType_],
				true,
				false);
		}
	}

	//左側の描画
	for (int x = drawBlockX; x > 0; x--)
	{
		for (int y = 0; y < drawBlockY; y++)
		{
			DrawRotaGraph(leftPos_.x - x * SIDE_DRAW_SIZE_X,
				leftPos_.y + y * SIDE_DRAW_SIZE_Y,
				1.0f,	//拡大
				0.0f,	//回転
				imgSideBlock_[sideBlockType_],
				true,
				false);
		}
	}

	NextMinoDraw();
}

void SideBase::Release(void)
{
	DeleteFontToHandle(dataFont_);
	DeleteFontToHandle(normalFont_);
	for (int i = 0; i < SIDE_IMAGES; i++) { DeleteGraph(imgSideBlock_[i]); }
}

void SideBase::SetFont()
{
	nmlFontSize_ = FONT_SIZE;
	dataFontSize_ = FONT_DATA_SIZE;

	normalFont_ = CreateFontToHandle("ベストテンDOT", nmlFontSize_, 3);
	dataFont_ = CreateFontToHandle("ベストテンDOT", dataFontSize_, 3);
}

void SideBase::NextMinoDraw()
{
	int border = 3;
	Vector2 intervel = { 40, 20};
	Vector2 boxPos = { intervel.x,150 };
	Vector2 boxSize = { leftSideSize_.x - SIDE_DRAW_SIZE_X / 2 - intervel.x * 2, 220 };
	WBorderRectangle(boxSize, boxPos, border);

	//テキスト描画
	DrawFormatStringToHandle(boxPos.x + intervel.x / 2,
		boxPos.y + intervel.y / 2,
		0xf00fff,
		normalFont_,
		"Next");

	//次のブロックの描画
	Vector2 blockPos =
	{ boxPos.x + boxSize.x / 2,
	  boxPos.y + nmlFontSize_ + intervel.y * 3};
	level_->NextBlockDraw(blockPos);
}

void SideBase::WBorderRectangle(Vector2 size, Vector2 pos, int border)
{
	for (int i = 1; i >= 0; i--)
	{
		int color = 0x000000;
		if (i == 1) { color = 0xffffff; }

		DrawBox(pos.x - border * i,
			pos.y - border * i,
			pos.x + size.x + border * i,
			pos.y + size.y + border * i,
			color,
			true);
	}
}
