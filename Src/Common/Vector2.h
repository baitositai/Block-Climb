#pragma once

class Vector2F;

class Vector2
{
public:

	int x;
	int y;

	// コンストラクタ
	Vector2(void);

	// コンストラクタ
	Vector2(int vX, int vY);

	// デストラクタ
	~Vector2(void);

	//Vector2Fへ変換する関数
	Vector2F ToVector2F(void);

};
