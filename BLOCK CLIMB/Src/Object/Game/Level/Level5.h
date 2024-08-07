#pragma once
#include "LevelManager.h"

class Moon;
class FireBall;

class Level5 :public LevelManager
{
public:

	void AddInit()override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;
	void SetParam() override;
	void HitMoon();
	void FireBallUpdate();
	void CreateFireBall();
	FireBall* GetValidFireBall();
	Moon* GetMoonInstans() override;

private:

	int fireCnt_;

	Moon* moon_;

	//‰Î‚Ì‹Ê
	std::vector<FireBall*> fire_;
};