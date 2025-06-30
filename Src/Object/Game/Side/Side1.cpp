#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Side1.h"

Side1::Side1()
{
}

Side1::~Side1()
{
}

void Side1::Reset()
{
	//リセット
	SideBase::Reset();

	//画像の種類の決定
	sideBlockType_ = SIDE_IMG_INDEX;
}

void Side1::Update()
{
}

void Side1::Draw(void)
{
	SideBase::Draw();

	Vector2 boxPos1 = {
		rightPos_.x - SIDE_DRAW_SIZE_X / 2 + BOX_MARGIN_X * BOX_POS_X_OFFSET_RATE,
		BOX_POS_Y
	};
	Vector2 boxSize1 = {
		rightSideSize_.x - BOX_WIDTH_MARGIN_TOTAL,
		BOX_HEIGHT
	};

	SideBase::WBorderRectangle(boxSize1, boxPos1, BOX_BORDER);

	//テキスト描画
	DrawFormatStringToHandle(
		boxPos1.x + BOX_MARGIN_X,
		boxPos1.y + BOX_MARGIN_Y,
		0xf00fff,
		normalFont_,
		"現在の高さ");

	//データの描画
	DrawFormatStringToHandle(
		boxPos1.x + BOX_MARGIN_X * DATA_POS_X_OFFSET_RATE,
		boxPos1.y + FONT_SIZE + BOX_MARGIN_Y,
		0xffffff,
		dataFont_,
		"%d m",
		level_->GetBlockHeight());
}
