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
	//�e�N���X���󂯎��
	title_ = parent;

	//�v���C���[��ނ��󂯎��
	type_ = type;

	//�摜��ǂݍ���
	Load(type_);

	//������
	Reset();
}

void TitlePlayer::Reset()
{
	//�e��ϐ�������
	fixedPos_ = { POS_X,POS_Y };
	animState_ = ANIM_STATE::IDLE;
	cntAnim_ = 0;
	animSpeed_ = ANIM_SPEED;
	titState_ = MOVE_STATE::MOVE;
	dir_ = false;


	//�L�������Ƃɒl�ݒ�
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

	//�L�����N�^�[���ƂɈړ�����
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

	//�A�j���[�V�����؂�ւ�
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

	//�A�j���[�V���������̐؂�ւ�
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

	//�A�j���[�V�����Ɋւ���v�Z
	if (animState_ == ANIM_STATE::JUMP || animState_ == ANIM_STATE::DIE) { animNum = 0; }
	else { animNum = static_cast<int>(cntAnim_ * animSpeed_) % numAnim_; }

	//�v���C���[�̕`��
	DrawRotaGraph(pos_.x,
		pos_.y,
		CHARA_RATE,	//�g��
		rot_,		//��]
		Images_[animState][animNum],
		true,		//����
		dir_);		//����
}

void TitlePlayer::Release()
{
	PlayerBase::Release();
}

bool TitlePlayer::IsText()
{
	return isText_;
}
