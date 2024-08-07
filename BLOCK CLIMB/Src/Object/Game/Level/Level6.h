#pragma once
#include "LevelManager.h"
#include "../../../Manager/SceneManager.h"

class Blast;
class FireBall;

class Level6 :public LevelManager
{
	static constexpr int ADD_LINE = 8;
	static constexpr int CREATE_INTERVAL = 1 * SceneManager::DEFAULT_FPS;

	void Init(GameScene* parent) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;
	void SetParam() override;

	void Reset() override;

	void ShiftGame() override;

	//月の当たり判定
	void HitMoon();

#pragma region ファイアーボール
	//火の玉の処理
	void FireBallUpdate();

	//ファイアーボール生成
	void CreateFireBall();

	//生成数を決める
	int GetCreateFireBallCnt();

	FireBall* GetValidFireBall();
#pragma endregion 

	//爆発処理
	void BlastUpdate();

private:

	//イベントライン
	int eventLine_;

	//プレイヤー状態変化用カウント
	int paramCnt_;

	//火の玉出現用カウント
	int fireCnt_;

	//火の玉出現条件値
	int fireCreateCnt_;

	//爆発中か確認
	bool isBlast_;

	//スピードダウンか確認
	bool isSpeedDown_;

	//爆発(ポインタ)
	std::vector<Blast*> blasts_;

	//火の玉
	std::vector<FireBall*> fire_;
};

