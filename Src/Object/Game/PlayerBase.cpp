#include <string.h>
#include <DxLib.h> 
#include "../../Common/Vector2.h"
#include "../../Utility/AsoUtility.h"
#include "../../Application.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SoundManager.h"
#include "PlayerBase.h"
#include "Block/BlockBase.h"
#include "Level/LevelManager.h"

//コンストラクタ
PlayerBase::PlayerBase(void)
{
	animSpeed_ = 0.0f;
	animState_ = ANIM_STATE::MAX;
	cntAnim_ = 0;
	cntJumpInput_ = 0.0f;
	dir_ = static_cast<int>(AsoUtility::DIR::MAX);
	level_ = nullptr;
	isJump_ = false;
	jumpPow_ = 0;
	numAnim_ = 0;
	pos_ = { 0,0 };
	speed_ = 0;
	maxSpeed_ = 0;
	rot_ = 0.0f;
	isDeath_ = false;
	deathCnt_ = 0;
	fallSound_ = false;
	hit_ = HIT::NONE;
	hitPos_ = { 0, 0 };
	hitBox_ = { 0, 0 };
	pad_ = InputManager::JOYPAD_NO::PAD1;

	for (int i = 0; i < static_cast<int>(ANIM_STATE::MAX); i++)
	{
		for (int j = 0; j < IDLE_NUM_ANIM; j++)
		{
			Images_[i][j] = 0;
		}
	}
}

//デストラクタ
PlayerBase::~PlayerBase(void)
{

}

//初期化処理（最初の一回のみ実行）
void PlayerBase::Init(LevelManager* scene)
{
	//ゲームシーンの機能を使えるように
	level_ = scene;

	//画像の読み込み
	//srand(100);

	PLAYER_TYPE type = static_cast<PLAYER_TYPE>(rand() % static_cast<int>(PLAYER_TYPE::MAX));
	Load(type);

	//変数の初期化
	Reset();
	
}

void PlayerBase::Reset()
{
	//プレイヤーのステータスの初期化
	speed_ = PLAYER_SPEED;
	pos_ = level_->GetFirstPlayerPos();
	size_ = { SIZE_X,SIZE_Y };
	dir_ = false;
	rot_ = 0.0f;
	isJump_ = false;
	cntJumpInput_ = 0;
	deathCnt_ = 0;
	maxSpeed_ = MAX_MOVE_SPEED;
	maxJumpPow_ = MAX_JUMP_POW;
	fallSound_ = false;

	//アニメーションに関する初期化
	animState_ = ANIM_STATE::IDLE;
	cntAnim_ = 0;
	animSpeed_ = ANIM_SPEED;

	//衝突判定用
	hitPos_ = { 0, 0 };					//中心座標
	hitBox_ = { SIZE_X / 2 - PLAYER_HIT_RANGE_OFFSET_X,			//範囲
				SIZE_Y / 2 - PLAYER_HIT_RANGE_OFFSET_Y };		
	hit_ = HIT::NONE;

	//操作主情報の格納
	pad_ = InputManager::JOYPAD_NO::PAD1;
}

//更新処理（毎度実行）
void PlayerBase::Update(void)
{
	//アニメーションのカウント
	cntAnim_++;

	//モーションの初期化を行う(ジャンプ中じゃないとき)
	if (isJump_ == false)
	{
		animState_ = ANIM_STATE::IDLE;
	}

	//プレイヤーが死亡してないとき
	if (!isDeath_)
	{
		//プレイヤーの移動操作
		ProcessMove();

		//減速
		Decelerate(MOVE_DEC);

		//移動(実際の座標移動)
		Move();

		//ジャンプ操作
		ProcessJump();

		//重力をかける
		AddGravity();

		//ジャンプ
		Jump();

		CheckDeath();
	}	
	else
	{
		DeathAnimation();
	}

}

//描画処理（毎度実行）
void PlayerBase::Draw(void)
{
	int animState = static_cast<int>(animState_);
	int animNum;
	Vector2F cameraPos = level_->GetCameraPos();

	//アニメーション総数の切り替え
	switch (animState_)
	{
	case PlayerBase::ANIM_STATE::IDLE:
		numAnim_ = IDLE_NUM_ANIM;
		break;
	case PlayerBase::ANIM_STATE::RUN:
		numAnim_ = RUN_NUM_ANIM;
		break;
	case PlayerBase::ANIM_STATE::JUMP:
		numAnim_ = 0;
		break;
	default:
		break;
	}

	//アニメーションに関する計算
	if (animState_ == ANIM_STATE::JUMP|| 
		animState_ == ANIM_STATE::DIE)
	{
		animNum = 0;
	}
	else
	{
		animNum = static_cast<int>(cntAnim_ * animSpeed_) % numAnim_;
	}

	//プレイヤーの描画
	DrawRotaGraph(pos_.x,
		pos_.y - cameraPos.y,
		1.0f,	//拡大
		rot_,	//回転
		Images_[animState][animNum],
		true,	//透過
		dir_);	//向き

}

//解放処理 (終了時一回のみ実行)
bool PlayerBase::Release(void)
{
	for (int i = 0; i < static_cast<int>(ANIM_STATE::MAX); i++)
	{
		for (int j = 0; j < IDLE_NUM_ANIM; j++)
		{
			DeleteGraph(Images_[i][j]);
		}
	}

	return true;
}

void PlayerBase::Load(PLAYER_TYPE type)
{
	//アニメーション管理用
	int anim;

	//種類分のプレイヤー画像の文字列管理用
	std::string playerType[static_cast<int>(PLAYER_TYPE::MAX)];
	playerType[static_cast<int>(PLAYER_TYPE::DUDU)] = "Player/Mask Dude/";
	playerType[static_cast<int>(PLAYER_TYPE::FROG)] = "Player/Ninja Frog/";
	playerType[static_cast<int>(PLAYER_TYPE::MAN)] = "Player/Pink Man/";
	playerType[static_cast<int>(PLAYER_TYPE::GUY)] = "Player/Virtual Guy/";

	int i = static_cast<int>(type);

	//プレイヤー画像読み込み
	//-------------------------------------------------------------------
	anim = static_cast<int>(ANIM_STATE::JUMP);
	Images_[anim][0] = LoadGraph((Application::PATH_IMAGE + playerType[i] + "Jump.png").c_str());

	anim = static_cast<int>(ANIM_STATE::FALL);
	Images_[anim][0] = LoadGraph((Application::PATH_IMAGE + playerType[i] + "Fall.png").c_str());

	anim = static_cast<int>(ANIM_STATE::DIE);
	Images_[anim][0] = LoadGraph((Application::PATH_IMAGE + playerType[i] + "Fall.png").c_str());

	anim = static_cast<int>(ANIM_STATE::IDLE);
	LoadDivGraph(((Application::PATH_IMAGE + playerType[i] + "Idle.png").c_str())
		, IDLE_NUM_ANIM
		, IDLE_SIZE_X
		, IDLE_SIZE_Y
		, SIZE_X
		, SIZE_Y
		, &(Images_[anim][0]));

	anim = static_cast<int>(ANIM_STATE::RUN);
	LoadDivGraph(((Application::PATH_IMAGE + playerType[i] + "Run.png").c_str())
		, RUN_NUM_ANIM
		, RUN_SIZE_X
		, RUN_SIZE_Y
		, SIZE_X
		, SIZE_Y
		, &(Images_[anim][0]));

	anim = static_cast<int>(ANIM_STATE::HIT);
	LoadDivGraph(((Application::PATH_IMAGE + playerType[i] + "Hit.png").c_str())
		, HIT_NUM_ANIM
		, HIT_SIZE_X
		, HIT_SIZE_Y
		, SIZE_X
		, SIZE_Y
		, &(Images_[anim][0]));
}

void PlayerBase::ProcessMove()
{	
	auto& ins = InputManager::GetInstance();
	int stickX = ins.GetJPadInputState(pad_).AKeyRX;

	//右移動
	if (ins.IsNew(KEY_INPUT_RIGHT) ||
		stickX > 0)
	{	
		dir_ = false;
		animState_ = ANIM_STATE::RUN;
		Accele(MOVE_ACC);			//加速
	}

	//左移動
	if (ins.IsNew(KEY_INPUT_LEFT) ||
		stickX < 0)
	{
		dir_ = true;
		animState_ = ANIM_STATE::RUN;
		Accele(-MOVE_ACC);			//加速
	}
}

void PlayerBase::Move()
{
	//座標のバックアップ
	prePos_ = pos_;
	
	//プレイヤーの移動
	pos_.x += speed_;
	
	//衝突判定
	if (speed_ > 0 || speed_ < 0)
	{
		if (CollisionRight() || CollisionLeft())
		{
			pos_.x = prePos_.x;
		}
	}
}

//加速処理
void PlayerBase::Accele(float speed)
{
	speed_ += speed;

	//速度制限(右方向)
	if (speed_ > maxSpeed_)
	{
		speed_ = maxSpeed_;
	}

	//速度制限(左方向)
	if (speed_ < -maxSpeed_)
	{
		speed_ = -maxSpeed_;
	}
}

//減速処理
void PlayerBase::Decelerate(float speed)
{
	//右方向の移動を減速させる
	if (speed_ > 0.0f)
	{
		speed_ -= speed;

		if (speed_ < 0.0f)
		{
			speed_ = 0.0f;
		}
	}

	//左方向の移動を減速させる
	if (speed_ < 0.0f)
	{
		speed_ += speed;

		if (speed_ > 0.0f)
		{
			speed_ = 0.0f;
		}
	}
}

//重力
void PlayerBase::AddGravity(void)
{
	int isCollisionFoot = CollisionFoot();
	if (isCollisionFoot == -1)		//してないとき
	{
		float pow = jumpPow_ + GRAVITY;
		SetJumpPow(pow);
	}
}

void PlayerBase::ProcessJump(void)
{
	auto& ins = InputManager::GetInstance();
	auto& snd = SoundManager::GetInstance();
	int stickY = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyRY;

	//ジャンプ判定
	if ((ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsPadBtnTrgDown(pad_, InputManager::JOYPAD_BTN::RIGHT) ||
		stickY < 0) &&
		(isJump_ == false &&					//ジャンプ中に押しても無効
		cntJumpInput_ < INPUT_JUMP_FRAME))
	{
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::PLAYER, static_cast<int>(SoundManager::PLAYER::JUMP));
		SetJumpPow(-maxJumpPow_);
		isJump_ = true;
		animState_ = ANIM_STATE::JUMP;
		cntJumpInput_ += 1;							//ジャンプカウンタを増やす
	}
}

void PlayerBase::Jump(void)
{
	//座標のバックアップ
	prePos_ = pos_;

	//ブロックの移動量を取得
	float speed = level_->GetFallSpeed();

	//ジャンプ
	pos_.y += jumpPow_;

	//頭の衝突判定
	if (CollisionHead())
	{
		pos_.y = prePos_.y + speed;
		SetJumpPow(1.0f);
	}

	//足元の衝突判定
	if (CollisionFoot() == 0)
	{
		pos_.y += speed - 1.0f;
		SetJumpPow(0.0f);
		cntJumpInput_ = 0;			//接地したらジャンプカウンタを元に戻す
		isJump_ = false;			//地面についたのでジャンプをリセットする
	}
	
	if (CollisionFoot() == 1)
	{
		pos_.y = prePos_.y;
		SetJumpPow(0.0f);
		cntJumpInput_ = 0;			//接地したらジャンプカウンタを元に戻す
		isJump_ = false;			//地面についたのでジャンプをリセットする
	}
}

void PlayerBase::SetJumpPow(float pow)
{
	//ジャンプ力を設定
	jumpPow_ = pow;

	//重力がかかり過ぎるのを防ぐ
	if (jumpPow_ > maxJumpPow_)
	{
		jumpPow_ = maxJumpPow_;
	}
}

void PlayerBase::CheckDeath()
{
	if ((CollisionHead() && CollisionFoot()))
	{
		level_->SetStopCnt(LevelManager::HIT_STOP_CNT);
		isDeath_ = true;
		deathPos_ = pos_;
	}
}

//死亡時のアニメーション
void PlayerBase::DeathAnimation()
{
	constexpr float DEATH_ANIM_SPEED = 80.0f;						//アニメ速さ
	constexpr float RAD_PER_FREAM = 2 * DX_PI_F / DEATH_ANIM_SPEED;	//SIN用の計算
	constexpr float HEIGHT = 120.0f;								//上昇高さ
	constexpr float ROT_SPEED = 0.3f;								//回転スピード

	deathCnt_++;
	rot_ += ROT_SPEED;

	if (pos_.y >deathPos_.y)
	{
		//下に下がる処理
		pos_.y += maxJumpPow_;
	}
	else
	{
		//飛び跳ねる処理
		if (!fallSound_) { SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::PLAYER, static_cast<int>(SoundManager::PLAYER::FALL)); }
		fallSound_ = true;
		pos_.y = -HEIGHT * sin(RAD_PER_FREAM * deathCnt_) + deathPos_.y;
	}
}
//プレイヤーの座標を返す
Vector2F PlayerBase::GetPos()
{
	return pos_;
}

//プレイヤーの各部位の座標を返す
Vector2 PlayerBase::GetColPos(COL_LR lr, COL_TD td)
{
	Vector2 ret = pos_.ToVector2();

	//相対座標を足す
	ret.x += hitPos_.x;
	ret.y += hitPos_.y;

	//左右
	switch (lr)
	{
	case COL_LR::L:
		ret.x -= hitBox_.x;
		break;
	case COL_LR::R:
		ret.x += hitBox_.x;
		break;
	}

	//上下
	switch (td)
	{
	case COL_TD::T:
		ret.y -= hitBox_.y;
		break;
	case COL_TD::D:
		ret.y += hitBox_.y + PLAYER_COL_D_OFFSET;
		break;
	}
	return ret;
}

Vector2 PlayerBase::GetSize()
{
	return size_;
}

bool PlayerBase::IsDeath()
{
	return isDeath_;
}

bool PlayerBase::CollisionHead(void)
{
	//頭部座標(中心)
	Vector2 HeadPosC = GetColPos(COL_LR::C, COL_TD::T);

	//頭部座標(左)
	Vector2 HeadPosL = GetColPos(COL_LR::L, COL_TD::T);

	//頭部座標(右)
	Vector2 HeadPosR = GetColPos(COL_LR::R, COL_TD::T);

	if (level_->IsHitBlocks(HeadPosC, size_) ||
		level_->IsHitBlocks(HeadPosL, size_) ||
		level_->IsHitBlocks(HeadPosR, size_))
	{
		return true;
	}
	return false;
}

bool PlayerBase::CollisionRight(void)
{
	//座標(右中央)
	Vector2 RightPosC = GetColPos(COL_LR::R, COL_TD::C);

	//座標(右上)
	Vector2 RightPosT = GetColPos(COL_LR::R, COL_TD::T);

	//座標(右下)
	Vector2 RightPosD = GetColPos(COL_LR::R, COL_TD::D);

	//マップチップの衝突判定（右側）
	if (level_->IsHitBlocks(RightPosC, size_)
		|| level_->IsHitBlocks(RightPosT, size_)
		|| level_->IsHitBlocks(RightPosD, size_))
	{
		return true;
	}
	return false;
}

bool PlayerBase::CollisionLeft(void)
{
	//座標(左中央)
	Vector2 LeftPosC = GetColPos(COL_LR::L, COL_TD::C);

	//座標(左上)
	Vector2 LeftPosT = GetColPos(COL_LR::L, COL_TD::T);

	//座標(左下)
	Vector2 LeftPosD = GetColPos(COL_LR::L, COL_TD::D);

	if (level_->IsHitBlocks(LeftPosC, size_)
	|| level_->IsHitBlocks(LeftPosT, size_)
	|| level_->IsHitBlocks(LeftPosD, size_))
	{
		return true;
	}
	return false;
}

int PlayerBase::CollisionFoot(void)
{
	//足元座標(中心)
	Vector2 footPosC = GetColPos(COL_LR::C, COL_TD::D);

	//足元座標(左)
	Vector2 footPosL = GetColPos(COL_LR::L, COL_TD::D);

	//足元座標(右)
	Vector2 footPosR = GetColPos(COL_LR::R, COL_TD::D);

	if (level_->IsHitMino(footPosC, size_) ||
		level_->IsHitMino(footPosL, size_) ||
		level_->IsHitMino(footPosR, size_))
	{
		return 0;
	}

	else if (level_->IsHitField(footPosC) ||
			level_->IsHitField(footPosL) ||
			level_->IsHitField(footPosR))
	{
		return 1;
	}

	return -1;
}

void PlayerBase::SetPos(Vector2F value)
{
	pos_.x += value.x;
	pos_.y += value.y;
}

void PlayerBase::SetState(ANIM_STATE state)
{
	animState_ = state;
}

void PlayerBase::SetIsDeath(bool value)
{
	isDeath_ = value;
}

void PlayerBase::SetParam(float speed_, float jumpPow)
{
	maxSpeed_ = speed_;
	maxJumpPow_ = jumpPow;
}