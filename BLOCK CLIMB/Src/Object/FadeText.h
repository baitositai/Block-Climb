#pragma once
#include <string>
#include "../Common/Vector2.h"



class FadeText
{
public:

	FadeText();
	~FadeText();

	void SetText(int font, int color,int fontSize,Vector2 pos,std::string text);
	void Update();
	void Draw();
	void Release();
	void SetPos(Vector2 pos);

private:

	//フォント
	int font_;

	//アルファ値
	int alpha_;

	//フェード値
	int fade_;

	//色
	int color_;

	//大きさ
	int size_;

	//座標
	Vector2 pos_;

	//テキスト
	std::string text_;

};

