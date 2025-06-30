#include<Dxlib.h>
#include "../../Scene/MenuScene.h"
#include "../../Application.h"
#include "MenuPlayer.h"


MenuPlayer::MenuPlayer()
{
	menu_ = nullptr;
	state_ = MOVE_STATE::NONE;
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
	fiexdPos_ = { FIXED_POS_X,FIXED_POS_Y};
	pos_ = fiexdPos_;
	animState_ = ANIM_STATE::IDLE;
	cntAnim_ = 0;
	animSpeed_ = ANIM_SPEED;
}

void MenuPlayer::Update()
{
	//�A�j���[�V�����̃J�E���g
	cntAnim_ = cntAnim_ + 1;

	if (state_ == MOVE_STATE::ADMISSION) { Admission(); }
	if (state_ == MOVE_STATE::EXIT) { Exit(); }
}

void MenuPlayer::Draw()
{
	//�A�j���[�V����
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
	if (animState_ == ANIM_STATE::JUMP || animState_ == ANIM_STATE::DIE)
	{ animNum = 0; }
	else
	{ animNum = static_cast<int>(cntAnim_ * animSpeed_) % numAnim_; }

	//�v���C���[�̕`��
	DrawRotaGraph(pos_.x,
		pos_.y,
		PLAYER_RATE,	//�g��
		rot_,			//��]
		Images_[animState][animNum],
		true,			//����
		dir_);			//����
}

void MenuPlayer::Admission()
{
	animState_ = ANIM_STATE::RUN;
	dir_ = true;
	//�ړ�����
	pos_.x -= SPEED;

	//�ړ��̏I���
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
	//�ړ�����
	pos_.x += SPEED;

	//�ړ��̏I���
	if (EXIT_FINISH <= pos_.x)
	{
		state_ = MOVE_STATE::NONE;
		animState_ = ANIM_STATE::IDLE;
	}
}

void MenuPlayer::ChangeState(const MOVE_STATE state)
{
	state_ = state;
}
