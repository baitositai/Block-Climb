#pragma once
#include "BlockBase.h"
#include "../../../Common/Vector2F.h"
#include "../../../Manager/SceneManager.h"

class BlockShower:public BlockBase
{
public:

	//角度
	static constexpr float ANGLE[MINO_TYPES][MINO_HEIGHT][MINO_WIDTH] = {
		{	//I
			{0,-DX_PI_F / 7 + DX_PI_F,0,0},
			{0,DX_PI_F / 2,0,0},
			{0,DX_PI_F / 7,0,0},
			{0,DX_PI_F / 14,0,0}
		},
		//O
			{
			{0,0,0,0},
			{0,DX_PI_F / 4,DX_PI_F / 4 + DX_PI_F / 2,0},
			{0,DX_PI_F / 4 - DX_PI_F / 2,DX_PI_F / 4 - DX_PI_F,0},
			{0,0,0,0}
		
		},
		//S
			{
			{0,0,0,0},
			{0,DX_PI_F,0,0},
			{-DX_PI_F / 5.5 - DX_PI_F,DX_PI_F / 7 + DX_PI_F / 2,0,0},
			{0,0,0,0}
			
		},
		//Z
			{
			{0,0,0,0},
			{DX_PI_F,DX_PI_F,0,0},
			{0,DX_PI_F / 7 + DX_PI_F / 2,-DX_PI_F / 7 + DX_PI_F / 2,0},
			{0,0,0,0}
			
		},
		//J
			{
			{0,0,DX_PI_F / 5.5 - DX_PI_F / 2,0},
			{0,0,-DX_PI_F / 6.5,0},
			{0,DX_PI_F / 2,DX_PI_F / 6.5,0},
			{0,0,0,0}
		},
		//L
			{
			{0,0,0,0},
			{0,0,0,0},
			{0,DX_PI_F,DX_PI_F / 7 + DX_PI_F / 2,0},
			{0,0,0,0}
		},
		//T
			{
			{0,0,0,0},
			{DX_PI_F,DX_PI_F,0,0},
			{0,DX_PI_F / 7 + DX_PI_F / 2,-DX_PI_F / 8 + DX_PI_F / 2,0},
			{0,0,0,0}
		}
	};

	//中心点用相対座標
	static constexpr int MINO_LOCAL_POS_X[MINO_TYPES] = {
		BLOCK_SIZE_X,
		static_cast<int>(BLOCK_SIZE_X * 1.5f),
		BLOCK_SIZE_X,
		BLOCK_SIZE_X,
		static_cast<int>(BLOCK_SIZE_X * 1.5f),
		static_cast<int>(BLOCK_SIZE_X * 1.5f),
		BLOCK_SIZE_X};

	static constexpr int MINO_LOCAL_POS_Y[MINO_TYPES] = {
		static_cast<int>(BLOCK_SIZE_Y * 1.5f),
		static_cast<int>(BLOCK_SIZE_Y * 1.5f),
		static_cast<int>(BLOCK_SIZE_Y * 1.5f),
		static_cast<int>(BLOCK_SIZE_Y * 1.5f),
		BLOCK_SIZE_Y,
		BLOCK_SIZE_Y,
		static_cast<int>(BLOCK_SIZE_Y * 1.5f)};

	//降下スピード
	static constexpr float SHOWER_SPEED = 1.5f;

	//回転速度
	static constexpr float ROTATION_SPEED = 0.02f;

	//削除ライン
	static constexpr int DELETE_LINE = Application::SCREEN_SIZE_Y + BLOCK_SIZE_X * 4;

	BlockShower();
	~BlockShower();

	void Create();
	void Update() override;
	void Draw() override;

	//変数初期化
	void Reset();

	//回転処理
	Vector2F RotatePosition(Vector2F centerPos, float angle, Vector2F pos);

private:

	//時間進行用ステップ
	float step_;

	float angle_[MINO_HEIGHT][MINO_WIDTH];
	
	Vector2F blockPos_[MINO_HEIGHT][MINO_WIDTH];

	//回転用中心座標
	Vector2F rotaCenterPos_;

	//種類ごとに中心点や角度設定
	void InitMino();
};

