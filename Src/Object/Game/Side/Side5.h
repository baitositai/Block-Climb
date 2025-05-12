#pragma once
#include "../,,/../../../Manager/SceneManager.h"
#include "SideBase.h"

class Side5:public SideBase
{
public:

	//サイド画像インデックス
	static constexpr int SIDE_IMG_INDEX = 4;

	//時間制限
	static constexpr int TIME_LIMIT = 300 * SceneManager::DEFAULT_FPS;

	//ノーマルフォントサイズ
	static constexpr int NORMAL_FONT_SIZE = 28;

	//データフォントサイズ
	static constexpr int DATA_FONT_SIZE = 32;

	// 制限時間の分の最大値（5分制限）
	static constexpr int TIME_LIMIT_MAX_MINUTES = 5;

	//四角形の枠の太さ
	static constexpr int BOX_BORDER = 3;

	//X方向の間隔
	static constexpr int INTERVAL_X = 5;

	//Y方向の間隔
	static constexpr int INTERVAL_Y = 10;

	//一つ目のボックスのX方向余白（intervalX × 倍数）
	static constexpr int BOX1_MARGIN_X_COUNT = 4;

	//一つ目のボックスのY位置
	static constexpr int BOX1_POS_Y = 150;

	//一つ目のボックスの高さ
	static constexpr int BOX1_HEIGHT = 110;

	//一つ目のボックスの横方向の余白合計（左右）
	static constexpr int BOX1_WIDTH_MARGIN_COUNT = 8;

	//二つ目のボックスのY位置
	static constexpr int BOX2_POS_Y = 300;

	//二つ目のボックスの高さ
	static constexpr int BOX2_HEIGHT = 110;

	//フォント設定
	void SetFont() override;

	//リセット
	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw(void) override;

private:
	int minitu_;
	int second_;

};

