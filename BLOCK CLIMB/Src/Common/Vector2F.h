#pragma once

class Vector2;

class Vector2F
{
public:

	//デフォルトコンストラクタ
	Vector2F(void);

	//コンストラクタ
	Vector2F(float ix, float iy);

	//デストラクタ
	~Vector2F(void);

	//Vector2へ変換する関数
	Vector2 ToVector2(void);

	//ベクトル線を作る
	Vector2F CreateVectorLine(Vector2 value1, Vector2 value2);

	//Vector2F同士の比較
	bool IsVector2F(Vector2F value1, Vector2F value2);

	float x;
	float y;

private:
};