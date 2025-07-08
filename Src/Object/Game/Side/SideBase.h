#pragma once
#include "../../../Common/Vector2.h"

class LevelManager;

class SideBase
{
public:

	//フォントサイズ
	static constexpr int FONT_SIZE = 32;

	//フォント太さ
	static constexpr int FONT_THICK = 3;

	//サイド画面に用いる画像サイズ
	static constexpr int SIDE_IMAGE_SIZE_X = 50;
	static constexpr int SIDE_IMAGE_SIZE_Y = 50;

	static constexpr int SIDE_DRAW_SIZE_X = 48;
	static constexpr int SIDE_DRAW_SIZE_Y = 48;

	//画像分割数数
	static constexpr int SIDE_IMAGES_X = 7;
	static constexpr int SIDE_IMAGES_Y = 1;

	//種類総数
	static constexpr int SIDE_IMAGES = SIDE_IMAGES_X * SIDE_IMAGES_Y;

	//描画ブロック数（横）
	static constexpr int DRAW_BLOCK_X = 8;

	//描画ブロック数の余分な縦追加数
	static constexpr int DRAW_BLOCK_Y_EXTRA = 2;

	//サイドブロックの初期タイプ
	static constexpr int INIT_SIDE_BLOCK_TYPE = 0;

	//右端位置の補正値
	static constexpr int RIGHT_POS_OFFSET = 5;

	//フォントデータサイズ
	static constexpr int FONT_DATA_SIZE = 64;

	// Nextブロック表示枠のボーダーサイズ
	static constexpr int NEXT_BLOCK_BORDER = 3;

	// Nextブロック表示の間隔
	static constexpr int NEXT_BLOCK_INTERVAL_X = 40;
	static constexpr int NEXT_BLOCK_INTERVAL_Y = 20;

	// Nextブロック表示枠の位置
	static constexpr int NEXT_BLOCK_BOX_POS_X = NEXT_BLOCK_INTERVAL_X;
	static constexpr int NEXT_BLOCK_BOX_POS_Y = 150;

	// Nextブロック表示枠のサイズ
	static constexpr int NEXT_BLOCK_BOX_SIZE_X = 160; // 値は実行時に調整されているが仮で設定
	static constexpr int NEXT_BLOCK_BOX_SIZE_Y = 220;

	//NextブロックのY方向オフセット倍率
	static constexpr int NEXT_BLOCK_Y_OFFSET_RATE = 3;

	//時間
	static constexpr int SECONDS_IN_AN_HOUR = 3600;
	static constexpr int SECONDS_IN_A_MINUTE = 60;

	//コンストラクタ
	SideBase(void);	
	
	//デストラクタ						
	~SideBase(void);						

	//初期化処理（最初の一回のみ実行)
	void Init(LevelManager* parent);
	
	//変数初期化処理		
	virtual void Reset();		
	
	//更新処理（毎度実行）			
	virtual void Update(void);		
	
	//描画処理（毎度実行）		
	virtual void Draw(void);					
	
	//解放処理 (終了時一回のみ実行)
	void Release(void);					

	//フォント設定
	virtual void SetFont();

	//ネクストミノ用箱の描画
	void NextMinoDraw();

	//ふちありの四角形描画
	void WBorderRectangle(Vector2 size, Vector2 pos, int border);

protected:
	
	//画像の格納用
	int imgSideBlock_[SIDE_IMAGES];

	//サイド画面の種類
	int sideBlockType_;

	//フォント
	int normalFont_;

	//数字用フォント
	int dataFont_;

	//フォントサイズ
	int nmlFontSize_;

	//数字用フォントサイズ
	int dataFontSize_;

	//ブロックの描画数
	int drawBlockX;
	int drawBlockY;

	//中心に描画用の調整値
	Vector2 center_;

	//サイド画面を除くゲーム画面のサイズ
	Vector2 gameSize_;

	//右始点
	Vector2 rightPos_;

	//右サイドのサイズ
	Vector2 rightSideSize_;

	//左始点
	Vector2 leftPos_;

	//左サイドのサイズ
	Vector2 leftSideSize_;

	//時間
	int time_;

	//インスタンス
	LevelManager* level_;

};

