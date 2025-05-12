#pragma once
#include "LevelManager.h"

class Blast;
class FireBall;
class RabbitMarason;

class Marason :public LevelManager
{
public:

	static constexpr int ADD_LINE = 8;								//追加ライン

	static constexpr int FIELD_WIDTH = 16;                          // フィールドの横のブロック数
	static constexpr int FIELD_HEIGHT = 20;                         // フィールドの縦のブロック数
	static constexpr int GROUND_HEIGHT = 3;                         // 地面の縦のブロック数

	static constexpr int BUFF_SECOND = 15;							//バフの秒数
	static constexpr int FIRE_SECOND = 15;							//火の玉の落下秒数

	static constexpr int PLAYER_OFFSET_BLOCK_Y = 2;                 // プレイヤーの位置のブロック数オフセット
	static constexpr int PLAYER_PIXEL_ADJUST_Y = 8;                 // プレイヤーの縦の微調整ピクセル数

	static constexpr int CAMERA_OFFSET_BLOCK_Y = 2;                 // カメラの位置のブロック数オフセット

	static constexpr int GOAL_OFFSET_X = 75;                        // ゴールの横位置の調整値
	static constexpr int GOAL_POS_Y = 600;                          // ゴールの縦位置

	static constexpr int RABBIT_DRAW_OFFSET_X = 30;                  // うさぎ画像の横位置の調整値
	static constexpr int SPEECH_DRAW_OFFSET_X = 40;                  // 吹き出し画像の基準位置の横調整値
	static constexpr int SPEECH_DRAW_OFFSET_Y = 5;                   // 吹き出し画像の縦位置の微調整値
	static constexpr int TEXT_DRAW_OFFSET_X = 70;                    // テキスト画像の基準位置の横調整値
	static constexpr int TEXT_DRAW_OFFSET_Y = 80;                    // テキスト画像の縦位置の追加調整値

	//生成数の変更回数
	static constexpr int CREATE_RULE_SIZE = 6;

	// 条件しきい値（降順）
	static constexpr int CREATE_HEIGHT_THRESHOLDS[CREATE_RULE_SIZE] = {
		100, 80, 60, 40, 20, 0
	};

	// 対応する生成数（CREATE_HEIGHT_THRESHOLDS と同じ並び）
	static constexpr int CREATE_COUNTS[CREATE_RULE_SIZE] = {
		15, 10, 7, 5, 4, 3
	};

	// 一定時間（秒 × FPS）
	static constexpr int FIRE_INTERVAL_SECOND = 5;

	//コンストラクタ
	Marason(void);

	//デストラクタ
	~Marason(void);

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

	//オブジェクトの位置調整
	void ShiftGame() override;

	//イベント発生の処理
	void GameEvent();

	//火の玉の処理
	void FireBallUpdate();

	//ファイアーボール生成
	void CreateFireBall();

	//火の玉の出現カウントの設定
	void SetTimeCount(int value);

	//火の玉を返す
	FireBall* GetValidFireBall();

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

	//変更判定
	bool isChange_;

	//インスタンス
	RabbitMarason* rabbit_;

	//爆発(ポインタ)
	std::vector<Blast*> blasts_;

	//火の玉
	std::vector<FireBall*> fire_;
};

