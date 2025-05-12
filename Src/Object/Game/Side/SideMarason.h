#pragma once
#include "SideBase.h"

class SideMarason:public SideBase
{
public:

	void Reset() override;
	void Update() override;
	void Draw(void) override;

	void HeightDraw();
	void IconDraw();

private:
};

