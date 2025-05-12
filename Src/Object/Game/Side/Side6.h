#pragma once
#include "SideBase.h"

class Side6 :public SideBase
{
public:

	//サイド画像インデックス
	static constexpr int SIDE_IMG_INDEX = 5;

	//X方向の間隔
	static constexpr int INTERVAL_X = 5;

	//Y方向の間隔
	static constexpr int INTERVAL_Y = 10;

	//四角形の枠の太さ
	static constexpr int BOX_BORDER = 3;

	//ボックスのX方向余白（intervalX × 倍数）
	static constexpr int BOX_MARGIN_X_COUNT = 8;

	//ボックスのY位置
	static constexpr int BOX_POS_Y = 150;

	//ボックスの高さ
	static constexpr int BOX_HEIGHT = 120;

	//ボックスの横方向の余白合計（左右）
	static constexpr int BOX_WIDTH_MARGIN_COUNT = 16;

	//アイコンボックスのXオフセット
	static constexpr int ICON_BOX_OFFSET_X = 64;

	//アイコンボックスのY位置
	static constexpr int ICON_BOX_POS_Y = 150;

	//アイコンボックスの幅
	static constexpr int ICON_BOX_WIDTH = 128;

	//アイコンボックスの高さ
	static constexpr int ICON_BOX_HEIGHT = 128;

	//リセット
	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw(void) override;

	//高さ描画
	void HeightDraw();

	//アイコン描画
	void IconDraw();
};

