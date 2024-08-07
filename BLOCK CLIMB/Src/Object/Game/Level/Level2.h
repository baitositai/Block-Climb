#pragma once
#include "LevelManager.h"

class Moon;

class Level2 :public LevelManager
{
public:

	void AddInit()override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;
	void SetParam() override;
	void HitMoon();

	Moon* GetMoonInstans() override;

private:

	Moon* moon_;
};