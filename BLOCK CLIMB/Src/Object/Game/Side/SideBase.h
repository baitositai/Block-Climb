#pragma once
#include "../../../Common/Vector2.h"

class LevelManager;

class SideBase
{
public:

#pragma region 画像関連
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
#pragma endregion

#pragma region フォント関連
	static constexpr int FONT_SIZE = 32;
	static constexpr int FONT_DATA_SIZE = 64;
#pragma endregion

	SideBase(void);							//コンストラクタ
	~SideBase(void);						//デストラクタ

	void Init(LevelManager* parent);		//初期化処理（最初の一回のみ実行)
	virtual void Reset();					//変数初期化処理
	virtual void Update(void);				//更新処理（毎度実行）
	virtual void Draw(void);				//描画処理（毎度実行）
	void Release(void);						//解放処理 (終了時一回のみ実行)

	//フォント設定
	virtual void SetFont();

	//ネクストミノ用箱の描画
	void NextMinoDraw();

	//ふちありの四角形描画
	void WBorderRectangle(Vector2 size, Vector2 pos, int border);

protected:
	
#pragma region 画像関連
	//画像の格納用
	int imgSideBlock_[SIDE_IMAGES];

	//サイド画面の種類
	int sideBlockType_;
#pragma endregion

#pragma region フォント関連
	//フォント
	int normalFont_;

	//数字用フォント
	int dataFont_;

	//フォントサイズ
	int nmlFontSize_;

	//数字用フォントサイズ
	int dataFontSize_;
#pragma endregion

#pragma region サイド画面関係
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
#pragma endregion

#pragma region 残り時間
	int time_;
#pragma endregion

	//インスタンス
	LevelManager* level_;

};

