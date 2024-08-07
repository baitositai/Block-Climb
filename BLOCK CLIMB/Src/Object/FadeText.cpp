#include <DxLib.h>
#include "FadeText.h"
#include "../Application.h"

FadeText::FadeText()
{
	alpha_ = 0;
	color_ = 0;
	fade_ = 0;
	font_ = 0;
	size_ = 0;
}

FadeText::~FadeText()
{
}

void FadeText::SetText(int font ,int color ,int size ,Vector2 pos ,std::string text)
{
	font_ = font;
	text_ = text;
	color_ = color;
	pos_ = pos;
	size_ = size;
	alpha_ = 256;
	fade_ = 1;
}

void FadeText::Update()
{
	if (alpha_ > 256 ||
		alpha_ < 128)
	{
		fade_ *= -1;
	}
	alpha_ += fade_;

}

void FadeText::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);

	DrawStringToHandle(pos_.x,pos_.y,
		text_.c_str(),
		color_,
		font_);
}

void FadeText::Release()
{
	DeleteFontToHandle(font_);
}

void FadeText::SetPos(Vector2 pos)
{
	pos_ = pos;
}
