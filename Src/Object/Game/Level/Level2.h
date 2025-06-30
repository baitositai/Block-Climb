#pragma once
#include "LevelManager.h"

class Moon;

class Level2 :public LevelManager
{
public:

	static constexpr float PLAYER_JUMP_BUFF = 1.2f;             // プレイヤーのジャンプ力のバフ倍率

	static constexpr int FIELD_WIDTH = 10;                         // フィールドの横のブロック数
	static constexpr int FIELD_HEIGHT = 12;                        // フィールドの縦のブロック数

	static constexpr int GROUND_WIDTH = 18;                        // 地面の横のブロック数
	static constexpr int GROUND_HEIGHT = 6;                        // 地面の縦のブロック数

	static constexpr int STAGE_EXTRA_HEIGHT = 3;                   // ステージの縦方向の追加分

	static constexpr int PLAYER_OFFSET_X = 50;                     // プレイヤーの初期位置の横のずれ
	static constexpr int PLAYER_OFFSET_Y_BLOCK = 2;                // プレイヤーの初期位置の縦のブロック位置
	static constexpr int PLAYER_PIXEL_ADJUST_Y = 8;                // プレイヤーの縦の微調整

	static constexpr int CAMERA_OFFSET_BLOCK_Y = 2;                // カメラの縦方向のブロックオフセット

	static constexpr int GOAL_OFFSET_X = 75;                       // ゴールの横方向のオフセット
	static constexpr int GOAL_POS_Y = 600;                         // ゴールの縦方向の座標

	//コンストラクタ
	Level2(void);

	//デストラクタ
	~Level2(void);

	//追加初期化
	void AddInit()override;

	//更新
	void Update(void) override;

	//描画
	void Draw(void) override;

	//解放
	void Release(void) override;

	//パラメーターの設定
	void SetParam() override;

	//月との衝突判定
	void HitMoon();

	//月を返す
	Moon* GetMoonInstans() override;

private:

	Moon* moon_;
};