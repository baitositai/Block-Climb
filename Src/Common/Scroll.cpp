#include<DxLib.h>
#include "Scroll.h"

Scroll::Scroll()
{
	imgBack_ = 0;
	speed_ = 0.0f;
}

Scroll::~Scroll()
{
}

void Scroll::Init(int image, Vector2 imageSize, int drawNum, float scrollSpeed)
{
	imgBack_ = image;
	size_ = imageSize;
	pos_.resize(drawNum,{0,0});
	speed_ = scrollSpeed;

	SetWidthScrollPos();
}

void Scroll::Update()
{
	//スクロール処理
	int size = pos_.size();
	for (int i = 0; i < size; i++)
	{
		pos_[i].x += speed_;

		//スクロールの制限
		if (pos_[i].x >= (size_.x * (size - 1)))
		{
			pos_[i].x = -size_.x;
		}
	}
}

void Scroll::Draw()
{
	int size = pos_.size();
	for (int i = 0; i < size; i++)
	{
		DrawGraph(pos_[i].x,
			pos_[i].y,
			imgBack_,
			true);
	}
}

void Scroll::Release()
{
	DeleteGraph(imgBack_);
}

void Scroll::SetWidthScrollPos()
{
	int size = pos_.size();
	for (int i = 0; i < size; i++)
	{
		pos_[i].x = -size_.x + i * (size_.x);
	}
}
