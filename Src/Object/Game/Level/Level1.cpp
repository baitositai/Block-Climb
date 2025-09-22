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

Level1::Level1(void)
{
}

Level1::~Level1(void)
{
}

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
	delete side_;
	block_->Release();
	delete block_;
	moon_->Release();
	delete moon_;
	LevelManager::Release();
}

void Level1::SetParam()
{
	//各種サイズ設定
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };                             //フィールドサイズ
	groundSize_ = { FIELD_WIDTH, GROUND_HEIGHT };                           //地面サイズ
	stageSize_ = { fieldSize_.x, fieldSize_.y + groundSize_.y };            //ステージ全体のサイズ

	float fieldY = static_cast<float>(fieldSize_.y);                        //計算用にfloatへ変換

	//プレイヤーの初期座標
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2,                                     //画面中央
		BlockBase::BLOCK_SIZE_Y * (fieldY - PLAYER_START_OFFSET_Y) - PLAYER_PIXEL_OFFSET_Y //Y座標下から2ブロック目、微調整
	};

	//カメラの初期座標
	firstCameraPos_ = {
		0,                                                                  //原点
		-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + CAMERA_OFFSET_Y_BLOCKS) //画面下から上にずらす
	};

	//ゴール座標
	goalPos_ = {
		Application::SCREEN_SIZE_X / 2 + GOAL_OFFSET_X,                     //画面中央から右にずらす
		GOAL_POS_Y                                                          //固定値
	};

	//描画中心（画面合わせ用）
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- fieldSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2 * DRAW_CENTER_BLOCK_OFFSET_X,     
		0
	};

}

