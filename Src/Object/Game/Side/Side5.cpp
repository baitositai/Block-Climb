#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Block/BlockBase.h"
#include "../Level/LevelManager.h"
#include "Side5.h"

void Side5::SetFont()
{
	nmlFontSize_ = NORMAL_FONT_SIZE;
	dataFontSize_ = DATA_FONT_SIZE;

	normalFont_ = CreateFontToHandle("ベストテンDOT", nmlFontSize_, FONT_THICK);
	dataFont_ = CreateFontToHandle("ベストテンDOT", dataFontSize_, FONT_THICK);
}

void Side5::Reset()
{
	//リセット
	SideBase::Reset();

	//画像の種類の決定
	sideBlockType_ = SIDE_IMG_INDEX;

	time_ = TIME_LIMIT;
	minitu_ = TIME_LIMIT_MAX_MINUTES;
	second_ = 0;
}

void Side5::Update()
{

	//制限時間の処理
	time_ -= SceneManager::GetInstance().GetDeltaTime();
	if (time_ <= 0)
	{
		level_->SetStopCnt(LevelManager::HIT_STOP_CNT);
		level_->SetGameOver(true);
	}	
	
	minitu_ = (time_ / SECONDS_IN_AN_HOUR) % TIME_LIMIT_MAX_MINUTES;
	second_ = time_ / SECONDS_IN_A_MINUTE % SECONDS_IN_A_MINUTE;
}

void Side5::Draw(void)
{
	SideBase::Draw();

    //一つ目のボックスの描画
    Vector2 boxPos1 = {
        rightPos_.x - SIDE_DRAW_SIZE_X / 2 + INTERVAL_X * BOX1_MARGIN_X_COUNT,
        BOX1_POS_Y
    };
    Vector2 boxSize1 = {
        rightSideSize_.x - INTERVAL_X * BOX1_WIDTH_MARGIN_COUNT,
        BOX1_HEIGHT
    };
    SideBase::WBorderRectangle(boxSize1, boxPos1, BOX_BORDER);

    //テキスト描画（「クリアまで残り」）
    DrawFormatStringToHandle(
        boxPos1.x + INTERVAL_X,
        boxPos1.y + INTERVAL_Y,
        0xf00fff,
        normalFont_,
        "クリアまで残り"
    );

    //ブロック数の表示
    DrawFormatStringToHandle(
        boxPos1.x + INTERVAL_X * 2,
        boxPos1.y + FONT_SIZE + INTERVAL_Y * 2,
        0xffffff,
        dataFont_,
        "%d ブロック",
        level_->GetBlockCnt()
    );

    //二つ目のボックスの描画
    boxPos1 = {
        rightPos_.x - SIDE_DRAW_SIZE_X / 2 + INTERVAL_X * BOX1_MARGIN_X_COUNT,
        BOX2_POS_Y
    };
    boxSize1 = {
        rightSideSize_.x - INTERVAL_X * BOX1_WIDTH_MARGIN_COUNT,
        BOX2_HEIGHT
    };
    SideBase::WBorderRectangle(boxSize1, boxPos1, BOX_BORDER);

    //テキスト描画（「制限時間」）
    DrawFormatStringToHandle(
        boxPos1.x + INTERVAL_X,
        boxPos1.y + INTERVAL_Y,
        0xf00fff,
        normalFont_,
        "制限時間"
    );

    //制限時間の分と秒の表示
    DrawFormatStringToHandle(
        boxPos1.x + INTERVAL_X * 2,
        boxPos1.y + FONT_SIZE + INTERVAL_Y * 2,
        0xffffff,
        dataFont_,
        "%d分 %d 秒",
        minitu_,
        second_
    );

}
