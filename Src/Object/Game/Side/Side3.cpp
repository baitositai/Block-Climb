#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Block/BlockBase.h"
#include "../Block/Block3.h"
#include "../Level/LevelManager.h"
#include "Side3.h"

Side3::Side3()
{
}

Side3::~Side3()
{
}

void Side3::SetFont()
{
	nmlFontSize_ = NORMAL_FONT_SIZE;
	dataFontSize_ = DATA_FONT_SIZE;

	normalFont_ = CreateFontToHandle("ベストテンDOT", nmlFontSize_, FONT_THICK);
	dataFont_ = CreateFontToHandle("ベストテンDOT", dataFontSize_, FONT_THICK);
}

void Side3::Reset()
{
	SideBase::Reset();

	//画像の種類の決定
	sideBlockType_ = SIDE_IMG_INDEX;
}

void Side3::Draw(void)
{
	SideBase::Draw();

	//フチあり四角の描画
	int border = SIDE_BOX_BORDER;

	Vector2 boxPos1 = {
		rightPos_.x - SIDE_DRAW_SIZE_X / 2 + SIDE_BOX_RIGHT_OFFSET_X,
		BOX_POS_Y
	};
	Vector2 boxSize1 = {
		rightSideSize_.x - SIDE_BOX_WIDTH_MARGIN,
		SIDE_BOX_HEIGHT
	};
	SideBase::WBorderRectangle(boxSize1, boxPos1, border);

	//テキスト描画
	DrawFormatStringToHandle(
		boxPos1.x + SIDE_BOX_INTERVAL_X,
		boxPos1.y + SIDE_BOX_INTERVAL_Y,
		0xf00fff,
		normalFont_,
		"クリアまで残り");

	int blockCnt = Block3::CREAL_LINE - level_->GetCntLine();

	//0未満を表示させない
	if (blockCnt <= 0) { blockCnt = 0; }

	//データの描画
	DrawFormatStringToHandle(
		boxPos1.x + SIDE_BOX_INTERVAL_X * 2,
		boxPos1.y + FONT_SIZE + SIDE_BOX_INTERVAL_Y,
		0xffffff,
		dataFont_,
		"%d ライン",
		blockCnt);
}