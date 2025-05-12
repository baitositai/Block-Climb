#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Utility/AsoUtility.h"
#include "../Level/LevelManager.h"
#include "Moon1.h"

Moon1::Moon1()
{
	level_ = nullptr;
}

Moon1::~Moon1()
{
}

void Moon1::Reset()
{	
	Moon::Reset();

	//黄色い月の初期座標
	int i = static_cast<int>(MOON_TYPE::GOAL);
	firstPos_[i] = level_->GetGoalPos().ToVector2F();
	pos_[i] = firstPos_[i];
	isMoon_[i] = false;
}

void Moon1::Update()
{
	int i = static_cast<int>(MOON_TYPE::GOAL);

	//座標設定
	pos_[i] = firstPos_[i];

	//シェイク用変数
	float amplitude = 1.0f;// 揺らす周波数（Hz）0.3
	float frequency = 5.0f;// 揺らす振幅（ピクセル）

	//シェイク処理
	pos_[i] = AsoUtility::SinShake(pos_[i].ToVector2(), amplitude, frequency).ToVector2F();
}

void Moon1::Draw()
{
	Vector2 cameraPos = level_->GetCameraPos().ToVector2();
	int i = static_cast<int>(MOON_TYPE::GOAL);

	//ゴールの描画
	DrawRotaGraph(pos_[i].x - cameraPos.x,
		pos_[i].y - cameraPos.y,
		1.0f,	//拡大
		0.0f,	//回転
		images_[i],
		true,	//分からん
		false);	//向き
}
