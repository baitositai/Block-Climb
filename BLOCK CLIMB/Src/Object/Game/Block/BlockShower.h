#pragma once
#include "BlockBase.h"
#include "../../../Common/Vector2F.h"
#include "../../../Manager/SceneManager.h"

class BlockShower:public BlockBase
{
public:
	static constexpr float SHOWER_SPEED = 1.5f;
	static constexpr float ROTATION_SPEED = 0.02f;

	BlockShower();
	~BlockShower();

	void Create();
	void Update() override;
	void Draw() override;

	//変数初期化
	void Reset();

	//回転処理
	Vector2F RotatePosition(Vector2F centerPos, float angle, Vector2F pos);

	//回転用中心座標の取得
	Vector2F GetRotationPos();
private:

	//時間進行用ステップ
	float step_;

	float angle_[MINO_HEIGHT][MINO_WIDTH];
	
	Vector2F blockPos_[MINO_HEIGHT][MINO_WIDTH];

	//回転用中心座標
	Vector2F rotaCenterPos_;
};

