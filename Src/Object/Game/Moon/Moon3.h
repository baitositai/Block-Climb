#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon3 : public Moon
{
public:

	//移動速度
	static constexpr float MOVE_SPEED = 3.0f;

	//間隔
	static constexpr int INTERVAL = 5;

	

	//生成のランダム秒数
	static constexpr int CREATE_RAND_MAX_SECOND = 3;

	//拡大速度
	static constexpr float EXPANSION_SPEED = 0.2f;

	//コンストラクタ
	Moon3();

	//デストラクタ
	~Moon3();

	//リセット
	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

private:

	int cnt_;

	//移動回数
	int downCnt_;

	//出現カウント
	int respawn_;

	//アルファ値
	int alpha_;

	//スピード
	float move_;

};

