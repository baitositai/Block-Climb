#pragma once
#include "../../Application.h"
#include "../Game/PlayerBase.h"

class MenuScene;

class MenuPlayer : public PlayerBase
{
public:

	//行動状態
	enum class MOVE_STATE
	{
		NONE,
		ADMISSION,
		EXIT
	};

	//速度
	static constexpr float SPEED = 5.0f;

	//アニメーション速度
	static constexpr float ANIM_SPEED = 0.2f;

	//プレイヤー拡大率
	static constexpr float PLAYER_RATE = 3.5f;

	//固定位置
	static constexpr int FIXED_POS_X = Application::SCREEN_SIZE_X - 300;
	static constexpr int FIXED_POS_Y = Application::SCREEN_SIZE_Y - (200 + SIZE_Y);

	//退出終了
	static constexpr int EXIT_FINISH = Application::SCREEN_SIZE_X + SIZE_X + 20;

	//コンストラクタ
	MenuPlayer();

	//デストラクタ
	~MenuPlayer();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="parent"></param>親インスタンス
	void Init(MenuScene* parent);

	//変数の初期化
	void Reset() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	/// <summary>
	/// 状態変更
	/// </summary>
	/// <param name="state"></param>次の状態
	void ChangeState(const MOVE_STATE state);

private:

	//ステート
	MOVE_STATE state_;

	//定位置
	Vector2F fiexdPos_;

	//インスタンス
	MenuScene* menu_;	
	
	//入場処理
	void Admission();

	//退場処理
	void Exit();

};