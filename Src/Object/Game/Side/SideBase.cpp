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

	// 画像読み込み
	int ret;
	ret = LoadDivGraph(((Application::PATH_IMAGE + "Background/BackGround.png").c_str()),
		SIDE_IMAGES,
		SIDE_IMAGES_X,
		SIDE_IMAGES_Y,
		SIDE_IMAGE_SIZE_X,
		SIDE_IMAGE_SIZE_Y,
		&(imgSideBlock_[0]));

	SetFont();
	Reset();
}

void SideBase::Reset()
{
	drawBlockX = DRAW_BLOCK_X;
	drawBlockY = Application::SCREEN_SIZE_Y / SIDE_IMAGE_SIZE_Y + DRAW_BLOCK_Y_EXTRA;

	sideBlockType_ = INIT_SIDE_BLOCK_TYPE;

	center_ = level_->GetGameCenter();

	gameSize_ = {
		level_->GetStageSize().x * BlockBase::BLOCK_SIZE_X,
		level_->GetStageSize().y * BlockBase::BLOCK_SIZE_Y
	};

	rightPos_ = {
		center_.x + gameSize_.x - BlockBase::BLOCK_SIZE_X - RIGHT_POS_OFFSET,
		0
	};

	rightSideSize_ = {
		Application::SCREEN_SIZE_X + SIDE_DRAW_SIZE_X / 2 - rightPos_.x,
		Application::SCREEN_SIZE_Y
	};

	leftPos_ = {
		center_.x + BlockBase::BLOCK_SIZE_X,
		0
	};

	leftSideSize_ = {
		leftPos_.x,
		Application::SCREEN_SIZE_Y
	};
}

void SideBase::Update(void)
{
}

void SideBase::Draw(void)
{
	for (int x = 0; x < drawBlockX; x++)
	{
		for (int y = 0; y < drawBlockY; y++)
		{
			DrawRotaGraph(
				rightPos_.x + x * SIDE_DRAW_SIZE_X,
				rightPos_.y + y * SIDE_DRAW_SIZE_Y,
				1.0f,
				0.0f,
				imgSideBlock_[sideBlockType_],
				true,
				false);
		}
	}

	for (int x = drawBlockX; x > 0; x--)
	{
		for (int y = 0; y < drawBlockY; y++)
		{
			DrawRotaGraph(
				leftPos_.x - x * SIDE_DRAW_SIZE_X,
				leftPos_.y + y * SIDE_DRAW_SIZE_Y,
				1.0f,
				0.0f,
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

	normalFont_ = CreateFontToHandle("ベストテンDOT", nmlFontSize_, FONT_THICK);
	dataFont_ = CreateFontToHandle("ベストテンDOT", dataFontSize_, FONT_THICK);
}

void SideBase::NextMinoDraw()
{
	WBorderRectangle({ NEXT_BLOCK_BOX_SIZE_X,NEXT_BLOCK_BOX_SIZE_Y }, { NEXT_BLOCK_BOX_POS_X,NEXT_BLOCK_BOX_POS_Y }, NEXT_BLOCK_BORDER);

	DrawFormatStringToHandle(
		NEXT_BLOCK_BOX_POS_X + NEXT_BLOCK_INTERVAL_X / 2,
		NEXT_BLOCK_BOX_POS_Y + NEXT_BLOCK_INTERVAL_Y / 2,
		0xf00fff,
		normalFont_,
		"Next");

	Vector2 blockPos = {
		NEXT_BLOCK_BOX_POS_X + NEXT_BLOCK_BOX_SIZE_X / 2,
		NEXT_BLOCK_BOX_POS_Y + nmlFontSize_ + NEXT_BLOCK_INTERVAL_Y * NEXT_BLOCK_Y_OFFSET_RATE
	};
	level_->NextBlockDraw(blockPos);
}

void SideBase::WBorderRectangle(Vector2 size, Vector2 pos, int border)
{
	for (int i = 1; i >= 0; i--)
	{
		int color = (i == 1) ? 0xffffff : 0x000000;
		DrawBox(
			pos.x - border * i,
			pos.y - border * i,
			pos.x + size.x + border * i,
			pos.y + size.y + border * i,
			color,
			true);
	}
}
