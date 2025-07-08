#pragma once
#include <string>
#include "../Common/Vector2.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "SceneBase.h"

class LevelManager;
class GameStart;
class GameOver;
class GameClear;
class Pause;
class Fader;

class GameScene : public SceneBase
{
public:

	//BGM音量
	static constexpr int BGM_VOLUME = 70;

	//ゲーム終了時のゲームUIの表示時間
	static constexpr float FINISH_TO_WAIT_TIME = 2.0f;

	//BGM種類数
	static constexpr int RAND_BGMS = 4;

	//ゲーム状態
	enum class STATE
	{
		START,
		GAME,
		OVER,
		CLEAR,
		PAUSE
	};

	//コンストラクタ
	GameScene();

	//デストラクタ
	~GameScene() override;

	//初期化
	virtual void Init() override;

	//更新
	virtual void Update() override;

	//描画
	virtual void Draw() override;

	//解放
	virtual void Release() override;

	//リトライ処理
	void Retry();

	/// <summary>
	/// 選択処理の許可の設定
	/// </summary>
	/// <param name="value"></param>選択の許可
	void SetIsSelect(const bool value);

	/// <summary>
	/// ゲーム状態の変更
	/// </summary>
	/// <param name="state"></param>ゲーム状態
	void ChangeState(const STATE state);

	//新記録か調べる
	void CheckNewRecode();

	//BGM再生
	void PlayBGM();

	//BGM停止
	void StopBGM();

	//ステートを返す
	STATE GetState();

	//高さを返す
	int GetHeight();

protected:

	//選択処理の許可
	bool isSelect_;

	//選択処理の出現カウント
	float cnt_;

	//ステートのチェンジ中
	bool isStateChanging_;

	//ゲームステート
	STATE state_;

	//再生中のBGM 
	SoundManager::BGM bgm_;

	//フェーダー
	Fader* fader_;

	//レベル管理クラス
	LevelManager* level_;

	//ゲームスタート
	GameStart* start_;

	//ゲームオーバー
	GameOver* over_;

	//ゲームクリア
	GameClear* clear_;

	//シーン選択
	Pause* select_;	
	
	//リセット
	void Reset();

	//ステージレベルの読み込み
	void LevelLoad();
	
	//フェード処理
	void Fade();

	//BGMの種類をランダムで決定する
	SoundManager::BGM GetRandGameBgm();

};

