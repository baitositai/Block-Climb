#pragma once
#include <string>
#include "GameStart.h"

class Start5 : public GameStart
{	
	//�T�C�Y
	static constexpr int IMG_SIZE_X = 827;
	static constexpr int IMG_SIZE_Y = 280;

	//�摜�ǂݍ���
	void SetImage() override;

};