#pragma once
#include "SideBase.h"

class Side4:public SideBase
{
public:
	//ブロック情報表示エリアの横方向の余白
	static constexpr int INTERVAL_X = 5;

	//ブロック情報表示エリアの縦方向の余白
	static constexpr int INTERVAL_Y = 10;

	//ブロック情報表示エリアの枠の太さ
	static constexpr int BOX_BORDER = 3;

	//ブロック情報表示エリアの高さ
	static constexpr int BOX_HEIGHT = 120;

	//ブロック情報表示エリアの位置Y
	static constexpr int BOX_POS_Y = 150;

	//ブロック情報表示エリアの横方向の余白の個数（右）
	static constexpr int BOX_MARGIN_X_COUNT = 8;

	//ブロック情報表示エリアの横方向の余白の個数（両側合計）
	static constexpr int BOX_WIDTH_MARGIN_COUNT = 16;

	//サイド画像種類インデックス　
	static constexpr int SIDE_IMG_INDEX = 3;

	//リセット
	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw(void) override;

private:
};

