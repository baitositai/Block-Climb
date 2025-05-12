#pragma once
#include "SideBase.h"

class Side1:public SideBase
{
public:

	//サイド画像種類インデックス　
	static constexpr int SIDE_IMG_INDEX = 0;

	//右ボックスのX方向マージン
	static constexpr int BOX_MARGIN_X = 5;

	//右ボックスのY方向マージン
	static constexpr int BOX_MARGIN_Y = 10;

	//右ボックスの枠の太さ
	static constexpr int BOX_BORDER = 3;

	//右ボックスの表示位置（Y座標）
	static constexpr int BOX_POS_Y = 150;

	//右ボックスの高さ
	static constexpr int BOX_HEIGHT = 120;

	//右ボックスの幅調整値（X方向のマージン合計）
	static constexpr int BOX_WIDTH_MARGIN_TOTAL = BOX_MARGIN_X * 16;

	//右ボックスの表示位置Xの調整倍率
	static constexpr int BOX_POS_X_OFFSET_RATE = 8;

	//データ表示のオフセット倍率
	static constexpr int DATA_POS_X_OFFSET_RATE = 2;

	//コンストラクタ
	Side1();

	//デストラクタ
	~Side1();

	//リセット
	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw(void) override;
};

