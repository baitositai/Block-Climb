#pragma once
#include <string>
#include "GameStart.h"

class Start2 : public GameStart
{
public:

	//�T�C�Y
	static constexpr int IMG_SIZE_X = 816;
	static constexpr int IMG_SIZE_Y = 280;

	//�摜�ǂݍ���
	void SetImage() override;

};

