#pragma once
#include <string>
#include "GameStart.h"

class Start2 : public GameStart
{
public:

	//サイズ
	static constexpr int IMG_SIZE_X = 816;
	static constexpr int IMG_SIZE_Y = 280;

	//画像読み込み
	void SetImage() override;

};

