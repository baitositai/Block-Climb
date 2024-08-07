#pragma once
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"

class LevelManager;

class FireBall
{
public:

	enum class STATE
	{
		FIRE,
		BLAST,
		NONE
	};

	//画像の分割
	static constexpr int WIDTH = 4;
	static constexpr int HEIGHT = 1;

	//画像サイズ
	static constexpr int SIZE_X = 48;
	static constexpr int SIZE_Y = SIZE_X;

	//アニメーション数
	static constexpr int ANIM_NUM = WIDTH * HEIGHT;

	//衝突判定用半径
	static constexpr float RADIUS = 16.0f;

	FireBall();
	~FireBall();

	void Create(LevelManager* parent, float speed);
	void Update();
	void Draw();
	void Release();

	void Load();
	void Reset();

	//座標をセットする
	void SetPos(Vector2F pos);

	//ステートの変更
	void SetState(STATE state);

	//座標を返す
	Vector2F GetPos();

	//ステートを返す
	STATE GetState();

private:

	//画像
	int imgFireBall_[static_cast<int>(STATE::NONE)][ANIM_NUM];

	//アニメーションカウント
	int cntAnim_;

	//表示しているアニメーション値
	int idxAnim_;

	//スピード
	float speed_;

	//爆発のアニメーション速度
	float animSpeed_;

	//ステート
	STATE state_;

	//座標
	Vector2F pos_;

	//インスタンス
	LevelManager* level_;
	
};

