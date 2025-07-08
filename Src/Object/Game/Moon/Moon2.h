#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon2 : public Moon
{
public:

	//赤い月の定位置
	static constexpr int RED_MOON_DEFAULT_POS_X = 75;
	static constexpr int RED_MOON_DEFAULT_POS_Y = 250;

	//青い対の定位置
	static constexpr int BLUE_MOON_DEFAULT_POS_X = static_cast<float>(Application::SCREEN_SIZE_X - 75);
	static constexpr int BLUE_MOON_DEFAULT_POS_Y = 250;

	//処理する月の数
	static constexpr int UPD_MOONS = 2;

	//コンストラクタ
	Moon2();

	//デストラクタ
	~Moon2();

	//リセット
	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

};


