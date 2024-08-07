#include "../../../Application.h"
#include "../../../Manager/InputManager.h"
#include "../../../Utility/Collision.h"
#include "Level1.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../Block/Block1.h"
#include "../BackGround.h"
#include "../Camera/Camera.h"
#include "../Moon/Moon1.h"
#include "../Side/SideBase.h"
#include "../Side/Side1.h"

void Level1::AddInit()
{
	//ゴールの読み込み
	moon_ = new Moon1();
	moon_->Init(this);

	//ブロックの読み込み
	block_ = new Block1();
	block_->Init(this);

	//サイドの読み込み
	side_ = new Side1();
	side_->Init(this);
}

void Level1::Update(void)
{
	//ヒットストップ処理
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}

	LevelManager::Update();

	//ゴール処理
	moon_->Update();

	//ゴールとの衝突判定
	LevelManager::GoalHit();
}

void Level1::Draw(void)
{
	// 振動
	if (hitStopCnt_ > 0)
	{
		// 描画先のスクリーンを設定 ヒットストップ中は、
		SetDrawScreen(tmpScreen_);
		ClearDrawScreen();				//描画領域のクリア
	}

	backGround_->Draw();
	moon_->Draw();
	block_->Draw();
	player_->Draw();
	camera_->Draw();
	
	CameraShake();

	side_->Draw();
	DebagDraw();
}

void Level1::Release(void)
{
	side_->Release();
	block_->Release();
	moon_->Release();
	LevelManager::Release();
}

void Level1::SetParam()
{

#pragma region 各パラメーター初期化用変数
	//フィールドサイズ
	fieldSize_ = { 16 , 30 };
	
	//地面サイズ
	groundSize_ = { 16 ,3 };

	//ステージサイズ
	stageSize_ = { fieldSize_.x,
					fieldSize_.y + groundSize_.y };

	float fieldY = fieldSize_.y;

	//プレイヤーの初期座標
	firstPlayerPos_ = { Application::SCREEN_SIZE_X / 2,
						BlockBase::BLOCK_SIZE_Y * (fieldY - 2) - 8 };

	//カメラの初期座標
	firstCameraPos_ = { 0,
						-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + 2) };

	//ゴール座標
	goalPos_ = { Application::SCREEN_SIZE_X / 2 + 75,
				150 };

	//描画合わせ用変数
	game_Draw_Center_ = { Application::SCREEN_SIZE_X / 2 - fieldSize_.x * BlockBase::BLOCK_SIZE_X / 2 + BlockBase::BLOCK_SIZE_X / 2,
							0 };
#pragma endregion

}

