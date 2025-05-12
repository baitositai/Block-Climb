#pragma once
#include "../,,/../../../Manager/SceneManager.h"
#include "SideBase.h"

class Side5:public SideBase
{
public:

	static constexpr int TIME_LIMIT = 300 * SceneManager::DEFAULT_FPS;

	void SetFont() override;
	void Reset() override;
	void Update() override;
	void Draw(void) override;

private:
	int minitu_;
	int second_;

};

