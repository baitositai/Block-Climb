#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Side6.h"

void Side6::Reset()
{
	//リセット
	SideBase::Reset();

	//画像の種類の決定
	sideBlockType_ = SIDE_IMG_INDEX;
}

void Side6::Update()
{
}

void Side6::Draw(void)
{
	SideBase::Draw();
	HeightDraw();
}

void Side6::HeightDraw()
{
	Vector2 boxPos1 = {
	rightPos_.x - SIDE_DRAW_SIZE_X / 2 + INTERVAL_X * BOX_MARGIN_X_COUNT,
	BOX_POS_Y
	};
	Vector2 boxSize1 = {
		rightSideSize_.x - INTERVAL_X * BOX_WIDTH_MARGIN_COUNT,
		BOX_HEIGHT
	};
	SideBase::WBorderRectangle(boxSize1, boxPos1, BOX_BORDER);

	//テキスト描画（「現在の高さ」）
	DrawFormatStringToHandle(
		boxPos1.x + INTERVAL_X,
		boxPos1.y + INTERVAL_Y,
		0xf00fff,
		normalFont_,
		"現在の高さ"
	);

	//データの描画（高さ表示）
	DrawFormatStringToHandle(
		boxPos1.x + INTERVAL_X * 2,
		boxPos1.y + FONT_SIZE + INTERVAL_Y,
		0xffffff,
		dataFont_,
		"%d m",
		level_->GetBlockHeight()
	);
}

void Side6::IconDraw()
{
	Vector2 boxPos1 = {
		rightPos_.x + (rightSideSize_.x / 2) - (SIDE_DRAW_SIZE_X / 2) - ICON_BOX_OFFSET_X,
		ICON_BOX_POS_Y
	};
	Vector2 boxSize1 = { ICON_BOX_WIDTH, ICON_BOX_HEIGHT };
	SideBase::WBorderRectangle(boxSize1, boxPos1, BOX_BORDER);

	level_->IconDraw(boxPos1);
}
