#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "SideMarason.h"

void SideMarason::Reset()
{
	//ƒŠƒZƒbƒg
	SideBase::Reset();

	//‰æ‘œ‚ÌŽí—Þ‚ÌŒˆ’è
	sideBlockType_ = rand() % SIDE_IMAGES;
}

void SideMarason::Update()
{
}

void SideMarason::Draw(void)
{
	SideBase::Draw();
	IconDraw();
	HeightDraw();
}

void SideMarason::HeightDraw()
{
	Vector2 boxPos1 = {
		rightPos_.x - SIDE_DRAW_SIZE_X / 2 + INTERVAL_X * HEIGHT_BOX_OFFSET_X_RATE,
		HEIGHT_BOX_POS_Y
	};
	Vector2 boxSize1 = {
		rightSideSize_.x - INTERVAL_X * HEIGHT_BOX_WIDTH_OFFSET_RATE,
		HEIGHT_BOX_SIZE_Y
	};
	SideBase::WBorderRectangle(boxSize1, boxPos1, BOX_BORDER);

	DrawFormatStringToHandle(
		boxPos1.x + INTERVAL_X,
		boxPos1.y + INTERVAL_Y,
		0xf00fff,
		normalFont_,
		"Œ»Ý‚Ì‚‚³"
	);

	DrawFormatStringToHandle(
		boxPos1.x + INTERVAL_X * 2,
		boxPos1.y + FONT_SIZE + INTERVAL_Y,
		0xffffff,
		dataFont_,
		"%d m",
		level_->GetBlockHeight()
	);
}

void SideMarason::IconDraw()
{
	Vector2 boxPos1 = {
		rightPos_.x + (rightSideSize_.x / 2) - (SIDE_DRAW_SIZE_X / 2) - ICON_BOX_OFFSET_X,
		ICON_BOX_POS_Y
	};
	Vector2 boxSize1 = { ICON_BOX_SIZE, ICON_BOX_SIZE };
	SideBase::WBorderRectangle(boxSize1, boxPos1, BOX_BORDER);

	level_->IconDraw(boxPos1);
}