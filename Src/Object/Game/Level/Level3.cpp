#include "../../../Application.h"
#include "../../../Manager/InputManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Utility/Collision.h"
#include "Level3.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../Block/Block3.h"
#include "../BackGround.h"
#include "../Camera/Camera.h"
#include "../Side/SideBase.h"
#include "../Side/Side3.h"
#include "../Gimic/Blast.h"
#include "../Moon/Moon3.h"

Level3::Level3(void)
{
	isBlast_ = false;
	moon_ = nullptr;
}

Level3::~Level3(void)
{
}

void Level3::AddInit()
{
	//ブロックの読み込み
	block_ = new Block3();
	block_->Init(this);

	side_ = new Side3();
	side_->Init(this);

	moon_ = new Moon3();
	moon_->Init(this);
}

void Level3::Update(void)
{
	//ヒットストップ処理
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}

	//ゲームオーバーチェック
	GameOverCheck();

	//ゲームクリアチェック
	GameClearCheck();

	//ブロック処理(爆発中は行わない)
	if (!isBlast_) { block_->Update(); }

	//プレイヤー
	player_->Update();

	//背景スクロール
	backGround_->Update();

	//カメラ
	camera_->Update();

	//サイド画面(スコア関係)
	side_->Update();

	//月
	moon_->Update();

	//フィールドにブロックがない状態の時かつ
	//月のステートがFADE_BIGじゃないとき
	//月のステートはSTOPにしておく
	if (!block_->IsBlock() && moon_->GetDarkMove() != Moon::DARK_MOVE::FADE_BIG)
	{
		moon_->SetDarkMove(Moon::DARK_MOVE::STOP);
	}

	//月との衝突判定
	HitMoon();

	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		//爆発生成数
		blast->Update();

		//爆発してないとき
		if (blast->GetState() == Blast::STATE::NONE)
		{
			isBlast_ = false;
		}

		//爆発中の処理
		if (blast->GetState() == Blast::STATE::BLAST)
		{
			isBlast_ = true;
			//衝突判定
			if (!player_->IsDeath() &&
				Collision::IsCollisionCircle(player_->GetPos().ToVector2(),
					player_->GetSize().x / 2,
					blast->GetPos(),
					blast->GetRadius()))
			{
				SetStopCnt(HIT_STOP_CNT);
				player_->SetIsDeath(true);
			}
		}	
	}

	//クリア条件ラインを消したらクリア判定にする
	if (block_->GetLineCount() >= Block3::CREAL_LINE)
	{
		SetGameClear(true);
	}
}

void Level3::Draw(void)
{
	// 振動
	if (hitStopCnt_ > 0)
	{
		// 描画先のスクリーンを設定 ヒットストップ中は、
		SetDrawScreen(tmpScreen_);
	}

	backGround_->Draw();
	block_->Draw();
	LevelManager::Draw();
	moon_->Draw();
	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		blast->Draw();
	}
	player_->Draw();
	camera_->Draw();
	side_->Draw();

	CameraShake();

	DebagDraw();
}

void Level3::Release(void)
{
	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		blast->Release();
	}
	moon_->Release();
	delete moon_;
	
	side_->Release();
	delete side_;
	
	block_->Release();
	delete block_;
	
	LevelManager::Release();
	
}

void Level3::SetParam()
{
	// フィールドと地面のサイズを設定
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };
	groundSize_ = { FIELD_WIDTH, GROUND_HEIGHT };

	// ステージサイズを設定
	stageSize_ = {
		fieldSize_.x,
		fieldSize_.y + groundSize_.y
	};

	float fieldY = static_cast<float>(fieldSize_.y);  // フィールドの縦サイズを float に変換して計算

	// プレイヤーの初期座標を設定
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2,
		BlockBase::BLOCK_SIZE_Y * (fieldY - PLAYER_START_BLOCK_OFFSET_Y) - PLAYER_PIXEL_OFFSET_Y
	};

	// カメラの初期座標を設定
	firstCameraPos_ = {
		0,
		-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + CAMERA_BLOCK_OFFSET_Y)
	};

	// ゴール座標を設定
	goalPos_ = {
		Application::SCREEN_SIZE_X / 2 + GOAL_OFFSET_X,
		GOAL_POS_Y
	};

	// 描画位置を画面の中心に合わせて調整
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- fieldSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2,
		0
	};

	//爆発判定をfalseに
	isBlast_ = false;
}

void Level3::HitMoon()
{
	//プレイヤー情報の取得
	Vector2 pPos = player_->GetPos().ToVector2();
	Vector2 pSize = player_->GetSize();			//プレイヤーのx座標の半分を半径とする
	int pRadius = pSize.x / 2;

	//月の取得
	Vector2 mPos = moon_->GetPos(Moon::MOON_TYPE::DEAD).ToVector2();

	if (!isBlast_ &&
		Collision::IsCollisionCircle(pPos, pRadius, mPos, Moon::RADIUS) && 
		moon_->IsMoon(Moon::MOON_TYPE::DEAD) == false)
	{
		StopBGM();
		moon_->SetDarkMove(Moon::DARK_MOVE::FADE_BIG);
		SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::DARK_MOON_HIT));
		block_->AllDeleteLine();
	}
}