#pragma once
#include "../../Common/Vector2F.h"
#include "../../Application.h"

class BackGround
{
public:
	//背景の種類
	enum class TYPE
	{
		SKY,
		NIGHT,
		SUNSET,
		MAX
	};

	//背景の画像サイズ
	static constexpr int IMAGE_SIZE_X = 1864;	
	static constexpr int IMAGE_SIZE_Y = 720;	

	//背景の描画数
	static constexpr int DRAW_IMAGES = 2;

	//スクロールスピード
	static constexpr float SCR_SPEED = 0.5f;

	//スカイスタート
	static constexpr int SKY_START = 8;

	//スカイ終わり
	static constexpr int SKY_FIN = 15;	
	
	//サンセット回数
	static constexpr int SUN_NUM = 2;

	//サンセットスタート
	static constexpr int SUN_START[SUN_NUM] = { 16,5 };

	//サンセット終わり
	static constexpr int SUN_FIN[SUN_NUM] = { 19,7 };

	//背景スクロール最大値
	static constexpr float SCROLL_MAX = IMAGE_SIZE_X;
	
	BackGround(void);							//コンストラクタ
	~BackGround(void);							//デストラクタ

	void Init(void);							//初期化
	virtual void Update(void);					//更新処理（毎度実行）
	virtual void Draw(void);					//描画処理（毎度実行）
	void Release(void);							//解放処理 (終了時一回のみ実行)

	//変数の初期化
	virtual void Reset();

private:

	//画像の格納用
	int imgSky_[static_cast<int>(TYPE::MAX)];

	//背景の種類の格納
	int skyType_;

	//スクロール用変数
	Vector2F drawPos_[DRAW_IMAGES];
	float scrollSpeed_;

	//画像の読み込み
	void Load();

};

