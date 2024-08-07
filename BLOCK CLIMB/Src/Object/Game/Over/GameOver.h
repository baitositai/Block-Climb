#pragma once
#include "../../../Common/Vector2.h"

class GameScene;

class GameOver
{
public:

	//画像サイズ
	static constexpr int SIZE_X = 762;
	static constexpr int SIZE_Y = 203;

	GameOver(void);
	~GameOver(void);

	void Init(GameScene* parent);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);

protected:

	//インスタンス
	GameScene* gameScene_;

private:

	//画像の格納
	int imgOver_;

	//描画用座標
	Vector2 pos_;
};

