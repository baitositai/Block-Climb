#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon6 : public Moon
{
public:

	static constexpr float MOVE_SPEED = 3.0f;
	static constexpr int INTERVAL = 5;

	Moon6();
	~Moon6();

	void Reset() override;
	void Update() override;
	void Draw() override;	

	//黒い月の動きランダム決定
	DARK_MOVE RandamDarkMove();

	//座標のリセット
	Vector2F ResetPos();

	//スピードのリセット
	Vector2F ResetSpeed();
	
	//黒い月の処理
	void DarkMoonUpdate(void);
	void DarkMoonDraw(void);


	//黄色月の処理
	void GoalMoonUpdate(void);
	void GoalMoonDraw(void);

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

