#pragma once
#include "LevelManager.h"


class Level1:public LevelManager
{
	void AddInit()override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void SetParam() override;
};

