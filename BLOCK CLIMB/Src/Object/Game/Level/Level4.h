#pragma once
#include "LevelManager.h"


class Level4:public LevelManager
{
	void AddInit()override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void SetParam() override;
	void FireBallCollision();
};

