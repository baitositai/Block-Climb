#pragma once
#include <string>
#include "GameStart.h"

class Start3 : public GameStart
{
public:
	//�T�C�Y
	static constexpr int IMG_SIZE_X = 948;
	static constexpr int IMG_SIZE_Y = 218;

	//�摜�ǂݍ���
	void SetImage() override;

};

