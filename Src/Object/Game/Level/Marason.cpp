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

Marason::Marason(void)
{
	eventLine_ = 0;
	fireCnt_ = 0;
	isChange_ = false;
	paramCnt_ = 0;
	rabbit_ = nullptr;
}

Marason::~Marason(void)
{
}

void Marason::Init(GameScene* parent)
{
	SetParam();

	gameScene_ = parent;

	camera_ = new MarasonCamera();
	camera_->Init(this);

	player_ = new PlayerBase();
	player_->Init(this);

	backGround_ = new BackGround();
	backGround_->Init();	

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
	rabbit_->Init(this);

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
	delete rabbit_;

	event_->Release();
	delete event_;
	
	side_->Release();
	delete side_;
	
	block_->Release();
	delete block_;
	
	backGround_->Release();
	delete backGround_;
	
	player_->Release();
	delete player_;
	
	camera_->Release();
	delete camera_;
}

void Marason::SetParam()
{

	// フィールドサイズの設定
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };

	// 地面サイズの設定
	groundSize_ = { FIELD_WIDTH, GROUND_HEIGHT };

	// ステージサイズの設定
	stageSize_ = {
		fieldSize_.x,
		fieldSize_.y + groundSize_.y
	};

	float fieldY = static_cast<float>(fieldSize_.y);  // フィールドの縦サイズを float に変換

	// プレイヤーの初期位置の設定
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2,
		BlockBase::BLOCK_SIZE_Y * (fieldY - PLAYER_OFFSET_BLOCK_Y) - PLAYER_PIXEL_ADJUST_Y
	};

	// カメラの初期位置の設定
	firstCameraPos_ = {
		0,
		-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + CAMERA_OFFSET_BLOCK_Y)
	};

	// ゴールの位置の設定
	goalPos_ = {
		Application::SCREEN_SIZE_X / 2 + GOAL_OFFSET_X,
		GOAL_POS_Y
	};

	// 描画位置の中心の調整
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- fieldSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2,
		0
	};

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
	// うさぎの描画位置を設定して描画
	Vector2 pos = {
		RABBIT_DRAW_OFFSET_X,
		Application::SCREEN_SIZE_Y - RabbitText::RABBIT_SIZE_Y
	};
	rabbit_->RabbitDraw(pos);

	// 吹き出しの描画位置を設定して描画
	pos = {
		SPEECH_DRAW_OFFSET_X + RabbitText::RABBIT_SIZE_X,
		Application::SCREEN_SIZE_Y - RabbitText::SPEECH_SIZE_Y + SPEECH_DRAW_OFFSET_Y
	};
	rabbit_->SpeechDraw(pos);

	// テキストの描画位置を設定して描画
	pos = {
		TEXT_DRAW_OFFSET_X + RabbitText::RABBIT_SIZE_X,
		Application::SCREEN_SIZE_Y - RabbitText::RABBIT_SIZE_Y + TEXT_DRAW_OFFSET_Y
	};
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
			rabbit_->SetTextData(RabbitMarason::BLAST_TEXT_INDEX);
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::TEXT));
			break;

		case Event::EVENT::FIRE_BALL:
			rabbit_->SetTextData(RabbitMarason::FIRE_TEXT_INDEX);
			SetTimeCount(FIRE_SECOND);
			break;

		case Event::EVENT::SPEED_DOWN:
			player_->SetParam(PlayerBase::MAX_MOVE_SPEED * DEBUFF_PERCENT, PlayerBase::MAX_JUMP_POW * DEBUFF_PERCENT);
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::SPEEDDOWN));
			SetParamCount(BUFF_SECOND);
			rabbit_->SetTextData(RabbitMarason::PLAYER_DEBUFF_TEXT_INDEX);
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::TEXT));
			break;

		case Event::EVENT::SPEED_UP:
			player_->SetParam(PlayerBase::MAX_MOVE_SPEED * BUFF_PERCENT, PlayerBase::MAX_JUMP_POW * BUFF_PERCENT);
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::SPEEDUP));
			SetParamCount(BUFF_SECOND);
			rabbit_->SetTextData(RabbitMarason::PLAYER_BUFF_TEXT_INDEX);
			break;

		case Event::EVENT::BLOCK_SPEED_UP:
			block_->SetFallSpeed(BlockBase::FALL_SPEED * BLOCK_FALL_SPEED_UP);
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::SPEEDUP));
			SetParamCount(BUFF_SECOND);
			rabbit_->SetTextData(RabbitMarason::BLOCK_FALL_SPEED_UP_TEXT_INDEX);
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
		efectPos = AsoUtility::V2Sub(player_->GetPos().ToVector2(), Vector2{ EFFECT_LOCAL_POS_X,EFFECT_LOCAL_POS_Y });
		event_->SetEfectPos(efectPos);
		if (PlayerSpeedCount())
		{
			event_->SetEvent(Event::EVENT::NONE);
			player_->SetParam(PlayerBase::MAX_MOVE_SPEED, PlayerBase::MAX_JUMP_POW);
		}
		break;

	case Event::EVENT::SPEED_UP:
		efectPos = AsoUtility::V2Sub(player_->GetPos().ToVector2(), Vector2{ EFFECT_LOCAL_POS_X,EFFECT_LOCAL_POS_Y });
		event_->SetEfectPos(efectPos);
		if (PlayerSpeedCount())
		{
			event_->SetEvent(Event::EVENT::NONE);
			player_->SetParam(PlayerBase::MAX_MOVE_SPEED, PlayerBase::MAX_JUMP_POW);
		}
		break;

	case Event::EVENT::BLOCK_SPEED_UP:
		efectPos = AsoUtility::V2Sub(block_->GetMinoPos().ToVector2(), Vector2{ EFFECT_LOCAL_POS_X,EFFECT_LOCAL_POS_Y });
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
	int createSecond = FIRE_INTERVAL_SECOND * SceneManager::DEFAULT_FPS;

	// ブロックの高さに応じた生成数を決定
	int blockHeight = GetBlockHeight();
	int createCnt = CREATE_COUNTS[CREATE_RULE_SIZE- 1]; // デフォルト（三個）

	for (int i = 0; i < CREATE_RULE_SIZE; ++i) {
		if (blockHeight > CREATE_HEIGHT_THRESHOLDS[i]) {
			createCnt = CREATE_COUNTS[i];
			break;
		}
	}

	// 指定時間ごとに生成処理
	if (fireCnt_ % createSecond == 0)
	{
		for (int i = 0; i < createCnt; ++i)
		{
			FireBall* fire = GetValidFireBall();
			fire->Create(this, CREATE_COUNTS[CREATE_RULE_SIZE - 1]);
		}
	}

	// カウント減少
	fireCnt_--;

	// イベント解除処理
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
