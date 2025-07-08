#pragma once
#include <string>
#include "../Common/Vector2.h"



class FadeText
{
public:

	//コンストラクタ
	FadeText();

	//デストラクタ
	~FadeText();

	/// <summary>
	/// テキストの設定
	/// </summary>
	/// <param name="font"></param>フォント
	/// <param name="color"></param>色
	/// <param name="fontSize"></param>サイズ
	/// <param name="pos"></param>座標
	/// <param name="text"></param>テキスト
	void SetText(int font, int color,int fontSize,Vector2 pos,std::string text);

	//更新
	void Update();

	//描画
	void Draw();

	//解放
	void Release();

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos"></param>座標
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

