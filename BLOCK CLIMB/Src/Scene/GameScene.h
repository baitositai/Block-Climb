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
class SceneSelect;
class Fader;

class GameScene : public SceneBase
{
public:

	enum class STATE
	{
		START,
		GAME,
		OVER,
		CLEAR,
		PAUSE
	};

	GameScene(void);
	~GameScene(void) override;

	virtual void Init(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	virtual void Release(void) override;

	//リセット
	void Reset();

	//ステージレベルの読み込み
	void LevelLoad();

	//リトライ処理
	void Retry();

	//選択処理の許可の設定
	void SetIsSelect(bool value);

	//ゲーム状態の変更
	void SetState(STATE state);

	//シーンチェンジ
	void ChangeScene(SceneManager::SCENE_ID scene);

	//新記録か調べる
	void CheckNewRecode();

	//フェード処理
	void Fade();

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
	int cnt_;

	//ステートのチェンジ中
	bool isStateChanging_;

	//ゲームステート
	STATE state_;

	//再生中のBGM 
	SoundManager::BGM bgm_;

	//インスタンス
	Fader* fader_;
	LevelManager* level_;
	GameStart* start_;
	GameOver* over_;
	GameClear* clear_;
	SceneSelect* select_;

};

