#pragma once
#include <string>
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"

class GameScene;

class GameStart
{
public:
	enum class STATE
	{
		UP,
		WAIT,
		EXIT
	};

	//画像サイズ
	static constexpr int SIZE_X = 491;
	static constexpr int SIZE_Y = 206;

	//画像拡大量
	static constexpr float EXPANSION = 0.05f;
	static constexpr float EXPANSION_MAX = 1.0f;

	//待ち秒数
	static constexpr float WAIT_SECOND = 1.5f;

	//座標移動速度
	static constexpr float MOVE_SPEED = 0.02f;

	//回転量
	static constexpr float ROTATION = 0.33f;


	GameStart(void);
	~GameStart(void);

	void Init(GameScene* parent);
	void Update(void);
	void Draw(void);
	void Release(void);


	void Reset();
	virtual void SetImage();

protected:

	//画像の格納
	int imgStart_;

	//画像の大きさ
	Vector2 size_;

	//画像拡大サイズ
	float expansion_;

	//画像回転用
	float angle_;

	//待ち用カウント変数
	int cnt_;

	//状態格納
	STATE state_;

	//描画用座標
	Vector2F pos_;

	//インスタンス
	GameScene* gameScene_;

};

