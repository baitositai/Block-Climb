#pragma once
#include <string>
#include "GameStart.h"

class StartMarason : public GameStart
{
	//サイズ
	static constexpr int IMG_SIZE_X = 1106;
	static constexpr int IMG_SIZE_Y = 280;

	//画像読み込み
	void SetImage() override;
};