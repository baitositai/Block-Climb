#pragma once
#include <string>
#include "GameStart.h"

class Start1: public GameStart
{
	//�T�C�Y
	static constexpr int IMG_SIZE_X = 826;
	static constexpr int IMG_SIZE_Y = 284;

	//�摜�ǂݍ���
	void SetImage() override;

};