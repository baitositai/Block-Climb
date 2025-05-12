#pragma once
#include "BlockBase.h"
#include "../Gimic/FireBall.h"


class Block4 :public BlockBase
{
public:

	//火の玉生成に関する要素数
	static constexpr int FIREBALL_RULE_SIZE = 3;

	// 高さしきい値（降順）
	static constexpr int FIREBALL_HEIGHT_THRESHOLDS[FIREBALL_RULE_SIZE] = {
		30, 15, 0
	};

	// 対応する生成数
	static constexpr int FIREBALL_COUNTS[FIREBALL_RULE_SIZE] = {
		3, 2, 1
	};	
	
	// 要素数
	static constexpr int FIREBALL_SPEED_RULE_SIZE = 2;


	// 高さしきい値（降順）
	static constexpr int FIREBALL_SPEED_HEIGHT_THRESHOLDS[FIREBALL_SPEED_RULE_SIZE] = {
		40, 0
	};

	// 対応する火の玉の落下速度
	static constexpr float FIREBALL_SPEEDS[FIREBALL_SPEED_RULE_SIZE] = {
		5.0f, 3.0f
	};

	//コンストラクタ
	Block4();

	//デストラクタ
	~Block4();

	//所と辻の更新処理
	void HitUpdate(Vector2 pos) override;

	//リセット
	void Reset(void) override;

	//ステージ生成処理
	void StageCreate(void) override;

	//火の玉生成
	void CreateFireBall();

	//高さごとの火の玉の生成数を返す
	int GenerationNumber();

	//高さごとの火の玉のスピードを設定
	float FireBallSpeed();

	//火の玉を生成して返す
	FireBall* GetValidFireBall();
};

