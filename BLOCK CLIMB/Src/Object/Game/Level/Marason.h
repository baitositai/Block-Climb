#pragma once
#include "LevelManager.h"

class Blast;
class FireBall;
class RabbitText;

class Marason :public LevelManager
{
	static constexpr int ADD_LINE = 8;

	void Init(GameScene* parent) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;
	void SetParam() override;

	void ShiftGame() override;

	//イベント発生の処理
	void GameEvent();

#pragma region ファイアーボール
	//火の玉の処理
	void FireBallUpdate();

	//ファイアーボール生成
	void CreateFireBall();

	void SetTimeCount(int value);

	FireBall* GetValidFireBall();
#pragma endregion 

	//爆発処理
	void BlastUpdate();

	//状態変化のカウント処理
	bool PlayerSpeedCount();

	//プレイヤー状態変化用カウントセット
	void SetParamCount(int value);

	//ウサギの描画
	void RabbitDraw();

private:

	//イベントライン
	int eventLine_;

	//プレイヤー状態変化用カウント
	int paramCnt_;

	//火の玉出現用カウント
	int fireCnt_;

	//
	bool isChange_;

	//インスタンス
	RabbitText* rabbit_;

	//爆発(ポインタ)
	std::vector<Blast*> blasts_;

	//火の玉
	std::vector<FireBall*> fire_;
};

