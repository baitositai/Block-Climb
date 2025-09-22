#include "../../../Application.h"
#include "../../../Manager/InputManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Utility/Collision.h"
#include "Level4.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../Block/Block4.h"
#include "../BackGround.h"
#include "../Camera/Camera.h"
#include "../Moon/Moon1.h"
#include "../Side/SideBase.h"
#include "../Side/Side4.h"
#include "../Gimic/FireBall.h"

Level4::Level4(void)
{
}

Level4::~Level4()
{
}

void Level4::AddInit()
{
	//ゴールの読み込み
	moon_ = new Moon1();
	moon_->Init(this);

	//ブロックの読み込み
	block_ = new Block4();
	block_->Init(this);

	//サイドの読み込み
	side_ = new Side4();
	side_->Init(this);
}

void Level4::Update(void)
{
	//ヒットストップ処理
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}

	LevelManager::Update();

	//火の玉の処理
	FireBallCollision();

	//ゴール処理
	moon_->Update();

	//ゴールとの衝突判定
	LevelManager::GoalHit();
}

void Level4::Draw(void)
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

	//火の玉の描画
	auto fires = block_->GetFireBall();
	for (auto fire : fires)
	{
		fire->Draw();
	}

	camera_->Draw();
	side_->Draw();
	CameraShake();

	DebagDraw();
}

void Level4::Release(void)
{	
	auto fires = block_->GetFireBall();
	for (auto fire : fires)
	{
		fire->Release();
	}
	moon_->Release();
	delete moon_;
	
	block_->Release();
	delete block_;
	
	side_->Release();
	delete side_;
	LevelManager::Release();
}

void Level4::SetParam()
{
	// フィールドサイズを設定
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };

	// 地面サイズを設定
	groundSize_ = { FIELD_WIDTH, GROUND_HEIGHT };

	// ステージサイズを設定
	stageSize_ = {
		fieldSize_.x,
		fieldSize_.y + groundSize_.y
	};

	float fieldY = static_cast<float>(fieldSize_.y);  // フィールドの縦サイズを float に変換

	// プレイヤーの初期座標を設定
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2,
		BlockBase::BLOCK_SIZE_Y * (fieldY - PLAYER_OFFSET_BLOCK_Y) - PLAYER_PIXEL_ADJUST_Y
	};

	// カメラの初期座標を設定
	firstCameraPos_ = {
		0,
		-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + CAMERA_OFFSET_BLOCK_Y)
	};

	// ゴールの座標を設定
	goalPos_ = {
		Application::SCREEN_SIZE_X / 2 + GOAL_OFFSET_X,
		GOAL_POS_Y
	};

	// 描画中心の座標を設定
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- fieldSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2,
		0
	};

}

void Level4::FireBallCollision()
{
	auto& snd = SoundManager::GetInstance();

	//火の玉の処理
	auto fires = block_->GetFireBall();
	for (auto fire : fires)
	{
		//爆発生成数
		fire->Update();

		Vector2 fPos = fire->GetPos().ToVector2();
		Vector2 fSize = { FireBall::SIZE_X,
						  FireBall::SIZE_Y };

		int pRadius = player_->GetSize().y / 2;

		//プレイヤーとの衝突判定
		if (fire->GetState() == FireBall::STATE::FIRE &&
			Collision::IsCollisionCircle(player_->GetPos().ToVector2(),
				pRadius,
				fire->GetPos().ToVector2(),
				FireBall::RADIUS))
		{
			fire->SetState(FireBall::STATE::BLAST);
			SetStopCnt(HIT_STOP_CNT);
			player_->SetIsDeath(true);
		}

		//ブロックとの衝突判定
		if (fire->GetState() == FireBall::STATE::FIRE &&
			IsHitField(fPos))
		{
			fire->SetState(FireBall::STATE::BLAST);
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::FIRE_BALL_HIT));
		}
		else if (fire->GetState() == FireBall::STATE::FIRE &&
			IsHitMino(fPos, fSize))
		{
			fire->SetState(FireBall::STATE::BLAST);
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::FIRE_BALL_HIT));
		}
	}
}

