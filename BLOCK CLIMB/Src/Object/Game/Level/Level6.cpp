#include "../../../Application.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Utility/Collision.h"
#include "Level6.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../Block/Block6.h"
#include "../BackGround.h"
#include "../Camera/MarasonCamera.h"
#include "../Moon/Moon6.h"
#include "../Gimic/Blast.h"
#include "../Gimic/FireBall.h"
#include "../Side/SideBase.h"
#include "../Side/Side6.h"

void Level6::Init(GameScene* parent)
{
	SetParam();

	gameScene_ = parent;

	camera_ = new MarasonCamera();
	camera_->Init(this);

	player_ = new PlayerBase();
	player_->Init(this);

	backGround_ = new BackGround();
	backGround_->Init(this);	

	//ブロックの読み込み
	block_ = new Block6();
	block_->Init(this);

	//サイドの読み込み
	side_ = new Side6();
	side_->Init(this);

	//ゴールの読み込み
	moon_ = new Moon6();
	moon_->Init(this);

	event_ = new Event();
	event_->Init(this);

	// 一時的な描画領域
	tmpScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	//初期化処理
	Reset();

	//火の玉の初期化
	for (auto fire : fire_)
	{
		fire->SetState(FireBall::STATE::NONE);
	}
}

void Level6::Update(void)
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
	
	//プレイヤーの更新処理
	player_->Update();

	//背景処理
	backGround_->Update();

	//カメラ処理
	camera_->Update();

	//サイド画面処理
	side_->Update();

	//月の処理
	moon_->Update();
	HitMoon();

	//爆発処理
	BlastUpdate();

	//火の玉処理
	FireBallUpdate();

	//プレイヤーへのデバフ
	if (GetBlockHeight() >= 40 && !isSpeedDown_) {
		player_->SetParam(PlayerBase::MAX_MOVE_SPEED * 0.75f, PlayerBase::MAX_JUMP_POW * 0.75f);
		SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::SPEEDDOWN));
		event_->SetEvent(Event::EVENT::SPEED_DOWN);
		Vector2 efectPos = AsoUtility::V2Sub(player_->GetPos().ToVector2(), Vector2{ 30,30 });
		event_->SetEfectPos(efectPos);

		isSpeedDown_ = true;
	}
}

void Level6::Draw(void)
{
	// 振動
	if (hitStopCnt_ > 0)
	{
		// 描画先のスクリーンを設定 ヒットストップ中は、
		SetDrawScreen(tmpScreen_);
		ClearDrawScreen();				//描画領域のクリア
	}

	//背景描画
	backGround_->Draw();

	//ブロック描画
	block_->Draw();

	//月の描画
	moon_->Draw();

	//プレイヤー描画
	player_->Draw();

	event_->EfectDraw();

	//カメラの描画
	camera_->Draw();

	for (auto fire : fire_)
	{
		fire->Draw();
	}
	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		blast->Draw();
	}

	CameraShake();

	side_->Draw();
	DebagDraw();
}

void Level6::Release(void)
{	
	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		blast->Release();
	}
	for (auto fire : fire_)
	{
		fire->Release();
	}
	event_->Release();
	side_->Release();
	block_->Release();
	moon_->Release();
	backGround_->Release();
	player_->Release();
	camera_->Release();
}

void Level6::SetParam()
{
#pragma region 各パラメーター初期化用変数
	//フィールドサイズ
	fieldSize_ = { 16 , 20 };

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
				600 };

	//描画合わせ用変数
	game_Draw_Center_ = { Application::SCREEN_SIZE_X / 2 - fieldSize_.x * BlockBase::BLOCK_SIZE_X / 2 + BlockBase::BLOCK_SIZE_X / 2,
							0 };
#pragma endregion
}

void Level6::Reset()
{
	LevelManager::Reset();
	fireCnt_ = 0;
	fireCreateCnt_ = 10 * SceneManager::DEFAULT_FPS;
	isSpeedDown_ = false;	
	eventLine_ = ADD_LINE;
	isBlast_ = false;
}

void Level6::ShiftGame()
{
	LevelManager::ShiftGame();

	//シフト用座標
	Vector2F pos = { 0,BlockBase::BLOCK_SIZE_Y };

	//炎ずらし
	for (auto fire : fire_)
	{
		fire->SetPos(pos);
	}

	//月座標ずらし
	moon_->SetPos(Moon::MOON_TYPE::DEAD, pos);
	moon_->SetPos(Moon::MOON_TYPE::GOAL, pos);
	moon_->SetFirstPos(Moon::MOON_TYPE::GOAL, pos);

}

void Level6::HitMoon()
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
		block_->LineDelete();
	}

	//プレイヤー情報の取得

	//ゴール情報の取得
	mPos = moon_->GetPos(Moon::MOON_TYPE::GOAL).ToVector2();
	if (Collision::IsCollisionCircle(pPos, pRadius, mPos, Moon::RADIUS))
	{
		StopBGM();
		SetStopCnt(HIT_STOP_CNT);
		isGameClear_ = true;
	}
}

void Level6::FireBallUpdate()
{
	CreateFireBall();

	//火の玉の処理
	for (auto fire : fire_)
	{
		//爆発生成数
		fire->Update();

		//プレイヤーとの衝突判定
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

void Level6::BlastUpdate()
{
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
}

void Level6::CreateFireBall()
{
	//時間減らす
	fireCnt_++;
	int cnt = GetCreateFireBallCnt();
	if (fireCnt_ >= fireCreateCnt_)
	{
		for (int i = 0; i < cnt; i++)
		{
			FireBall* fire = GetValidFireBall();

			//爆発の生成
			fire->Create(this, 2);
		}
		fireCnt_ = 0;
		fireCreateCnt_ = CREATE_INTERVAL + rand() % 5 * SceneManager::DEFAULT_FPS;
	}
}

//高さごとに火の玉の生成数を決める
int Level6::GetCreateFireBallCnt()
{
	int cnt = 3;
	int height = GetBlockHeight();
	if (height >= 70) { cnt = 20; }
	else if (height >= 60) { cnt = 15; }
	else if (height >= 50) { cnt = 10; }
	else if (height >= 30) { cnt = 8; }
	else if (height >= 20) { cnt = 5; }
	else if (height >= 10) { cnt = 4; }
	else { cnt = 3; }

	return cnt;
}

FireBall* Level6::GetValidFireBall()
{
	FireBall* fire = new FireBall();
	fire_.push_back(fire);
	return fire;
}
