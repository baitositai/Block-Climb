#pragma once
#include "../../Application.h"
#include "../../Common/Vector2.h"

class GameScene;

class GameClear
{
public:

	//画像サイズ
	static constexpr int SIZE_X = 491;
	static constexpr int SIZE_Y = 206;

	//揺らす周波数
	static constexpr float AMPLITUDE = 1.0f;

	//揺らす振幅
	static constexpr float FREQUENCY = 10.0f;

	//座標位置
	static constexpr int POS_X = Application::SCREEN_SIZE_X / 2 - SIZE_X / 2;
	static constexpr int POS_Y = Application::SCREEN_SIZE_Y / 2 - SIZE_Y / 2;

	//コンストラクタ
	GameClear();

	//デストラクタ
	~GameClear();

	// 初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

	//解放
	void Release();

private:

	//画像の格納
	int imgClear_;

	//描画用座標
	Vector2 pos_;

};

