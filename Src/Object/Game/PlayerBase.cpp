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

//�R���X�g���N�^
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

//�f�X�g���N�^
PlayerBase::~PlayerBase(void)
{

}

//�����������i�ŏ��̈��̂ݎ��s�j
void PlayerBase::Init(LevelManager* scene)
{
	//�Q�[���V�[���̋@�\���g����悤��
	level_ = scene;

	//�摜�̓ǂݍ���
	//srand(100);

	PLAYER_TYPE type = static_cast<PLAYER_TYPE>(rand() % static_cast<int>(PLAYER_TYPE::MAX));
	Load(type);

	//�ϐ��̏�����
	Reset();
	
}

void PlayerBase::Reset()
{
	//�v���C���[�̃X�e�[�^�X�̏�����
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

	//�A�j���[�V�����Ɋւ��鏉����
	animState_ = ANIM_STATE::IDLE;
	cntAnim_ = 0;
	animSpeed_ = ANIM_SPEED;

	//�Փ˔���p
	hitPos_ = { 0, 0 };					//���S���W
	hitBox_ = { SIZE_X / 2 - PLAYER_HIT_RANGE_OFFSET_X,			//�͈�
				SIZE_Y / 2 - PLAYER_HIT_RANGE_OFFSET_Y };		
	hit_ = HIT::NONE;

	//�������̊i�[
	pad_ = InputManager::JOYPAD_NO::PAD1;
}

//�X�V�����i���x���s�j
void PlayerBase::Update(void)
{
	//�A�j���[�V�����̃J�E���g
	cntAnim_++;

	//���[�V�����̏��������s��(�W�����v������Ȃ��Ƃ�)
	if (isJump_ == false)
	{
		animState_ = ANIM_STATE::IDLE;
	}

	//�v���C���[�����S���ĂȂ��Ƃ�
	if (!isDeath_)
	{
		//�v���C���[�̈ړ�����
		ProcessMove();

		//����
		Decelerate(MOVE_DEC);

		//�ړ�(���ۂ̍��W�ړ�)
		Move();

		//�W�����v����
		ProcessJump();

		//�d�͂�������
		AddGravity();

		//�W�����v
		Jump();

		CheckDeath();
	}	
	else
	{
		DeathAnimation();
	}

}

//�`�揈���i���x���s�j
void PlayerBase::Draw(void)
{
	int animState = static_cast<int>(animState_);
	int animNum;
	Vector2F cameraPos = level_->GetCameraPos();

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
	if (animState_ == ANIM_STATE::JUMP|| 
		animState_ == ANIM_STATE::DIE)
	{
		animNum = 0;
	}
	else
	{
		animNum = static_cast<int>(cntAnim_ * animSpeed_) % numAnim_;
	}

	//�v���C���[�̕`��
	DrawRotaGraph(pos_.x,
		pos_.y - cameraPos.y,
		1.0f,	//�g��
		rot_,	//��]
		Images_[animState][animNum],
		true,	//����
		dir_);	//����

}

//������� (�I�������̂ݎ��s)
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
	//�A�j���[�V�����Ǘ��p
	int anim;

	//��ޕ��̃v���C���[�摜�̕�����Ǘ��p
	std::string playerType[static_cast<int>(PLAYER_TYPE::MAX)];
	playerType[static_cast<int>(PLAYER_TYPE::DUDU)] = "Player/Mask Dude/";
	playerType[static_cast<int>(PLAYER_TYPE::FROG)] = "Player/Ninja Frog/";
	playerType[static_cast<int>(PLAYER_TYPE::MAN)] = "Player/Pink Man/";
	playerType[static_cast<int>(PLAYER_TYPE::GUY)] = "Player/Virtual Guy/";

	int i = static_cast<int>(type);

	//�v���C���[�摜�ǂݍ���
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

	//�E�ړ�
	if (ins.IsNew(KEY_INPUT_RIGHT) ||
		stickX > 0)
	{	
		dir_ = false;
		animState_ = ANIM_STATE::RUN;
		Accele(MOVE_ACC);			//����
	}

	//���ړ�
	if (ins.IsNew(KEY_INPUT_LEFT) ||
		stickX < 0)
	{
		dir_ = true;
		animState_ = ANIM_STATE::RUN;
		Accele(-MOVE_ACC);			//����
	}
}

void PlayerBase::Move()
{
	//���W�̃o�b�N�A�b�v
	prePos_ = pos_;
	
	//�v���C���[�̈ړ�
	pos_.x += speed_;
	
	//�Փ˔���
	if (speed_ > 0 || speed_ < 0)
	{
		if (CollisionRight() || CollisionLeft())
		{
			pos_.x = prePos_.x;
		}
	}
}

//��������
void PlayerBase::Accele(float speed)
{
	speed_ += speed;

	//���x����(�E����)
	if (speed_ > maxSpeed_)
	{
		speed_ = maxSpeed_;
	}

	//���x����(������)
	if (speed_ < -maxSpeed_)
	{
		speed_ = -maxSpeed_;
	}
}

//��������
void PlayerBase::Decelerate(float speed)
{
	//�E�����̈ړ�������������
	if (speed_ > 0.0f)
	{
		speed_ -= speed;

		if (speed_ < 0.0f)
		{
			speed_ = 0.0f;
		}
	}

	//�������̈ړ�������������
	if (speed_ < 0.0f)
	{
		speed_ += speed;

		if (speed_ > 0.0f)
		{
			speed_ = 0.0f;
		}
	}
}

//�d��
void PlayerBase::AddGravity(void)
{
	int isCollisionFoot = CollisionFoot();
	if (isCollisionFoot == -1)		//���ĂȂ��Ƃ�
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

	//�W�����v����
	if ((ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsPadBtnTrgDown(pad_, InputManager::JOYPAD_BTN::RIGHT) ||
		stickY < 0) &&
		(isJump_ == false &&					//�W�����v���ɉ����Ă�����
		cntJumpInput_ < INPUT_JUMP_FRAME))
	{
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::PLAYER, static_cast<int>(SoundManager::PLAYER::JUMP));
		SetJumpPow(-maxJumpPow_);
		isJump_ = true;
		animState_ = ANIM_STATE::JUMP;
		cntJumpInput_ += 1;							//�W�����v�J�E���^�𑝂₷
	}
}

void PlayerBase::Jump(void)
{
	//���W�̃o�b�N�A�b�v
	prePos_ = pos_;

	//�u���b�N�̈ړ��ʂ��擾
	float speed = level_->GetFallSpeed();

	//�W�����v
	pos_.y += jumpPow_;

	//���̏Փ˔���
	if (CollisionHead())
	{
		pos_.y = prePos_.y + speed;
		SetJumpPow(1.0f);
	}

	//�����̏Փ˔���
	if (CollisionFoot() == 0)
	{
		pos_.y += speed - 1.0f;
		SetJumpPow(0.0f);
		cntJumpInput_ = 0;			//�ڒn������W�����v�J�E���^�����ɖ߂�
		isJump_ = false;			//�n�ʂɂ����̂ŃW�����v�����Z�b�g����
	}
	
	if (CollisionFoot() == 1)
	{
		pos_.y = prePos_.y;
		SetJumpPow(0.0f);
		cntJumpInput_ = 0;			//�ڒn������W�����v�J�E���^�����ɖ߂�
		isJump_ = false;			//�n�ʂɂ����̂ŃW�����v�����Z�b�g����
	}
}

void PlayerBase::SetJumpPow(float pow)
{
	//�W�����v�͂�ݒ�
	jumpPow_ = pow;

	//�d�͂�������߂���̂�h��
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

//���S���̃A�j���[�V����
void PlayerBase::DeathAnimation()
{
	constexpr float DEATH_ANIM_SPEED = 80.0f;						//�A�j������
	constexpr float RAD_PER_FREAM = 2 * DX_PI_F / DEATH_ANIM_SPEED;	//SIN�p�̌v�Z
	constexpr float HEIGHT = 120.0f;								//�㏸����
	constexpr float ROT_SPEED = 0.3f;								//��]�X�s�[�h

	deathCnt_++;
	rot_ += ROT_SPEED;

	if (pos_.y >deathPos_.y)
	{
		//���ɉ����鏈��
		pos_.y += maxJumpPow_;
	}
	else
	{
		//��ђ��˂鏈��
		if (!fallSound_) { SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::PLAYER, static_cast<int>(SoundManager::PLAYER::FALL)); }
		fallSound_ = true;
		pos_.y = -HEIGHT * sin(RAD_PER_FREAM * deathCnt_) + deathPos_.y;
	}
}
//�v���C���[�̍��W��Ԃ�
Vector2F PlayerBase::GetPos()
{
	return pos_;
}

//�v���C���[�̊e���ʂ̍��W��Ԃ�
Vector2 PlayerBase::GetColPos(COL_LR lr, COL_TD td)
{
	Vector2 ret = pos_.ToVector2();

	//���΍��W�𑫂�
	ret.x += hitPos_.x;
	ret.y += hitPos_.y;

	//���E
	switch (lr)
	{
	case COL_LR::L:
		ret.x -= hitBox_.x;
		break;
	case COL_LR::R:
		ret.x += hitBox_.x;
		break;
	}

	//�㉺
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
	//�������W(���S)
	Vector2 HeadPosC = GetColPos(COL_LR::C, COL_TD::T);

	//�������W(��)
	Vector2 HeadPosL = GetColPos(COL_LR::L, COL_TD::T);

	//�������W(�E)
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
	//���W(�E����)
	Vector2 RightPosC = GetColPos(COL_LR::R, COL_TD::C);

	//���W(�E��)
	Vector2 RightPosT = GetColPos(COL_LR::R, COL_TD::T);

	//���W(�E��)
	Vector2 RightPosD = GetColPos(COL_LR::R, COL_TD::D);

	//�}�b�v�`�b�v�̏Փ˔���i�E���j
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
	//���W(������)
	Vector2 LeftPosC = GetColPos(COL_LR::L, COL_TD::C);

	//���W(����)
	Vector2 LeftPosT = GetColPos(COL_LR::L, COL_TD::T);

	//���W(����)
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
	//�������W(���S)
	Vector2 footPosC = GetColPos(COL_LR::C, COL_TD::D);

	//�������W(��)
	Vector2 footPosL = GetColPos(COL_LR::L, COL_TD::D);

	//�������W(�E)
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