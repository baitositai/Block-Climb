#pragma once
#include "LevelManager.h"
#include "../../../Manager/SceneManager.h"

class Blast;
class FireBall;

class Level6 :public LevelManager
{
public:

	static constexpr int DEBUFF_LINE = 40;							//デバフラインの高さ

	static constexpr int FIELD_WIDTH = 16;                          // フィールドの横のブロック数
	static constexpr int FIELD_HEIGHT = 20;                         // フィールドの縦のブロック数

	static constexpr int GROUND_HEIGHT = 3;                         // 地面の縦のブロック数

	static constexpr int PLAYER_OFFSET_BLOCK_Y = 2;                 // プレイヤーの初期位置の縦のブロック数オフセット
	static constexpr int PLAYER_PIXEL_ADJUST_Y = 8;                 // プレイヤーの縦方向の微調整に使うピクセル数

	static constexpr int CAMERA_OFFSET_BLOCK_Y = 2;                 // カメラの縦のブロック数オフセット

	static constexpr int GOAL_OFFSET_X = 75;                        // ゴールの横方向の調整値
	static constexpr int GOAL_POS_Y = 600;                          // ゴールの縦方向の位置

	static constexpr int ADD_LINE = 8;								//追加ライン

	static constexpr int DEFAULT_CREATE_FIRE_CNT = 10 * SceneManager::DEFAULT_FPS;//生成のインターバル
	static constexpr int CREATE_INTERVAL = 1 * SceneManager::DEFAULT_FPS;//生成のインターバル
	static constexpr int CREATE_RAND_RANGE = 5 * SceneManager::DEFAULT_FPS;//生成のインターバル

	static constexpr int EVENT_CHANGE = 6;							//イベントの状態変化カウント
	static constexpr int FIRE_CHANGE = 7;							//火の玉の状態変化カウント

	static constexpr int HEIGHT_THRESHOLDS[EVENT_CHANGE] = { 70, 60, 50, 30, 20, 10 };  // 高さの閾値

	static constexpr int CNT_VALUES[FIRE_CHANGE] = { 20, 15, 10, 8, 5, 4, 3 };     // 高さに対応するカウント値

	static constexpr float FIRE_BALL_SPEED = 2.0f;							//当たり判定のストップカウント

	//コンストラクタ
	Level6(void);

	//デストラクタ
	~Level6(void);

	//初期化
	void Init(GameScene* parent) override;

	//更新
	void Update(void) override;

	//描画
	void Draw(void) override;

	//解放
	void Release(void) override;

	//パラメーター設定
	void SetParam() override;

	//リセット
	void Reset() override;

	//オブジェクト等の位置をずらす
	void ShiftGame() override;

	//月の当たり判定
	void HitMoon();

	//火の玉の処理
	void FireBallUpdate();

	//ファイアーボール生成
	void CreateFireBall();

	//高さごとに火の玉の生成数を決める
	int GetCreateFireBallCnt();

	//火の玉を返す
	FireBall* GetValidFireBall();

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

