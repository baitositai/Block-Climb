#pragma once
#include "BlockBase.h"


class Block1 :public BlockBase
{
public:
	void Reset(void) override;
	void StageCreate(void) override;
};

