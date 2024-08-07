#pragma once
#include "../Game/PlayerBase.h"

class MenuScene;

class MenuPlayer : public PlayerBase
{
public:

	enum class MOVE_STATE
	{
		NONE,
		ADMISSION,
		EXIT
	};

	static constexpr float SPEED = 5.0f;

	MenuPlayer();
	~MenuPlayer();

	void Init(MenuScene* parent);
	void Reset() override;
	void Update() override;
	void Draw() override;

	//入場処理
	void Admission();

	//退場処理
	void Exit();

	//移動の許可の設定
	void SetState(MOVE_STATE state);

private:

	//ステート
	MOVE_STATE state_;

	//定位置
	Vector2F fiexdPos_;

	//インスタンス
	MenuScene* menu_;

};

