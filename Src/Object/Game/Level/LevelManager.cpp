#include <DxLib.h>
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"
#include "../../../Common/Data.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Utility/Collision.h"
#include "../../../Scene/GameScene.h"
#include "../../../Manager/InputManager.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../BackGround.h"
#include "../Camera/Camera.h"
#include "../Moon/Moon.h"
#include "../Side/SideBase.h"
#include "../Event/Event.h"
#include "LevelManager.h"

LevelManager::LevelManager(void)
{
	gameScene_ = nullptr;
	block_ = nullptr;
	camera_ = nullptr;
	moon_ = nullptr;
	player_ = nullptr;
	backGround_ = nullptr;
	side_ = nullptr;
	event_ = nullptr;
	isGameClear_ = false;
	isGameOver_ = false;
	hitStopCnt_ = 0;
	tmpScreen_ = 0;
}

LevelManager::~LevelManager(void)
{
}

void LevelManager::Init(GameScene* parent)
{
	SetParam();

	gameScene_ = parent;

	camera_ = new Camera();
	camera_->Init(this);

	player_ = new PlayerBase();
	player_->Init(this);

	backGround_ = new BackGround();
	backGround_->Init();

	// 一時的な描画領域
	tmpScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	//初期化処理
	Reset();

	//各レベルごとに追加の読み込み
	AddInit();
}

void LevelManager::SetParam()
{
}

void LevelManager::Reset()
{
	hitStopCnt_ = 0;
	isGameClear_ = false;
	isGameOver_ = false;
}

void LevelManager::Update(void)
{
	//ゲームオーバーチェック
	GameOverCheck();

	//ゲームクリアチェック
	GameClearCheck();

	block_->Update();
	player_->Update();
	backGround_->Update();
	camera_->Update();
	side_->Update();
	
}

void LevelManager::Draw(void)
{
	backGround_->Draw();
	block_->Draw();
	player_->Draw();
	camera_->Draw();
	side_->Draw();
	//DebagDraw();
}

void LevelManager::Release(void)
{
	backGround_->Release();
	delete backGround_;
	player_->Release();
	delete player_;
	camera_->Release();
	delete camera_;
}

void LevelManager::AddInit()
{
}

void LevelManager::GoalHit()
{
	//プレイヤー情報の取得
	Vector2 pPos = player_->GetPos().ToVector2();
	Vector2 pSize = player_->GetSize();			//プレイヤーのx座標の半分を半径とする
	int pRadius = pSize.x / 2;

	//ゴール情報の取得
	Vector2 mPos = moon_->GetPos(Moon::MOON_TYPE::GOAL).ToVector2();

	if (Collision::IsCollisionCircle(pPos, pRadius, mPos, Moon::RADIUS))
	{
		SetStopCnt(HIT_STOP_CNT);
		isGameClear_ = true;
	}
}

void LevelManager::GameClearCheck()
{
	if (isGameClear_)
	{
		StopBGM();
		gameScene_->ChangeState(GameScene::STATE::CLEAR);
	}
}

void LevelManager::GameOverCheck()
{
	IsCameraRange();

	if (isGameOver_)
	{
		gameScene_->ChangeState(GameScene::STATE::OVER);
	}
}

//プレイヤーとブロックの衝突判定
bool LevelManager::IsHitBlocks(Vector2 Pos, Vector2 Size)
{
	//フィールドとの当たり判定
	if (IsHitField(Pos))
	{
		return true;
	}
	//ミノとの当たり判定
	if (IsHitMino(Pos , Size))
	{
		return true;
	}
	return false;
}

bool LevelManager::IsHitField(Vector2 Ppos)
{
	//プレイヤー座標をテトリスの描画位置分引く
	Vector2 pPos = { Ppos.x + BlockBase::BLOCK_SIZE_X / 2 - game_Draw_Center_.x,
					Ppos.y + BlockBase::BLOCK_SIZE_Y / 2 };
	
	//座標をフィールド座標へ変換する
	Vector2 fieldPpos = Field2Pos(pPos);
	
	//衝突判定
	if (block_->IsHitBlock(fieldPpos))
	{
		return true;
	}
	return false;
}

bool LevelManager::IsHitMino(Vector2 Ppos ,Vector2 Psize)
{
	//ミノの座標を得る
	Vector2 minoPos = block_->GetMinoPos().ToVector2();

	//ミノの種類を得る
	int minoType = block_->GetMinoType();

	//当たり判定用のサイズを得る
	Vector2 mSize = block_->GetSize();
	mSize.x = mSize.x / (BlockBase::BLOCK_SIZE_X);
	mSize.y = mSize.y / (BlockBase::BLOCK_SIZE_Y);

	for (int i = 0; i < BlockBase::MINO_HEIGHT; i++)
	{
		for (int j = 0; j < BlockBase::MINO_WIDTH; j++)
		{
			//ミノのブロックの位置を確認
			if (block_->GetMinoShapes(minoType, j, i) == 1)
			{
				//ブロックの座標を得る
				Vector2 minoBlockPos = block_->GetMinoBlockPos(minoPos, j, i);

				//衝突判定
				if (Collision::IsCollisionRectCenter(Ppos, Psize, minoBlockPos, mSize))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//ミノの移動前の当たり判定確認
bool LevelManager::IsPlayerCheck(AsoUtility::DIR value, Vector2 Mino, int MinoType)
{
	////ミノの座標を得る
	//Vector2 minoPos = block_->GetMinoPos().ToVector2();

	////ミノの種類を得る
	//int minoType = block_->GetMinoType();

	////プレイヤーサイズを得る
	//Vector3\

	//Vector2 PlayerPosC;
	//Vector2 PlayerPosL;
	//Vector2 PlayerPosR;

	//switch (value)
	//{
	//case AsoUtility::DIR::RIGHT:

	//	minoPos.x += BlockBase::BLOCK_SIZE_X;

	//	//右側座標
	//	PlayerPosC = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::R, PlayerBase::COL_TD::C));
	//	PlayerPosL = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::R, PlayerBase::COL_TD::T));
	//	PlayerPosR = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::R, PlayerBase::COL_TD::D));
	//	if (IsHitMino(PlayerPosC) ||
	//		IsHitMino(PlayerPosL) ||
	//		IsHitMino(PlayerPosR))
	//	{
	//		return true;
	//	}
	//	break;

	//case AsoUtility::DIR::DOWN:

	//	//頭部座標
	//	PlayerPosC = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::C, PlayerBase::COL_TD::T));
	//	PlayerPosL = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::L, PlayerBase::COL_TD::T));
	//	PlayerPosR = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::R, PlayerBase::COL_TD::T));
	//	if (IsHitMino(PlayerPosC) ||
	//		IsHitMino(PlayerPosL) ||
	//		IsHitMino(PlayerPosR))
	//	{
	//		return true;
	//	}
	//	break;

	//case AsoUtility::DIR::LEFT:

	//	minoPos.x -= BlockBase::BLOCK_SIZE_X;

	//	//左側座標
	//	PlayerPosC = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::L, PlayerBase::COL_TD::C));
	//	PlayerPosL = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::L, PlayerBase::COL_TD::T));
	//	PlayerPosR = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::L, PlayerBase::COL_TD::D));
	//	if (IsHitMino(PlayerPosC) ||
	//		IsHitMino(PlayerPosL) ||
	//		IsHitMino(PlayerPosR))
	//	{
	//		return true;
	//	}
	//	break;

	//default:
	//	break;
	//}
	return false;
}

void LevelManager::IsCameraRange()
{
	if (camera_->IsCameraRange(player_->GetPos().ToVector2(), player_->GetSize()))
	{
		if (!player_->IsDeath())
		{
			SetStopCnt(HIT_STOP_CNT);
			player_->SetIsDeath(true);
			return;
		}

		isGameOver_ = true;
	}

	if (camera_->IsCameraRange(block_->GetMinoPos().ToVector2(), block_->GetSize()))
	{
		if (!player_->IsDeath())
		{
			block_->ResetMino();
		}
	}
}

//プレイヤーの座標をずらす処理
void LevelManager::PlayerShift(AsoUtility::DIR value)
{
	Vector2F shift = { 0,0 };

	switch (value)
	{

	case AsoUtility::DIR::RIGHT:
		shift = { BlockBase::BLOCK_SIZE_X ,0 };
		break;

	case AsoUtility::DIR::DOWN:
		shift = { 0, BlockBase::BLOCK_SIZE_Y };
		break;

	case AsoUtility::DIR::LEFT:
		shift = { -BlockBase::BLOCK_SIZE_X,0 };
		break;

	default:
		break;
	}

	player_->SetPos(shift);
}

//座標をテトリス用座標に変換する
Vector2 LevelManager::Field2Pos(Vector2 worldPos)
{
	Vector2 ret;

	int mapX = worldPos.x / BlockBase::BLOCK_SIZE_X;
	int mapY = worldPos.y / BlockBase::BLOCK_SIZE_Y;

	ret.x = mapX;
	ret.y = mapY;

	return ret;
}

//ワールド用に座標の返還
Vector2 LevelManager::World2Pos(Vector2 fieldPos)
{
	Vector2 ret;

	int mapX = fieldPos.x * BlockBase::BLOCK_SIZE_X;
	int mapY = fieldPos.y * BlockBase::BLOCK_SIZE_Y;

	ret.x = mapX;
	ret.y = mapY;

	return ret;
}

void LevelManager::DebagDraw()
{
	////ミノの座標
	//Vector2F mPos = block_->GetMinoPos();
	//
	//DrawFormatString(0
	//	, 0
	//	, 0x000000
	//	, "ミノの座標 = (%f, %f)"
	//	, mPos);
	//
	////プレイヤーの座標
	//Vector2F pPosF = player_->GetPos();
	//
	//DrawFormatString(0, 
	//	16,
	//	0x000000,
	//	"プレイヤー座標=(%f, %f)",
	//	pPosF.x,
	//	pPosF.y);
	//
	////プレイヤーのフィールド座標
	//Vector2 pPos = pPosF.ToVector2();
	//pPos = { pPos.x - game_Draw_Center_.x,pPos.y };
	//Vector2 mapPos = Field2Pos(pPos);
	//
	//DrawFormatString(0,
	//	32,
	//	0x000000,
	//	"プレイヤーマップ座標=(%d, %d)",
	//	mapPos.x,
	//	mapPos.y);
	//
	////カメラの座標
	//Vector2F cPos = camera_->GetPos();
	//
	//DrawFormatString(0, 48, 0x000000,
	//	"カメラの座標=(%.1f, %.1f)",
	//	cPos.x,
	//	cPos.y);
	//
	//DrawCircle
	//(cPos.x,
	//	cPos.y,
	//	50,
	//	0x00ffff,
	//	true);
	//
	////ミノの落下速度
	//float fallSpeed = block_->GetFallSpeed();
	//
	//DrawFormatString(0, 64, 0x000000,
	//	"落下速度=(%.1f)",
	//	fallSpeed);
}

void LevelManager::SetGameClear(bool value)
{
	isGameClear_ = value;
}

void LevelManager::SetGameOver(bool value)
{
	isGameOver_ = value;
}

void LevelManager::SetStopCnt(int cnt)
{
	StopBGM();
	SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::PLAYER, static_cast<int>(SoundManager::PLAYER::DEAD));
	hitStopCnt_ = cnt;
}

void LevelManager::CameraShake()
{
	// 振動
	if (hitStopCnt_ > 0)
	{
		// 描画先を裏画面に設定
		SetDrawScreen(DX_SCREEN_BACK);

		// シェイク方向の決定
		int shake = hitStopCnt_ / HITSTOP_SHAKE_INTERVAL % SHAKE_SCALE;

		// 倍率変換
		shake *= SHAKE_SCALE;

		// オフセット調整
		shake -= SHAKE_OFFSET;

		// 実際に移動させる距離へ変換
		shake *= SHAKE_DISTANCE;

		// 指定したオフセット位置に一時スクリーンを描画（画面を揺らす）
		DrawGraph(shake, shake, tmpScreen_, true);
	}
}

void LevelManager::NextBlockDraw(Vector2 pos)
{
	Vector2 blockPos = pos;

	block_->NextBlockDraw(blockPos, NEXT_BLOCK_RATE);
}

void LevelManager::ShiftGame()
{
	//プレイヤーずらし
	Vector2F pPos = { 0,BlockBase::BLOCK_SIZE_Y };
	player_->SetPos(pPos);

	//カメラずらし
	Vector2F cPos = camera_->GetPos();
	cPos.y += BlockBase::BLOCK_SIZE_Y;
	camera_->SetPos(cPos);
}

void LevelManager::IconDraw(Vector2 pos)
{
	Vector2 drawPos = pos;

	event_->IconDraw(drawPos);
}

void LevelManager::PlayBGM()
{
	gameScene_->PlayBGM();
}

void LevelManager::StopBGM()
{
	gameScene_->StopBGM();
}

int LevelManager::GetFieldBlockY(int y)
{
	return block_->GetFieldBestBlockY(y);
}

int LevelManager::GetBlockHeight()
{
	return block_->GetNowHeight();
}

int LevelManager::GetBlockCnt()
{
	return block_->GetBlockCount();
}

int LevelManager::GetCntLine()
{
	return block_->GetLineCount();
}

float LevelManager::GetFallSpeed()
{
	return block_->GetFallSpeed();
}

Vector2F LevelManager::GetCameraPos()
{
	return camera_->GetPos();
}

Vector2F LevelManager::GetPlayerPos()
{
	return player_->GetPos();
}

Vector2F LevelManager::GetMinoBlockPos(Vector2F pPos)
{
	Vector2F minoPos = block_->GetMinoPos();

	Vector2F mino = { (pPos.x - minoPos.x - game_Draw_Center_.x) / BlockBase::BLOCK_SIZE_X,
						(pPos.y - minoPos.y - game_Draw_Center_.y) / BlockBase::BLOCK_SIZE_Y, };
	Vector2F minoBlockPos = { mino.x * BlockBase::BLOCK_SIZE_X + minoPos.x,
								mino.y * BlockBase::BLOCK_SIZE_Y + minoPos.y };
	return minoBlockPos;
}

Moon* LevelManager::GetMoonInstans()
{
	return nullptr;
}

Event::EVENT LevelManager::GetEventState()
{
	return event_->GetEvent();
}

Vector2 LevelManager::GetFieldSize()
{
	return fieldSize_;
}

Vector2 LevelManager::GetGroundSize()
{
	return groundSize_;
}

Vector2 LevelManager::GetStageSize()
{
	return stageSize_;
}

Vector2F LevelManager::GetFirstPlayerPos()
{
	return firstPlayerPos_;
}

Vector2F LevelManager::GetFirstCameraPos()
{
	return firstCameraPos_;
}

Vector2 LevelManager::GetGoalPos()
{
	return goalPos_;
}

Vector2 LevelManager::GetGameCenter()
{
	return game_Draw_Center_;
}