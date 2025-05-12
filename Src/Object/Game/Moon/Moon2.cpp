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
	firstPos_[i] = { center + 75, 250 };
	pos_[i] = firstPos_[i];
	isMoon_[i] = false;

	//青い月の初期座標
	i = static_cast<int>(MOON_TYPE::CHANGE);
	firstPos_[i] = { static_cast<float>(Application::SCREEN_SIZE_X - (center + 75)), 250 };
	pos_[i] = firstPos_[i];
	isMoon_[i] = false;
}

void Moon2::Update()
{
	for (int i = 0; i < 2; i++)
	{
		int j = static_cast<int>(MOON_TYPE::CHANGE);
		if (i == 1) { j = static_cast<int>(MOON_TYPE::CREATE); }

		//座標設定
		pos_[j] = firstPos_[j];

		//シェイク用変数
		float amplitude = 1.0f;// 揺らす周波数（Hz）0.3
		float frequency = 5.0f;// 揺らす振幅（ピクセル）

		//シェイク処理
		pos_[j] = AsoUtility::SinShake(pos_[j].ToVector2(), amplitude, frequency).ToVector2F();
	}
}

void Moon2::Draw()
{
	for (int i = 0; i < 2; i++)
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
