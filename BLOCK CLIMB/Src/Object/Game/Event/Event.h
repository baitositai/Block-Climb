#pragma once
#include "../../../Common/Vector2.h"

class LevelManager;

class Event
{
public:

	enum class EVENT
	{
		SPEED_UP,
		BLOCK_SPEED_UP,
		SPEED_DOWN,
		BLAST_LINE,
		FIRE_BALL,
		NONE,
	};

	enum class EFECT
	{
		SPEED_UP,
		SPEED_DOWN,
		NONE
	};

	//イベントの種類
	static constexpr int EVENT_TYPE = static_cast<int>(EVENT::NONE);

	//エフェクトのアニメーションスピード
	static constexpr float EFECT_ANIM_SPEED = 0.03f;

	//エフェクト種類
	static constexpr int EFECT_TYPE = static_cast<int>(EFECT::NONE);


	//各イベントの発生率
	static constexpr int BLAST_FREQUENCY = 3;
	static constexpr int FIRE_BALL_FREQUENCY = 3;
	static constexpr int SPEED_UP_FREQUENCY = 3;
	static constexpr int BLOCK_SPEED_UP_FREQUENCY = 3;
	static constexpr int SPEED_DOWN_FREQUENCY = 3;
	static constexpr int FREQUENCY = 15;


	void Init(LevelManager* parent);
	void Update();
	void Draw();
	void Release();

	void Reset();
	void Load();

	//アイコンの描画
	void IconDraw(Vector2 pos);

	//エフェクトの描画
	void EfectDraw();

	//イベントをランダム確率で発生
	void EventOccurs();

	//イベント状態の設定
	void SetEvent(EVENT value);

	//エフェクトの座標の設定
	void SetEfectPos(Vector2 pos);

	//イベント状態を返す
	EVENT GetEvent();

private:

	//アイコン画像
	int icon_[EVENT_TYPE];

	//エフェクト画像
	int efect_[EFECT_TYPE];

	//エフェクトサイズ
	float size_;

	//エフェクトアニメーションスピード
	float efectAnimSpeed_;

	//エフェクトの描画位置
	Vector2 efectPos_;

	//イベント状態
	EVENT eventState_;

	//エフェクト状態
	EFECT efeState_;

	//インスタンス
	LevelManager* level_;

};

