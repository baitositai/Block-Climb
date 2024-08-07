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

	static constexpr int HIT_STOP_CNT = 60;

	LevelManager(void);
	~LevelManager(void);

	virtual void Init(GameScene* parent);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

#pragma region 各レベルごとで追加や変更する用
	//追加の読み込み
	virtual void AddInit();

	//ステージレベルの初期設定
	virtual void SetParam();

	//リセット機能
	virtual void Reset();
#pragma endregion 

#pragma region 衝突判定関連
	//クリア判定
	virtual void GoalHit();

	void GameClearCheck();

	//ゲームオーバー判定
	void GameOverCheck();

	//テトリス関係の当たり判定
	bool IsHitBlocks(Vector2 Pos, Vector2 Size);

	//フィールドとの当たり判定
	bool IsHitField(Vector2 Ppos);

	//動かしてるミノとの当たり判定
	bool IsHitMino(Vector2 Ppos, Vector2 Psize);

	//プレイヤーが衝突判定を起こしてるかの確認
	bool IsPlayerCheck(AsoUtility::DIR value, Vector2 Mino, int MinoType);

	//プレイヤーがカメラ範囲か確認
	void IsCameraRange();
#pragma endregion
	
#pragma region その他処理
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

#pragma endregion 

#pragma region 値を返す
	int GetFieldBlockY(int y);
	int GetBlockHeight();
	int GetBlockCnt();
	int GetCntLine();
	float GetFallSpeed();
	Vector2F GetCameraPos();
	Vector2F GetPlayerPos();
	Vector2F GetMinoBlockPos(Vector2F pPos);
	virtual Moon* GetMoonInstans();
	Event::EVENT GetEventState();

	Vector2 GetFieldSize();
	Vector2 GetGroundSize();
	Vector2 GetStageSize();
	Vector2F GetFirstPlayerPos();
	Vector2F GetFirstCameraPos();
	Vector2 GetGoalPos();
	Vector2 GetGameCenter();
#pragma endregion

protected:

#pragma region ゲーム処理の判定
	//ゲームクリア判定
	bool isGameClear_;

	//ゲームオーバー判定
	bool isGameOver_;
#pragma endregion

#pragma region ヒットストップ関連
	//ヒットストップカウント
	int hitStopCnt_;
#pragma endregion

#pragma region 他cppへ情報を送る用
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
#pragma endregion

#pragma region インスタンスの生成
	GameScene* gameScene_;
	BlockBase* block_;
	PlayerBase* player_;
	BackGround* backGround_;
	Camera* camera_;
	Moon* moon_;
	SideBase* side_;
	Event* event_;
#pragma endregion

	//一時的なスクリーン
	int tmpScreen_;

private:	
};

