#pragma once
#include <string>
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"
#include "../../../Utility/AsoUtility.h"
#include "../Event/Event.h"

class GameScene;
class BlockBase;
class PlayerBase;
class BackGround;
class Camera;
class Moon;
class SideBase;
class Moon;
class Event;

class LevelManager
{
public:

	//ヒットストップ用のカウント
	static constexpr int HIT_STOP_CNT = 60;

	//次回ブロック拡大率
	static constexpr float NEXT_BLOCK_RATE = 0.7f;

	// 定数でマジックナンバーを置き換え
	static constexpr int HITSTOP_SHAKE_INTERVAL = 5;   // 揺れの切り替え間隔（フレーム）
	static constexpr int SHAKE_SCALE = 2;              // シェイクの強度（最終位置の倍率）
	static constexpr int SHAKE_OFFSET = 1;             // 中心からのオフセット調整
	static constexpr int SHAKE_DISTANCE = 5;           // 実際に画面を動かす距離

	static constexpr int EFFECT_LOCAL_POS_X = 30;					//エフェクトの相対位置X
	static constexpr int EFFECT_LOCAL_POS_Y = 30;					//エフェクトの相対位置Y

	static constexpr float BUFF_PERCENT = 1.5f;						//バフの割合
	static constexpr float DEBUFF_PERCENT = 0.75f;					//デバフの割合
	static constexpr int BLOCK_FALL_SPEED_UP = 3;					//ブロックの落下速度

	LevelManager(void);
	~LevelManager(void);

	virtual void Init(GameScene* parent);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	//追加の読み込み
	virtual void AddInit();

	//ステージレベルの初期設定
	virtual void SetParam();

	//リセット機能
	virtual void Reset();

	//ゴールとの衝突判定
	virtual void GoalHit();

	//クリア判定
	void GameClearCheck();

	//ゲームオーバー判定
	void GameOverCheck();

	//ブロック関係の当たり判定
	bool IsHitBlocks(Vector2 Pos, Vector2 Size);

	//フィールドとの当たり判定
	bool IsHitField(Vector2 Ppos);

	//動かしてるミノとの当たり判定
	bool IsHitMino(Vector2 Ppos, Vector2 Psize);

	//プレイヤーが衝突判定を起こしてるかの確認
	bool IsPlayerCheck(AsoUtility::DIR value, Vector2 Mino, int MinoType);

	//プレイヤーがカメラ範囲か確認
	void IsCameraRange();

	//プレイヤーをずらす処理
	void PlayerShift(AsoUtility::DIR value);

	//フィールド用に座標の変換
	Vector2 Field2Pos(Vector2 worldPos);

	//ワールド用に座標の返還
	Vector2 World2Pos(Vector2 fieldPos);

	//デバッグに関する描画
	void DebagDraw();

	//ゲームクリアへ変える
	void SetGameClear(bool value);

	//ゲームオーバーへ変える
	void SetGameOver(bool value);

	//ヒットストップのカウントを設定
	void SetStopCnt(int cnt);

	//カメラシェイク
	void CameraShake();

	//次のブロックの描画
	void NextBlockDraw(Vector2 pos);

	//座標をずらす処理
	virtual void ShiftGame();

	//イベントアイコン描画
	void IconDraw(Vector2 pos);

	//bgmの再生
	void PlayBGM();

	//bgmの停止
	void StopBGM();

	/// <summary>
	/// ブロックの縦に置かれてる数を返す
	/// </summary>
	/// <param name="y"></param>ブロック縦の数最新の値
	/// <returns></returns>
	int GetFieldBlockY(int y);

	/// <summary>
	/// 現在の高さを返す
	/// </summary>
	/// <returns></returns>積み上げた高さ
	int GetBlockHeight();

	/// <summary>
	/// 課題用ブロックの置く数を返す
	/// </summary>
	/// <returns></returns>課題用ブロックの置く数
	int GetBlockCnt();

	/// <summary>
	/// 消したラインの数
	/// </summary>
	/// <returns></returns>消したラインの数
	int GetCntLine();

	/// <summary>
	/// 落下速度を返す
	/// </summary>
	/// <returns></returns>落下速度
	float GetFallSpeed();

	/// <summary>
	/// カメラ座標を返す
	/// </summary>
	/// <returns></returns>カメラ座標
	Vector2F GetCameraPos();

	/// <summary>
	/// プレイヤー座標を返す
	/// </summary>
	/// <returns></returns>プレイヤー座標
	Vector2F GetPlayerPos();

	/// <summary>
	/// プレイヤーとミノの位置からミノの座標を返す
	/// </summary>
	/// <param name="pPos"></param>プレイヤー座標
	/// <returns></returns>ミノの座標
	Vector2F GetMinoBlockPos(Vector2F pPos);

	/// <summary>
	/// 月のクラスを返す
	/// </summary>
	/// <returns></returns>月
	virtual Moon* GetMoonInstans();

	/// <summary>
	/// イベント状態を返す
	/// </summary>
	/// <returns></returns>イベントの状態
	Event::EVENT GetEventState();

	/// <summary>
	/// フィールドサイズを返す
	/// </summary>
	/// <returns></returns>フィールドサイズ
	Vector2 GetFieldSize();

	/// <summary>
	/// 地面のサイズを返す
	/// </summary>
	/// <returns></returns>地面サイズ
	Vector2 GetGroundSize();

	/// <summary>
	/// ステージ全体のサイズ返す
	/// </summary>
	/// <returns></returns>ステージ全体のサイズ
	Vector2 GetStageSize();

	/// <summary>
	/// プレイヤーの初期位置を返す
	/// </summary>
	/// <returns></returns>プレイヤーの初期位置
	Vector2F GetFirstPlayerPos();

	/// <summary>
	/// カメラの初期位置を返す
	/// </summary>
	/// <returns></returns>カメラの初期位置
	Vector2F GetFirstCameraPos();

	/// <summary>
	/// ゴールの位置を返す
	/// </summary>
	/// <returns></returns>ゴールの位置を返す
	Vector2 GetGoalPos();

	/// <summary>
	/// 中心位置に合わせる用の値を返す
	/// </summary>
	/// <returns></returns>中心位置に合わせる用の値
	Vector2 GetGameCenter();

protected:

	//ゲームクリア判定
	bool isGameClear_;

	//ゲームオーバー判定
	bool isGameOver_;

	//ヒットストップカウント
	int hitStopCnt_;

	//フィールドサイズ
	Vector2 fieldSize_;

	//地面サイズ
	Vector2 groundSize_;

	//ステージサイズ
	Vector2 stageSize_;

	//プレイヤーの初期座標
	Vector2F firstPlayerPos_;

	//カメラの初期座標
	Vector2F firstCameraPos_;

	//ゴール座標
	Vector2 goalPos_;
	
	//ゲームを画面中心で描画できるようにする用の座標
	Vector2 game_Draw_Center_;

	//ゲームシーン
	GameScene* gameScene_;

	//ブロック
	BlockBase* block_;

	//プレイヤー
	PlayerBase* player_;

	//背景
	BackGround* backGround_;

	//カメラ
	Camera* camera_;

	//月
	Moon* moon_;

	//サイド画面
	SideBase* side_;

	//イベント
	Event* event_;

	//一時的なスクリーン
	int tmpScreen_;
	
};

