#include<DxLib.h>
#include"../Game/BackGround.h"
#include "TitleBackGround.h"

TitleBackGround::TitleBackGround()
{
}

TitleBackGround::~TitleBackGround()
{
}

void TitleBackGround::Init(TitleScene* parent)
{
	title_ = parent;

	Load();

	Reset();
}

void TitleBackGround::Reset()
{
	BackGround::Reset();
}
