#pragma once
#include "LevelManager.h"


class Level4:public LevelManager
{
public:

	static constexpr int FIELD_WIDTH = 16;                          // フィールドの横のブロック数
	static constexpr int FIELD_HEIGHT = 60;                         // フィールドの縦のブロック数

	static constexpr int GROUND_HEIGHT = 3;                         // 地面の縦のブロック数

	static constexpr int PLAYER_OFFSET_BLOCK_Y = 2;                 // プレイヤーの初期位置の縦のブロック数オフセット
	static constexpr int PLAYER_PIXEL_ADJUST_Y = 8;                 // プレイヤーの縦の微調整に使うピクセル数

	static constexpr int CAMERA_OFFSET_BLOCK_Y = 2;                 // カメラの初期位置の縦のブロック数オフセット

	static constexpr int GOAL_OFFSET_X = 75;                        // ゴールの横の位置の調整値
	static constexpr int GOAL_POS_Y = 300;                          // ゴールの縦の位置

	//コンストラクタ
	Level4();

	//デストラクタ
	~Level4();

	//追加初期化
	void AddInit()override;

	//更新
	void Update() override;
	
	//描画
	void Draw() override;
	
	//解放
	void Release() override;

	//パラメーターの設定
	void SetParam() override;

	//火の玉との衝突判定
	void FireBallCollision();
};

