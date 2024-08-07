#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Block/BlockBase.h"
#include "../Block/Block3.h"
#include "../Level/LevelManager.h"
#include "Side3.h"

void Side3::SetFont()
{
	nmlFontSize_ = 28;
	dataFontSize_ = 48;

	normalFont_ = CreateFontToHandle("ベストテンDOT", nmlFontSize_, 3);
	dataFont_ = CreateFontToHandle("ベストテンDOT", dataFontSize_, 3);
}

void Side3::Reset()
{
	SideBase::Reset();

	//画像の種類の決定
	sideBlockType_ = 2;
}

void Side3::Draw(void)
{
	SideBase::Draw();

	//フチあり四角の描画
	int border = 3;

	//間隔
	int intervalX = 5;
	int intervalY = 10;

	Vector2 boxPos1 = { rightPos_.x - SIDE_DRAW_SIZE_X / 2 + intervalX * 4,150 };
	Vector2 boxSize1 = { rightSideSize_.x - intervalX * 8,110 };
	SideBase::WBorderRectangle(boxSize1, boxPos1, border);

	//テキスト描画
	DrawFormatStringToHandle(boxPos1.x + intervalX,
		boxPos1.y + intervalY,
		0xf00fff,
		normalFont_,
		"クリアまで残り");

	int blockCnt = Block3::CREAL_LINE - level_->GetCntLine();

	//データの描画
	DrawFormatStringToHandle(boxPos1.x + intervalX * 2,
		boxPos1.y + FONT_SIZE + intervalY,
		0xffffff,
		dataFont_,
		"%d ライン",
		blockCnt);
}
