#pragma once
#include "LevelManager.h"

class Moon;
class FireBall;

class Level5 :public LevelManager
{
public:

	static constexpr float PLAYER_JUMP_POW = 1.2f;					// プレイヤーのジャンプ力

	static constexpr int FIELD_WIDTH = 10;                          // フィールドの横のブロック数
	static constexpr int FIELD_HEIGHT = 12;                         // フィールドの縦のブロック数

	static constexpr int GROUND_WIDTH = 18;                         // 地面の横のブロック数
	static constexpr int GROUND_HEIGHT = 5;                         // 地面の縦のブロック数

	static constexpr int STAGE_GROUND_EXTRA_Y = 3;                  // ステージの縦サイズに加えるブロック数

	static constexpr int PLAYER_OFFSET_X = 50;                      // プレイヤーの初期位置の横方向の調整値
	static constexpr int PLAYER_OFFSET_BLOCK_Y = 2;                 // プレイヤーの初期位置の縦のブロック数オフセット
	static constexpr int PLAYER_PIXEL_ADJUST_Y = 8;                 // プレイヤーの縦方向の微調整に使うピクセル数

	static constexpr int CAMERA_OFFSET_BLOCK_Y = 2;                 // カメラの縦のブロック数オフセット

	static constexpr int GOAL_OFFSET_X = 75;                        // ゴールの横方向の調整値
	static constexpr int GOAL_POS_Y = 600;                          // ゴールの縦方向の位置

	//コンストラクタ
	Level5();

	//デストラクタ
	~Level5();

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

	//月の当たり判定
	void HitMoon();

	//火の玉の更新
	void FireBallUpdate();

	//火の玉生成
	void CreateFireBall();

	//火の玉を返す
	FireBall* GetValidFireBall();

	//月を返す
	Moon* GetMoonInstans() override;

private:

	int fireCnt_;

	Moon* moon_;

	//火の玉
	std::vector<FireBall*> fire_;
};