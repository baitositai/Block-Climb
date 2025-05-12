#pragma once
#include "LevelManager.h"


class Level1:public LevelManager
{
public:

	static constexpr int FIELD_WIDTH = 16;                          // フィールドの横幅（ブロック数）
	static constexpr int FIELD_HEIGHT = 30;                         // フィールドの縦幅（ブロック数）
	static constexpr int GROUND_HEIGHT = 3;                         // 地面の縦幅（ブロック数）
	static constexpr int PLAYER_START_OFFSET_Y = 2;                 // プレイヤー初期位置のY軸補正（下から何ブロック目）
	static constexpr int PLAYER_PIXEL_OFFSET_Y = 8;                 // プレイヤー初期位置の微調整（ピクセル）
	static constexpr int CAMERA_OFFSET_Y_BLOCKS = 2;                // カメラY軸オフセット（ブロック単位）
	static constexpr int GOAL_OFFSET_X = 75;                        // ゴールのX座標補正（画面中央からのずれ）
	static constexpr int GOAL_POS_Y = 150;                          // ゴールのY座標
	static constexpr int DRAW_CENTER_BLOCK_OFFSET_X = 1;            // 描画中心のX補正（1ブロック分右にずらす）

	//コンストラクタ
	Level1(void);

	//デストラクタ
	~Level1(void);

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
};

