#include"../../Application.h"
#include "TitlePlayer.h"
#include "../../Scene/TitleScene.h"

TitlePlayer::TitlePlayer()
{
	isText_ = false;
	titState_ = MOVE_STATE::NONE;
	title_ = nullptr;
	type_ = PLAYER_TYPE::MAX;
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Init(TitleScene* parent, PLAYER_TYPE type)
{
	//親クラスを受け取る
	title_ = parent;

	//プレイヤー種類を受け取る
	type_ = type;

	//画像を読み込み
	Load(type_);

	//初期化
	Reset();
}

void TitlePlayer::Reset()
{
	//各種変数初期化
	fixedPos_ = { POS_X,POS_Y };
	animState_ = ANIM_STATE::IDLE;
	cntAnim_ = 0;
	animSpeed_ = ANIM_SPEED;
	titState_ = MOVE_STATE::MOVE;
	dir_ = false;


	//キャラごとに値設定
	int cnt = static_cast<int>(type_);
	switch (type_)
	{
	case PLAYER_TYPE::DUDU:
		pos_ = fixedPos_;
		pos_.x -= MOVES;
		break;

	case PLAYER_TYPE::FROG:
		fixedPos_.x += fixedPos_.x * cnt;
		pos_ = fixedPos_;
		pos_.x -= MOVES;
		break;

	case PLAYER_TYPE::MAN:
		fixedPos_.x += fixedPos_.x * cnt;
		pos_ = fixedPos_;
		pos_.x += MOVES;
		dir_ = true;
		break;

	case PLAYER_TYPE::GUY:
		fixedPos_.x += fixedPos_.x * cnt;
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
	if(titState_ == MOVE_STATE::MOVE)
	switch (type_)
	{
	case PLAYER_TYPE::DUDU:	
	case PLAYER_TYPE::FROG:
		pos_.x += SPEED;
		if (pos_.x > fixedPos_.x) {titState_ = MOVE_STATE::STOP; title_->SetIsText(true);}
		break;

	case PLAYER_TYPE::MAN:
	case PLAYER_TYPE::GUY:
		pos_.x -= SPEED;
		if (pos_.x < fixedPos_.x) { titState_ = MOVE_STATE::STOP; title_->SetIsText(true);}
		break;

	default:
		break;
	}

	//アニメーション切り替え
	switch (titState_)
	{
	case MOVE_STATE::MOVE:
		animState_ = ANIM_STATE::RUN;
		break;

	case MOVE_STATE::STOP:
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
		CHARA_RATE,	//拡大
		rot_,		//回転
		Images_[animState][animNum],
		true,		//透過
		dir_);		//向き
}

void TitlePlayer::Release()
{
	PlayerBase::Release();
}

bool TitlePlayer::IsText()
{
	return isText_;
}
