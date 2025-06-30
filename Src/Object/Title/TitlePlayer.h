#pragma once
#include "../../Common/Vector2F.h"
#include "../Game/PlayerBase.h"

class TitleScene;

class TitlePlayer :public PlayerBase
{
public:

	//タイトルプレイヤーの運動状態
	enum class MOVE_STATE
	{
		NONE,
		MOVE,
		STOP
	};

	//移動
	static constexpr int MOVES = 500;

	//移動スピード
	static constexpr float SPEED = 3.0f;

	//アニメーションスピード
	static constexpr float ANIM_SPEED = 0.2f;

	//キャラクター拡大値
	static constexpr float CHARA_RATE = 1.8f;

	//固定位置
	static constexpr int POS_X = Application::SCREEN_SIZE_X / 5;
	static constexpr int POS_Y = Application::SCREEN_SIZE_Y - 145 - (SIZE_Y * 1.8 / 2);

	TitlePlayer();
	~TitlePlayer();

	void Init(TitleScene* parent, PLAYER_TYPE type);
	void Reset() override;
	void Update() override;
	void Draw() override;
	void Release();

	bool IsText();

private:
	//キャラクターの種類
	PLAYER_TYPE type_;

	//タイトル用キャラクターステート
	MOVE_STATE titState_;

	//定位置
	Vector2F fixedPos_;

	bool isText_;

	TitleScene* title_;

};

