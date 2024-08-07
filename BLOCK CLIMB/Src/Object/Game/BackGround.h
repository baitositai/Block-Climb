#pragma once
#include "../../Common/Vector2F.h"
#include "../../Application.h"

class LevelManager;

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

#pragma region  背景画像関連
	//背景の画像サイズ
	static constexpr int IMAGE_SIZE_X = 1864;	
	static constexpr int IMAGE_SIZE_Y = 720;	

	//背景の描画数
	static constexpr int DRAW_IMAGES = 2;

	//背景スクロール最大値
	static constexpr float SCROLL_MAX = IMAGE_SIZE_X;
#pragma endregion
	
	BackGround(void);							//コンストラクタ
	~BackGround(void);							//デストラクタ

	void Init(LevelManager* parent);			//初期化処理（最初の一回のみ実行)
	virtual void Update(void);					//更新処理（毎度実行）
	virtual void Draw(void);					//描画処理（毎度実行）
	void Release(void);							//解放処理 (終了時一回のみ実行)

	virtual void Reset();

	//画像の読み込み
	void Load();

protected:

	//画像の格納用
	int imgSky_[static_cast<int>(TYPE::MAX)];

	//背景の種類の格納
	int skyType_;

private:

#pragma region 背景関連
	//スクロール用変数
	Vector2F drawPos_[DRAW_IMAGES];
	float scrollSpeed_;
#pragma endregion

	//インスタンス
	LevelManager* level_;

};

