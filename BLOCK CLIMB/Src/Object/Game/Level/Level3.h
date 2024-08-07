#pragma once
#include "LevelManager.h"

class Blast;
class Moon;

class Level3 :public LevelManager
{
public:

	void AddInit()override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void SetParam() override;

	//ŒŽ‚Ì“–‚½‚è”»’è
	void HitMoon();

private:
	Moon* moon_;
	std::vector<Blast*> blast_;
	bool isBlast_; //”š”­’†‚©Šm”F
};

