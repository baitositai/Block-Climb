#pragma once
#include "SideBase.h"

class Side1:public SideBase
{
public:

	void Reset() override;
	void Update() override;
	void Draw(void) override;

private:
};

