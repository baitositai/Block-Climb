#pragma once
#include "../,,/../../../Manager/SceneManager.h"
#include "SideBase.h"

class Side2:public SideBase
{
public:

	//サイド画像種類インデックス　
	static constexpr int SIDE_IMG_INDEX = 1;

	//ノーマルフォントサイズ
	static constexpr int NORMAL_FONT_SIZE = 28;

	//データフォントサイズ
	static constexpr int DATA_FONT_SIZE = 32;

	// 制限時間の分の最大値（3分制限）
	static constexpr int TIME_LIMIT_MAX_MINUTES = 3;

	//時間制限
	static constexpr int TIME_LIMIT = 180 * SceneManager::DEFAULT_FPS;

	// ボックスの枠の太さ
	static constexpr int SIDE_BOX_BORDER = 3;

	// ボックスのX方向マージン
	static constexpr int SIDE_BOX_INTERVAL_X = 5;

	// ボックスのY方向マージン
	static constexpr int SIDE_BOX_INTERVAL_Y = 10;

	// 1つ目のボックスのY座標
	static constexpr int BLOCK_COUNT_BOX_POS_Y = 150;

	// 2つ目のボックスのY座標（制限時間）
	static constexpr int TIME_LIMIT_BOX_POS_Y = 300;

	// ボックスの高さ
	static constexpr int SIDE_BOX_HEIGHT = 110;

	// ボックスの横幅調整値（マージンの倍数）
	static constexpr int SIDE_BOX_WIDTH_MARGIN = SIDE_BOX_INTERVAL_X * 8;

	// ボックスX座標オフセット倍率
	static constexpr int SIDE_BOX_POS_X_OFFSET = SIDE_BOX_INTERVAL_X * 4;

	// データ描画時のXオフセット倍率
	static constexpr int SIDE_DATA_OFFSET_X_RATE = 2;

	// データ描画時のYオフセット倍率（フォント＋マージン）
	static constexpr int SIDE_DATA_OFFSET_Y_RATE = 2;

	//コンストラクタ
	Side2();

	//デストラクタ
	~Side2();

	//フォント設定
	void SetFont() override;

	//リセット
	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw(void) override;

private:

	int minute_;
	int second_;
};

