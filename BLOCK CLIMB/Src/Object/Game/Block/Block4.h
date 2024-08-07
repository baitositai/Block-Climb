#pragma once
#include "BlockBase.h"
#include "../Gimic/FireBall.h"


class Block4 :public BlockBase
{
public:
	//void Update(void) override;
	void HitUpdate(Vector2 pos) override;
	void Reset(void) override;
	void StageCreate(void) override;

	void CreateFireBall();

	int GenerationNumber();

	float FireBallSpeed();

	FireBall* GetValidFireBall();

public:
};

