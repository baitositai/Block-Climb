#pragma once
#include "SideBase.h"

class SideMarason:public SideBase
{
public:

	//X方向の間隔
	static constexpr int INTERVAL_X = 5;

	//Y方向の間隔
	static constexpr int INTERVAL_Y = 10;

	//フチの太さ
	static constexpr int BOX_BORDER = 3;

	//高さ表示ボックスのY座標
	static constexpr int HEIGHT_BOX_POS_Y = 310;

	//高さ表示ボックスの高さ
	static constexpr int HEIGHT_BOX_SIZE_Y = 120;

	//アイコンボックスのXオフセット
	static constexpr int ICON_BOX_OFFSET_X = 64;

	//アイコンボックスのY座標
	static constexpr int ICON_BOX_POS_Y = 150;

	//アイコンボックスのサイズ
	static constexpr int ICON_BOX_SIZE = 128;

	//高さボックスのX座標調整
	static constexpr int HEIGHT_BOX_OFFSET_X_RATE = 8;

	//高さボックスの横幅調整
	static constexpr int HEIGHT_BOX_WIDTH_OFFSET_RATE = 16;

	void Reset() override;
	void Update() override;
	void Draw(void) override;

	void HeightDraw();
	void IconDraw();

private:
};

