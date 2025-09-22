#include "Level2.h"

#include "../../../Application.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Utility/Collision.h"

#include "../Block/BlockBase.h"
#include "../Block/Block2.h"
#include "../PlayerBase.h"
#include "../BackGround.h"
#include "../Moon/Moon2.h"
#include "../Camera/Camera.h"
#include "../Side/SideBase.h"
#include "../Side/Side2.h"

Level2::Level2(void)
{
	moon_ = nullptr;
}

Level2::~Level2(void)
{
}

void Level2::AddInit()
{	
	moon_ = new Moon2();
	moon_->Init(this);

	//ブロックの読み込み
	block_ = new Block2();
	block_->Init(this);

	side_ = new Side2();
	side_->Init(this);

	player_->SetParam(PlayerBase::MAX_MOVE_SPEED, PlayerBase::MAX_JUMP_POW * PLAYER_JUMP_BUFF);

}

void Level2::Update(void)
{
	//ヒットストップ処理
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}

	LevelManager::Update();
	moon_->Update();
	HitMoon();

}

void Level2::Draw(void)
{
	// 振動
	if (hitStopCnt_ > 0)
	{
		// 描画先のスクリーンを設定 ヒットストップ中は、
		SetDrawScreen(tmpScreen_);
	}
	backGround_->Draw();
	block_->Draw();
	player_->Draw();
	camera_->Draw();
	moon_->Draw();
	side_->Draw();
	DebagDraw();
	CameraShake();
}

void Level2::Release(void)
{
	side_->Release();
	delete side_;

	block_->Release();
	delete block_;

	moon_->Release();
	delete moon_;

	LevelManager::Release();
}

void Level2::SetParam()
{	
	// フィールドと地面のサイズを設定
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };
	groundSize_ = { GROUND_WIDTH, GROUND_HEIGHT };

	// ステージサイズを設定
	stageSize_ = {
		groundSize_.x,
		fieldSize_.y + STAGE_EXTRA_HEIGHT
	};

	float fieldY = static_cast<float>(fieldSize_.y);  // フィールドの縦サイズを計算に使うため float に変換

	// プレイヤーの初期位置を設定
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2 - PLAYER_OFFSET_X,
		BlockBase::BLOCK_SIZE_Y * (fieldY - PLAYER_OFFSET_Y_BLOCK) - PLAYER_PIXEL_ADJUST_Y
	};

	// カメラの初期位置を設定
	firstCameraPos_ = {
		0,
		-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + CAMERA_OFFSET_BLOCK_Y)
	};

	// ゴールの座標を設定
	goalPos_ = {
		Application::SCREEN_SIZE_X / 2 + GOAL_OFFSET_X,
		GOAL_POS_Y
	};

	// 描画中心の位置を計算して設定
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- stageSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2,
		0
	};

}

void Level2::HitMoon()
{
	auto& snd = SoundManager::GetInstance();
	//プレイヤー情報の取得
	Vector2 pPos = player_->GetPos().ToVector2();
	Vector2 pSize = player_->GetSize();			//プレイヤーのx座標の半分を半径とする
	int pRadius = pSize.x / 2;

	//赤い月の取得
	Vector2 rPos = moon_->GetPos(Moon::MOON_TYPE::CREATE).ToVector2();

	if (Collision::IsCollisionCircle(pPos, pRadius, rPos, Moon::RADIUS) && moon_->IsMoon(Moon::MOON_TYPE::CREATE) == false)
	{
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::CREATE_MOON_HIT));
		moon_->SetIsMoon(Moon::MOON_TYPE::CREATE, true);
		block_->ResetMino();
	}

	//青い月の取得
	Vector2 bPos = moon_->GetPos(Moon::MOON_TYPE::CHANGE).ToVector2();
	bool Hit = Collision::IsCollisionCircle(pPos, pRadius, bPos, Moon::RADIUS);
	bool isBlue = moon_->IsMoon(Moon::MOON_TYPE::CHANGE);

	if (Hit && !isBlue)
	{
 		moon_->SetIsMoon(Moon::MOON_TYPE::CHANGE, true);
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::CHANGE_MOON_HIT));
		block_->ChangeNextBlock();
	}
	else if (!Hit && isBlue)
	{
		moon_->SetIsMoon(Moon::MOON_TYPE::CHANGE, false);
	}
}

Moon* Level2::GetMoonInstans()
{
	return moon_;
}
