#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon6 : public Moon
{
public:

	//移動速度
	static constexpr float MOVE_SPEED = 3.0f;

	//間隔
	static constexpr int INTERVAL = 5;

	//ゴール月位置調整用
	static constexpr int GOAL_MOON_HEIGHT_OFFSET = 80;

	//月の位置初期バックアップ値
	static constexpr int MOON_GOAL_PRE_BLOCK = 24;

	//月のスクロール速度
	static constexpr float MOON_SCROLL_SPEED = 2.0f;

	//月の行動高さ条件値
	static constexpr int DARK_MOON_TERM_HEIGHT = 20;	//黒月
	static constexpr int GOAL_MOON_TERM_HEIGHT = 70;	//ゴール

	//黒月オフセット
	static constexpr float DARK_POS_Y_OFFSET = 1.5f;

	//黒月のランダム月出現調整
	static constexpr int DARK_SCREEN_DIVISOR = 3;

	//ランダム落下用値
	static constexpr int RANDAM_MOON_DOWN_MIN = 2;
	static constexpr int RANDAM_MOON_DOWN_MAX = 4;

	//コンストラクタ
	Moon6();

	//デストラクタ
	~Moon6();

	//リセット
	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//黒い月の動きランダム決定
	DARK_MOVE RandamDarkMove();

	//座標のリセット
	Vector2F ResetPos();

	//スピードのリセット
	Vector2F ResetSpeed();
	
	//黒い月の処理
	void DarkMoonUpdate(void);	//更新
	void DarkMoonDraw(void);	//描画


	//黄色月の処理
	void GoalMoonUpdate(void);	//更新
	void GoalMoonDraw(void);	//描画

private:

	//停止カウント
	float stopCnt_;

	//移動回数
	int downCnt_;

	//出現カウント
	int respawn_;

	//アルファ値
	int alpha_;

	//ブロックの前値
	int preBlock_;

	float scroll_;
	float scrollSpeed_;
	float scrollMax_;

	//スピード
	Vector2F speed_;

};

