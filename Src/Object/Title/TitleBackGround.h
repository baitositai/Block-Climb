#pragma once
#include "../Game/BackGround.h"

class TitleScene;

class TitleBackGround :public BackGround
{
public:

	TitleBackGround();
	~TitleBackGround();

	void Init(TitleScene* parent);
	void Reset();

private:

	//�C���X�^���X
	TitleScene* title_;

};

