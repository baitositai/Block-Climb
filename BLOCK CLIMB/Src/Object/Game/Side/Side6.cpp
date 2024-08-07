#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Side6.h"

void Side6::Reset()
{
	//ƒŠƒZƒbƒg
	SideBase::Reset();

	//‰æ‘œ‚ÌŽí—Þ‚ÌŒˆ’è
	sideBlockType_ = 5;
}

void Side6::Update()
{
}

void Side6::Draw(void)
{
	SideBase::Draw();
	/*IconDraw();*/
	HeightDraw();
}

void Side6::HeightDraw()
{
	//ŠÔŠu
	int intervalX = 5;
	int intervalY = 10;

	//ƒtƒ`‚ ‚èŽlŠp‚Ì•`‰æ
	int border = 3;
	Vector2 boxPos1 = { rightPos_.x - SIDE_DRAW_SIZE_X / 2 + intervalX * 8,150 };
	Vector2 boxSize1 = { rightSideSize_.x - intervalX * 16,120 };
	SideBase::WBorderRectangle(boxSize1, boxPos1, border);

	//ƒeƒLƒXƒg•`‰æ
	DrawFormatStringToHandle(boxPos1.x + intervalX,
		boxPos1.y + intervalY,
		0xf00fff,
		normalFont_,
		"Œ»Ý‚Ì‚‚³");

	//ƒf[ƒ^‚Ì•`‰æ
	DrawFormatStringToHandle(boxPos1.x + intervalX * 2,
		boxPos1.y + FONT_SIZE + intervalY,
		0xffffff,
		dataFont_,
		"%d m",
		level_->GetBlockHeight());
}

void Side6::IconDraw()
{
	//ŠÔŠu
	int intervalX = 5;
	int intervalY = 10;

	//ƒtƒ`‚ ‚èŽlŠp‚Ì•`‰æ
	int border = 3;
	Vector2 boxPos1 = { rightPos_.x +(rightSideSize_.x / 2) -(SIDE_DRAW_SIZE_X / 2) -64,150 };
	Vector2 boxSize1 = { 128,128 };
	SideBase::WBorderRectangle(boxSize1, boxPos1, border);

	level_->IconDraw(boxPos1);

}
