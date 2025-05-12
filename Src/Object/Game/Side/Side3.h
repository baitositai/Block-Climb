#pragma once
#include "SideBase.h"

class Side3:public SideBase
{
public:

	//サイド画像種類インデックス　
	static constexpr int SIDE_IMG_INDEX = 2;

	//ノーマルフォントサイズ
	static constexpr int NORMAL_FONT_SIZE = 28;

	//データフォントサイズ
	static constexpr int DATA_FONT_SIZE = 48;

	//箱位置Y座標
	static constexpr int BOX_POS_Y = 150;

	// ボックスの枠線の太さ
	static constexpr int SIDE_BOX_BORDER = 3;

	// ボックス内の横の余白
	static constexpr int SIDE_BOX_INTERVAL_X = 5;

	// ボックス内の縦の余白
	static constexpr int SIDE_BOX_INTERVAL_Y = 10;

	// サイドボックスの縦サイズ
	static constexpr int SIDE_BOX_HEIGHT = 110;

	// ボックスX座標調整（右端からの余白）
	static constexpr int SIDE_BOX_RIGHT_OFFSET_X = SIDE_BOX_INTERVAL_X * 4;

	// ボックス幅調整
	static constexpr int SIDE_BOX_WIDTH_MARGIN = SIDE_BOX_INTERVAL_X * 8;

	//コンストラクタ
	Side3();

	//デストラクタ
	~Side3();

	void SetFont() override;
	void Reset() override;
	void Draw(void) override;

};

