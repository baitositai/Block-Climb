#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Side4.h"

void Side4::Reset()
{
	//リセット
	SideBase::Reset();

	//画像の種類の決定
	sideBlockType_ = SIDE_IMG_INDEX;
}

void Side4::Update()
{
}

void Side4::Draw(void)
{
    SideBase::Draw();

    Vector2 boxPos1 = {
    rightPos_.x - SIDE_DRAW_SIZE_X / 2 + INTERVAL_X * BOX_MARGIN_X_COUNT,
    BOX_POS_Y
    };

    Vector2 boxSize1 = {
        rightSideSize_.x - INTERVAL_X * BOX_WIDTH_MARGIN_COUNT,
        BOX_HEIGHT
    };

    SideBase::WBorderRectangle(boxSize1, boxPos1, BOX_BORDER);

    //テキスト描画
    DrawFormatStringToHandle(
        boxPos1.x + INTERVAL_X,
        boxPos1.y + INTERVAL_Y,
        0xf00fff,
        normalFont_,
        "現在の高さ"
    );

    //データの描画
    DrawFormatStringToHandle(
        boxPos1.x + INTERVAL_X * 2,
        boxPos1.y + FONT_SIZE + INTERVAL_Y,
        0xffffff,
        dataFont_,
        "%d m",
        level_->GetBlockHeight()
    );
}
