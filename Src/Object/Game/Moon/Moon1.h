#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon1 : public Moon
{
public:

	//コンストラクタ
	Moon1();

	//デストラクタ
	~Moon1();

	//リセット
	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

};

