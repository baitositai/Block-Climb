#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Utility/AsoUtility.h"
#include "../Level/LevelManager.h"
#include "Moon2.h"

Moon2::Moon2()
{
}

Moon2::~Moon2()
{
}

void Moon2::Reset()
{
	Moon::Reset();
	float center = level_->GetGameCenter().x;

	//赤い月の初期座標
	int i = static_cast<int>(MOON_TYPE::CREATE);
	firstPos_[i] = { center + RED_MOON_DEFAULT_POS_X, RED_MOON_DEFAULT_POS_Y };
	pos_[i] = firstPos_[i];
	isMoon_[i] = false;

	//青い月の初期座標
	i = static_cast<int>(MOON_TYPE::CHANGE);
	firstPos_[i] = { BLUE_MOON_DEFAULT_POS_X - center, BLUE_MOON_DEFAULT_POS_Y };
	pos_[i] = firstPos_[i];
	isMoon_[i] = false;
}

void Moon2::Update()
{
	for (int i = 0; i < UPD_MOONS; i++)
	{
		int j = static_cast<int>(MOON_TYPE::CHANGE);
		if (i == 1) { j = static_cast<int>(MOON_TYPE::CREATE); }

		//座標設定
		pos_[j] = firstPos_[j];

		//シェイク処理
		pos_[j] = AsoUtility::SinShake(pos_[j].ToVector2(), AMPLITUDE, FREQUENCY).ToVector2F();
	}
}

void Moon2::Draw()
{
	for (int i = 0; i < UPD_MOONS; i++)
	{
		int j = static_cast<int>(MOON_TYPE::CHANGE);
		if (i == 1) { j = static_cast<int>(MOON_TYPE::CREATE); }

		DrawRotaGraph(pos_[j].x,
			pos_[j].y,
			1.0f,
			0.0f,
			images_[j],
			true,
			false);
	}
}
