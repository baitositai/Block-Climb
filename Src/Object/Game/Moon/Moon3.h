#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon3 : public Moon
{
public:

	static constexpr float MOVE_SPEED = 3.0f;
	static constexpr int INTERVAL = 5;

	Moon3();
	~Moon3();

	void Reset() override;
	void Update() override;
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

