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
		NONE,
		UP,
		WAIT,
		EXIT,
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

	//コンストラクタ
	GameStart(void);

	//デストラクタ
	~GameStart(void);

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="parent"></param>親インスタンス
	void Init(GameScene* parent);

	//更新
	void Update(void);

	//描画
	void Draw(void);

	//解放
	void Release(void);

	//変数の初期化
	void Reset();

	//画像設定
	virtual void SetImage()  = 0;

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

