#include"../../Application.h"
#include "TitlePlayer.h"
#include "../../Scene/TitleScene.h"

TitlePlayer::TitlePlayer()
{
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Init(TitleScene* parent, PLAYER_TYPE type)
{
	title_ = parent;

	type_ = type;

	Load(type_);

	Reset();
}

void TitlePlayer::Reset()
{
	fixedPos_ = { Application::SCREEN_SIZE_X / 5,
					Application::SCREEN_SIZE_Y - 145 - (SIZE_Y * 1.8 / 2)};
	animState_ = ANIM_STATE::IDLE;
	cntAnim_ = 0;
	animSpeed_ = 0.2f;
	dir_ = false;

	switch (type_)
	{
	case PLAYER_TYPE::DUDU:
		pos_ = fixedPos_;
		pos_.x -= MOVES;
		break;

	case PLAYER_TYPE::FROG:
		fixedPos_.x += fixedPos_.x;
		pos_ = fixedPos_;
		pos_.x -= MOVES;
		break;

	case PLAYER_TYPE::MAN:
		fixedPos_.x += fixedPos_.x * 2;
		pos_ = fixedPos_;
		pos_.x += MOVES;
		dir_ = true;
		break;

	case PLAYER_TYPE::GUY:
		fixedPos_.x += fixedPos_.x * 3;
		pos_ = fixedPos_;
		pos_.x += MOVES;
		dir_ = true;
		break;

	default:
		break;
	}
}

void TitlePlayer::Update()
{
	cntAnim_++;

	//キャラクターごとに移動処理
	if(titState_ == TITLE_PLAYER::MOVE)
	switch (type_)
	{
	case PLAYER_TYPE::DUDU:
		pos_.x += SPEED;
		if (pos_.x > fixedPos_.x) {titState_ = TITLE_PLAYER::STOP; title_->SetIsText(true);}
		break;

	case PLAYER_TYPE::FROG:
		pos_.x += SPEED;
		if (pos_.x > fixedPos_.x) { titState_ = TITLE_PLAYER::STOP; title_->SetIsText(true);}
		break;

	case PLAYER_TYPE::MAN:
		pos_.x -= SPEED;
		if (pos_.x < fixedPos_.x) { titState_ = TITLE_PLAYER::STOP; title_->SetIsText(true);}
		break;

	case PLAYER_TYPE::GUY:
		pos_.x -= SPEED;
		if (pos_.x < fixedPos_.x) { titState_ = TITLE_PLAYER::STOP; title_->SetIsText(true); }
		break;

	default:
		break;
	}

	//アニメーション切り替え
	switch (titState_)
	{
	case TITLE_PLAYER::MOVE:
		animState_ = ANIM_STATE::RUN;
		break;

	case TITLE_PLAYER::STOP:
		animState_ = ANIM_STATE::IDLE;
		break;

	default:
		break;
	}
}

void TitlePlayer::Draw()
{
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
	if (animState_ == ANIM_STATE::JUMP || animState_ == ANIM_STATE::DIE) { animNum = 0; }
	else { animNum = static_cast<int>(cntAnim_ * animSpeed_) % numAnim_; }

	//プレイヤーの描画
	DrawRotaGraph(pos_.x,
		pos_.y,
		1.8f,	//拡大
		rot_,	//回転
		Images_[animState][animNum],
		true,	//分からん
		dir_);	//向き
}

void TitlePlayer::Release()
{
	PlayerBase::Release();
}

bool TitlePlayer::IsText()
{
	return isText_;
}
