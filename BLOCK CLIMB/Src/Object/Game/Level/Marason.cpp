#include "../../../Application.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Utility/Collision.h"
#include "Marason.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../Block/BlockMarason.h"
#include "../BackGround.h"
#include "../Camera/MarasonCamera.h"
#include "../Moon/Moon.h"
#include "../Gimic/Blast.h"
#include "../Gimic/FireBall.h"
#include "../Event/Event.h"
#include "../Side/SideBase.h"
#include "../Side/SideMarason.h"
#include "../RabbitText/RabbitMarason.h"

void Marason::Init(GameScene* parent)
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
	block_ = new BlockMarason();
	block_->Init(this);

	//サイドの読み込み
	side_ = new SideMarason();
	side_->Init(this);

	//イベントの処理
	event_ = new Event();
	event_->Init(this);

	rabbit_ = new RabbitMarason();
	rabbit_->GameInit(this);

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

void Marason::Update(void)
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

	//イベントステートが爆発の時は実行しない
	if (event_->GetEvent() != Event::EVENT::BLAST_LINE)
	{
		block_->Update();
	}
	
	//プレイヤーの更新処理
	player_->Update();

	//背景処理
	backGround_->Update();

	//カメラ処理
	camera_->Update();

	//サイド画面処理
	side_->Update();

	//イベント処理
	event_->Update();

	//爆発処理
	BlastUpdate();

	//火の玉処理
	FireBallUpdate();

	//ゲームイベント処理
	GameEvent();

	rabbit_->Update();
}

void Marason::Draw(void)
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

	//プレイヤー描画
	player_->Draw();

	//エフェクトの描画
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

	RabbitDraw();
}

void Marason::Release(void)
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
	
	rabbit_->Release();	
	event_->Release();
	side_->Release();
	block_->Release();
	backGround_->Release();
	player_->Release();
	camera_->Release();
}

void Marason::SetParam()
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

	eventLine_ = ADD_LINE;

}

void Marason::ShiftGame()
{
	LevelManager::ShiftGame();

	//シフト用座標
	Vector2F pos = { 0,BlockBase::BLOCK_SIZE_Y };

	//炎ずらし
	for (auto fire : fire_)
	{
		fire->SetPos(pos);
	}
}

void Marason::FireBallUpdate()
{
	//火の玉の処理
	for (auto fire : fire_)
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

void Marason::BlastUpdate()
{
	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		//ステートの取得
		Blast::STATE state = blast->GetState();

		//爆発の有り無
		if (state == Blast::STATE::NONE)
		{
			isChange_ = true;
		}
		else
		{
			isChange_ = false;
		}

		//爆発生成数
		blast->Update();

		//衝突判定
		if (state == Blast::STATE::BLAST &&
			!player_->IsDeath() &&
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

bool Marason::PlayerSpeedCount()
{
	paramCnt_--;

	if (paramCnt_ <= 0)
	{
		return true;
	}

	return false;
}

void Marason::SetParamCount(int value)
{
	paramCnt_ = value * SceneManager::DEFAULT_FPS;
}

void Marason::RabbitDraw()
{
	Vector2 pos = { 30, Application::SCREEN_SIZE_Y - RabbitText::RABBIT_SIZE_Y };
	rabbit_->RabbitDraw(pos);

	pos = { 40 + RabbitText::RABBIT_SIZE_X, Application::SCREEN_SIZE_Y - RabbitText::SPEECH_SIZE_Y + 5 };
	rabbit_->SpeechDraw(pos);

	pos = { 70 + RabbitText::RABBIT_SIZE_X , Application::SCREEN_SIZE_Y - RabbitText::RABBIT_SIZE_Y + 80 };
	rabbit_->TextDraw(pos);
}

void Marason::GameEvent()
{
	auto& snd = SoundManager::GetInstance();
	Event::EVENT checkState = event_->GetEvent();
	Vector2 efectPos;

	if (checkState == Event::EVENT::NONE &&
		block_->GetNowHeight() >= eventLine_)
	{
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::HAPPENING));

		//条件値の追加
		eventLine_ += ADD_LINE;

		//イベントランダム決定
		event_->EventOccurs();

		//決定後のイベントを取得
		Event::EVENT newState = event_->GetEvent();

		switch (newState)
		{
		case Event::EVENT::BLAST_LINE:
			block_->LineDelete();
			rabbit_->SetTextData(16);
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::TEXT));
			break;

		case Event::EVENT::FIRE_BALL:
			rabbit_->SetTextData(15);
			(15, true);
			SetTimeCount(15);
			break;

		case Event::EVENT::SPEED_DOWN:
			player_->SetParam(PlayerBase::MAX_MOVE_SPEED * 0.75f, PlayerBase::MAX_JUMP_POW * 0.75f);
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::SPEEDDOWN));
			SetParamCount(15);
			rabbit_->SetTextData(14);
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::TEXT));
			break;

		case Event::EVENT::SPEED_UP:
			player_->SetParam(PlayerBase::MAX_MOVE_SPEED * 1.5f, PlayerBase::MAX_JUMP_POW * 1.5f);
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::SPEEDUP));
			SetParamCount(15);
			rabbit_->SetTextData(13);
			break;

		case Event::EVENT::BLOCK_SPEED_UP:
			block_->SetFallSpeed(BlockBase::FALL_SPEED * 3);
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::SPEEDUP));
			SetParamCount(15);
			rabbit_->SetTextData(17);
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::TEXT));
			break;

		default:
			break;

			checkState = newState;
		}
	}

	switch (checkState)
	{
	case Event::EVENT::BLAST_LINE:
		if (isChange_)
		{
			event_->SetEvent(Event::EVENT::NONE);
		}
		break;

	case Event::EVENT::FIRE_BALL:
		CreateFireBall();
		break;

	case Event::EVENT::SPEED_DOWN:
		efectPos = AsoUtility::V2Sub(player_->GetPos().ToVector2(), Vector2{ 30,30 });
		event_->SetEfectPos(efectPos);
		if (PlayerSpeedCount())
		{
			event_->SetEvent(Event::EVENT::NONE);
			player_->SetParam(PlayerBase::MAX_MOVE_SPEED, PlayerBase::MAX_JUMP_POW);
		}
		break;

	case Event::EVENT::SPEED_UP:
		efectPos = AsoUtility::V2Sub(player_->GetPos().ToVector2(), Vector2{ 30,30 });
		event_->SetEfectPos(efectPos);
		if (PlayerSpeedCount())
		{
			event_->SetEvent(Event::EVENT::NONE);
			player_->SetParam(PlayerBase::MAX_MOVE_SPEED, PlayerBase::MAX_JUMP_POW);
		}
		break;

	case Event::EVENT::BLOCK_SPEED_UP:
		efectPos = AsoUtility::V2Sub(block_->GetMinoPos().ToVector2(), Vector2{30,30});
		event_->SetEfectPos(efectPos);
		if (PlayerSpeedCount())
		{
			event_->SetEvent(Event::EVENT::NONE);
			block_->SetFallSpeed(BlockBase::FALL_SPEED);
		}
		break;

	default:
		break;
	}
}


void Marason::CreateFireBall()
{
	//一定時間
	int createSecond = 5 * SceneManager::DEFAULT_FPS;

	//一度に作る生成数
	int blockHeight = GetBlockHeight();
	int createCnt = 5;
	if (blockHeight > 100) { createCnt = 15; }
	else if (blockHeight > 80) { createCnt = 10; }
	else if (blockHeight > 60) { createCnt = 7; }
	else if (blockHeight > 40) { createCnt = 5; }
	else if (blockHeight > 20) { createCnt = 4; }
	else { createCnt = 3; }

	if (fireCnt_ % createSecond == 0)
	{
		for (int i = 0; i < createCnt; i++)
		{
			FireBall* fire = GetValidFireBall();

			//爆発の生成
			fire->Create(this, 3);
		}
	}
	
	//時間減らす
	fireCnt_--;

	if (fireCnt_ <= 0)
	{
		event_->SetEvent(Event::EVENT::NONE);
	}
}

void Marason::SetTimeCount(int value)
{
	fireCnt_ = value * SceneManager::DEFAULT_FPS;
}

FireBall* Marason::GetValidFireBall()
{
	FireBall* fire = new FireBall();
	fire_.push_back(fire);
	return fire;
}
