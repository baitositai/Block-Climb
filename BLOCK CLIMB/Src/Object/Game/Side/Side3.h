#pragma once
#include "SideBase.h"

class Side3:public SideBase
{
public:

	void SetFont() override;
	void Reset() override;
	void Draw(void) override;

private:
};

