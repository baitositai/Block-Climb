#pragma once
#include <string>
#include "GameStart.h"

class Start4 : public GameStart
{
	//サイズ
	static constexpr int IMG_SIZE_X = 826;
	static constexpr int IMG_SIZE_Y = 284;
	//画像読み込み
	void SetImage() override;

private:

};