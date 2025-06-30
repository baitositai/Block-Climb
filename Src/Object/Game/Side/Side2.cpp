#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Block/BlockBase.h"
#include "../Level/LevelManager.h"
#include "Side2.h"

Side2::Side2()
{
	minute_ = 0;
	second_ = 0;
}

Side2::~Side2()
{
}

void Side2::SetFont()
{
	nmlFontSize_ = NORMAL_FONT_SIZE;
	dataFontSize_ = DATA_FONT_SIZE;

	normalFont_ = CreateFontToHandle("ベストテンDOT", nmlFontSize_, FONT_THICK);
	dataFont_ = CreateFontToHandle("ベストテンDOT", dataFontSize_, FONT_THICK);
}

void Side2::Reset()
{
	//リセット
	SideBase::Reset();

	//画像の種類の決定
	sideBlockType_ = SIDE_IMG_INDEX;

	//制限時間関係
	time_ = TIME_LIMIT;
	minute_ = TIME_LIMIT_MAX_MINUTES;
	second_ = 0;
}

void Side2::Update()
{

	//制限時間の処理
	time_ -= SceneManager::GetInstance().GetDeltaTime();
	if (time_ <= 0)
	{
		level_->SetStopCnt(LevelManager::HIT_STOP_CNT);
		level_->SetGameOver(true);
	}	
	
	minute_ = (time_ / SECONDS_IN_AN_HOUR) % TIME_LIMIT_MAX_MINUTES;
	 second_ = time_ / SECONDS_IN_A_MINUTE % SECONDS_IN_A_MINUTE;
}

void Side2::Draw(void)
{
	SideBase::Draw();

	//【残りブロック数のボックス】
	Vector2 boxPos1 = {
		rightPos_.x - SIDE_DRAW_SIZE_X / 2 + SIDE_BOX_POS_X_OFFSET,
		BLOCK_COUNT_BOX_POS_Y
	};
	Vector2 boxSize1 = {
		rightSideSize_.x - SIDE_BOX_WIDTH_MARGIN,
		SIDE_BOX_HEIGHT
	};
	SideBase::WBorderRectangle(boxSize1, boxPos1, SIDE_BOX_BORDER);

	DrawFormatStringToHandle(
		boxPos1.x + SIDE_BOX_INTERVAL_X,
		boxPos1.y + SIDE_BOX_INTERVAL_Y,
		0xf00fff,
		normalFont_,
		"クリアまで残り");

	DrawFormatStringToHandle(
		boxPos1.x + SIDE_BOX_INTERVAL_X * SIDE_DATA_OFFSET_X_RATE,
		boxPos1.y + FONT_SIZE + SIDE_BOX_INTERVAL_Y * SIDE_DATA_OFFSET_Y_RATE,
		0xffffff,
		dataFont_,
		"%d ブロック",
		level_->GetBlockCnt());

	//【制限時間のボックス】
	boxPos1 = {
		rightPos_.x - SIDE_DRAW_SIZE_X / 2 + SIDE_BOX_POS_X_OFFSET,
		TIME_LIMIT_BOX_POS_Y
	};
	boxSize1 = {
		rightSideSize_.x - SIDE_BOX_WIDTH_MARGIN,
		SIDE_BOX_HEIGHT
	};
	SideBase::WBorderRectangle(boxSize1, boxPos1, SIDE_BOX_BORDER);

	DrawFormatStringToHandle(
		boxPos1.x + SIDE_BOX_INTERVAL_X,
		boxPos1.y + SIDE_BOX_INTERVAL_Y,
		0xf00fff,
		normalFont_,
		"制限時間");

	DrawFormatStringToHandle(
		boxPos1.x + SIDE_BOX_INTERVAL_X * SIDE_DATA_OFFSET_X_RATE,
		boxPos1.y + FONT_SIZE + SIDE_BOX_INTERVAL_Y * SIDE_DATA_OFFSET_Y_RATE,
		0xffffff,
		dataFont_,
		"%d分 %d 秒",
		minute_,
		second_);
}