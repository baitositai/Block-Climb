#pragma once
#include <string>
#include "GameStart.h"

class Start3 : public GameStart
{
public:
	//サイズ
	static constexpr int IMG_SIZE_X = 948;
	static constexpr int IMG_SIZE_Y = 218;

	//画像読み込み
	void SetImage() override;

};

