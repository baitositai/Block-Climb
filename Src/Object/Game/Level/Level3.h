#pragma once
#include "LevelManager.h"

class Blast;
class Moon;

class Level3 :public LevelManager
{
public:

	static constexpr int FIELD_WIDTH = 16;                          // フィールドの横のブロック数
	static constexpr int FIELD_HEIGHT = 12;                         // フィールドの縦のブロック数

	static constexpr int GROUND_HEIGHT = 3;                         // 地面の縦のブロック数

	static constexpr int PLAYER_START_BLOCK_OFFSET_Y = 2;           // プレイヤーの縦の位置のブロック数オフセット
	static constexpr int PLAYER_PIXEL_OFFSET_Y = 8;                 // プレイヤーの縦のピクセル調整

	static constexpr int CAMERA_BLOCK_OFFSET_Y = 2;                 // カメラの縦方向のブロックオフセット

	static constexpr int GOAL_OFFSET_X = 75;                        // ゴールの横のオフセット
	static constexpr int GOAL_POS_Y = 600;                          // ゴールの縦の位置

	//コンストラクタ
	Level3(void);

	//デストラクタ
	~Level3(void);

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

	//月の当たり判定
	void HitMoon();

private:
	Moon* moon_;
	std::vector<Blast*> blast_;
	bool isBlast_; //爆発中か確認
};

