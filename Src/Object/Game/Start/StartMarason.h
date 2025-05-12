#pragma once
#include <string>
#include "GameStart.h"

class StartMarason : public GameStart
{
	//ƒTƒCƒY
	static constexpr int IMG_SIZE_X = 1106;
	static constexpr int IMG_SIZE_Y = 280;

	//‰æ‘œ“Ç‚İ‚İ
	void SetImage() override;
};