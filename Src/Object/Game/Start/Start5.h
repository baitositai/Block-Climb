#pragma once
#include <string>
#include "GameStart.h"

class Start5 : public GameStart
{	
	//サイズ
	static constexpr int IMG_SIZE_X = 827;
	static constexpr int IMG_SIZE_Y = 280;

	//画像読み込み
	void SetImage() override;

};