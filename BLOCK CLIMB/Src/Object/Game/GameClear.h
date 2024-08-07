#pragma once
#include "../../Common/Vector2.h"

class GameScene;

class GameClear
{
public:

	//画像サイズ
	static constexpr int SIZE_X = 491;
	static constexpr int SIZE_Y = 206;

	GameClear(void);
	~GameClear(void);

	void Init(GameScene* parent);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	//画像の格納
	int imgClear_;

	//描画用座標
	Vector2 pos_;

	//インスタンス
	GameScene* gameScene_;

};

