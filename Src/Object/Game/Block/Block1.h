#pragma once
#include "BlockBase.h"


class Block1 :public BlockBase
{
public:

	//コンストラクタ
	Block1();

	//デストラクタ
	~Block1();

	//リセット
	void Reset(void) override;

	//ステージ生成
	void StageCreate(void) override;
};

