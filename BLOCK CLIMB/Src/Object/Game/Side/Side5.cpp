#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Block/BlockBase.h"
#include "../Level/LevelManager.h"
#include "Side5.h"

void Side5::SetFont()
{
	nmlFontSize_ = 28;
	dataFontSize_ = 32;

	normalFont_ = CreateFontToHandle("ベストテンDOT", nmlFontSize_, 3);
	dataFont_ = CreateFontToHandle("ベストテンDOT", dataFontSize_, 3);
}

void Side5::Reset()
{
	//リセット
	SideBase::Reset();

	//画像の種類の決定
	sideBlockType_ = 4;

	time_ = TIME_LIMIT;
	minitu_ = 5;
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
	
	minitu_ = (time_ / 3600) % 5;
	second_ = time_ / 60 % 60;
}

void Side5::Draw(void)
{
	SideBase::Draw();

#pragma region 残りブロック数
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

	//データの描画
	DrawFormatStringToHandle(boxPos1.x + intervalX * 2,
		boxPos1.y + FONT_SIZE + intervalY * 2,
		0xffffff,
		dataFont_,
		"%d ブロック",
		level_->GetBlockCnt());
#pragma endregion

#pragma region	制限時間
	//フチあり四角の描画
	border = 3;

	//間隔
	intervalX = 5;
	intervalY = 10;

	boxPos1 = { rightPos_.x - SIDE_DRAW_SIZE_X / 2 + intervalX * 4,300 };
	boxSize1 = { rightSideSize_.x - intervalX * 8,110 };
	SideBase::WBorderRectangle(boxSize1, boxPos1, border);

	//テキスト描画
	DrawFormatStringToHandle(boxPos1.x + intervalX,
		boxPos1.y + intervalY,
		0xf00fff,
		normalFont_,
		"制限時間");



	//データの描画
	DrawFormatStringToHandle(boxPos1.x + intervalX * 2,
		boxPos1.y + FONT_SIZE + intervalY * 2,
		0xffffff,
		dataFont_,
		"%d分 %d 秒",
		minitu_,
		second_);
#pragma endregion

}
