#pragma once
#include "../../Common/Vector2F.h"
#include "../Game/PlayerBase.h"

class TitleScene;

class TitlePlayer :public PlayerBase
{
public:
	enum class TITLE_PLAYER
	{
		MOVE,
		STOP
	};

	static constexpr int MOVES = 500;
	static constexpr float SPEED = 3.0f;

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
	TITLE_PLAYER titState_;

	//定位置
	Vector2F fixedPos_;

	bool isText_;

	TitleScene* title_;

};

