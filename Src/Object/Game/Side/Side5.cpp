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

	normalFont_ = CreateFontToHandle("�x�X�g�e��DOT", nmlFontSize_, FONT_THICK);
	dataFont_ = CreateFontToHandle("�x�X�g�e��DOT", dataFontSize_, FONT_THICK);
}

void Side5::Reset()
{
	//���Z�b�g
	SideBase::Reset();

	//�摜�̎�ނ̌���
	sideBlockType_ = SIDE_IMG_INDEX;

	time_ = TIME_LIMIT;
	minitu_ = TIME_LIMIT_MAX_MINUTES;
	second_ = 0;
}

void Side5::Update()
{

	//�������Ԃ̏���
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

    //��ڂ̃{�b�N�X�̕`��
    Vector2 boxPos1 = {
        rightPos_.x - SIDE_DRAW_SIZE_X / 2 + INTERVAL_X * BOX1_MARGIN_X_COUNT,
        BOX1_POS_Y
    };
    Vector2 boxSize1 = {
        rightSideSize_.x - INTERVAL_X * BOX1_WIDTH_MARGIN_COUNT,
        BOX1_HEIGHT
    };
    SideBase::WBorderRectangle(boxSize1, boxPos1, BOX_BORDER);

    //�e�L�X�g�`��i�u�N���A�܂Ŏc��v�j
    DrawFormatStringToHandle(
        boxPos1.x + INTERVAL_X,
        boxPos1.y + INTERVAL_Y,
        0xf00fff,
        normalFont_,
        "�N���A�܂Ŏc��"
    );

    //�u���b�N���̕\��
    DrawFormatStringToHandle(
        boxPos1.x + INTERVAL_X * 2,
        boxPos1.y + FONT_SIZE + INTERVAL_Y * 2,
        0xffffff,
        dataFont_,
        "%d �u���b�N",
        level_->GetBlockCnt()
    );

    //��ڂ̃{�b�N�X�̕`��
    boxPos1 = {
        rightPos_.x - SIDE_DRAW_SIZE_X / 2 + INTERVAL_X * BOX1_MARGIN_X_COUNT,
        BOX2_POS_Y
    };
    boxSize1 = {
        rightSideSize_.x - INTERVAL_X * BOX1_WIDTH_MARGIN_COUNT,
        BOX2_HEIGHT
    };
    SideBase::WBorderRectangle(boxSize1, boxPos1, BOX_BORDER);

    //�e�L�X�g�`��i�u�������ԁv�j
    DrawFormatStringToHandle(
        boxPos1.x + INTERVAL_X,
        boxPos1.y + INTERVAL_Y,
        0xf00fff,
        normalFont_,
        "��������"
    );

    //�������Ԃ̕��ƕb�̕\��
    DrawFormatStringToHandle(
        boxPos1.x + INTERVAL_X * 2,
        boxPos1.y + FONT_SIZE + INTERVAL_Y * 2,
        0xffffff,
        dataFont_,
        "%d�� %d �b",
        minitu_,
        second_
    );

}
