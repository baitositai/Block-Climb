#include<Dxlib.h>
#include "../../Scene/MenuScene.h"
#include "../../Application.h"
#include "MenuPlayer.h"


MenuPlayer::MenuPlayer()
{
}

MenuPlayer::~MenuPlayer()
{
}

void MenuPlayer::Init(MenuScene* parent)
{
	menu_ = parent;

	PLAYER_TYPE type = static_cast<PLAYER_TYPE>(rand() % static_cast<int>(PLAYER_TYPE::MAX));
	Load(type);

	Reset();
}

void MenuPlayer::Reset()
{
	fiexdPos_ = { Application::SCREEN_SIZE_X - 300,
				  Application::SCREEN_SIZE_Y - (200 + SIZE_Y)};
	pos_ = fiexdPos_;
	animState_ = ANIM_STATE::IDLE;
	cntAnim_ = 0;
	animSpeed_ = 0.2f;
}

void MenuPlayer::Update()
{
	//アニメーションのカウント
	cntAnim_ = cntAnim_ + 1;

	if (state_ == MOVE_STATE::ADMISSION) { Admission(); }
	if (state_ == MOVE_STATE::EXIT) { Exit(); }
}

void MenuPlayer::Draw()
{
	//アニメーション
	int animState = static_cast<int>(animState_);
	int animNum;

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
	if (animState_ == ANIM_STATE::JUMP || animState_ == ANIM_STATE::DIE)
	{ animNum = 0; }
	else
	{ animNum = static_cast<int>(cntAnim_ * animSpeed_) % numAnim_; }

	//プレイヤーの描画
	DrawRotaGraph(pos_.x,
		pos_.y,
		3.5f,	//拡大
		rot_,	//回転
		Images_[animState][animNum],
		true,	//分からん
		dir_);	//向き
}

void MenuPlayer::Admission()
{
	animState_ = ANIM_STATE::RUN;
	dir_ = true;
	//移動処理
	pos_.x -= SPEED;

	//移動の終わり
	if (fiexdPos_.x >= pos_.x)
	{
		state_ = MOVE_STATE::NONE;
		animState_ = ANIM_STATE::IDLE;
	}
}

void MenuPlayer::Exit()
{
	animState_ = ANIM_STATE::RUN;
	dir_ = false;
	//移動処理
	pos_.x += SPEED;

	//移動の終わり
	if (Application::SCREEN_SIZE_X + SIZE_X + 20 <= pos_.x)
	{
		state_ = MOVE_STATE::NONE;
		animState_ = ANIM_STATE::IDLE;
	}
}

void MenuPlayer::SetState(MOVE_STATE state)
{
	state_ = state;
}
