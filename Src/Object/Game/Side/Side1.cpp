#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Side1.h"

void Side1::Reset()
{
	//リセット
	SideBase::Reset();

	//画像の種類の決定
	sideBlockType_ = 0;
}

void Side1::Update()
{
}

void Side1::Draw(void)
{
	SideBase::Draw();
	
	//間隔
	int intervalX = 5;
	int intervalY = 10;

	//フチあり四角の描画
	int border = 3;
	Vector2 boxPos1 = { rightPos_.x - SIDE_DRAW_SIZE_X / 2 + intervalX * 8,150 };
	Vector2 boxSize1 = { rightSideSize_.x - intervalX * 16,120 };
	SideBase::WBorderRectangle(boxSize1, boxPos1, border);

	//テキスト描画
	DrawFormatStringToHandle(boxPos1.x + intervalX,
		boxPos1.y + intervalY,
		0xf00fff,
		normalFont_,
		"現在の高さ");

	//データの描画
	DrawFormatStringToHandle(boxPos1.x + intervalX * 2,
		boxPos1.y + FONT_SIZE + intervalY,
		0xffffff,
		dataFont_,
		"%d m",
		level_->GetBlockHeight());
}
