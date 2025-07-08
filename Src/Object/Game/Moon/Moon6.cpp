#include <DxLib.h>
#include <cmath>
#include "../../../Application.h"
#include "../../../Common/Fader.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"
#include "../Level/LevelManager.h"
#include "../Block/BlockBase.h"
#include "Moon6.h"

Moon6::Moon6()
{
	level_ = nullptr;
	stopCnt_ = 0.0f;
	downCnt_ = 0;
	respawn_ = 0;
	alpha_ = 0;
	preBlock_ = 0;
	scroll_ = 0.0f;
	scrollSpeed_ = 0.0f;
	scrollMax_ = 0.0f;
	speed_ = {};
}

Moon6::~Moon6()
{
}

void Moon6::Reset()
{
	Moon::Reset();

	//�������̏����ݒ�
	int i = static_cast<int>(MOON_TYPE::DEAD);
	darkState_ = RandamDarkMove();
	pos_[i] = ResetPos();
	isMoon_[i] = false;
	
	speed_ = { MOVE_SPEED,MOVE_SPEED };
	drawSize_ = 1.0f;
	alpha_ = Fader::FADE_MAX;
	respawn_ = INTERVAL * SceneManager::DEFAULT_FPS;

	//���F���̏����ݒ�
	i = static_cast<int>(MOON_TYPE::GOAL);
	firstPos_[i] = { Application::SCREEN_SIZE_X / 2, static_cast<float>( - BlockBase::BLOCK_SIZE_Y * (GOAL_MOON_HEIGHT_OFFSET - level_->GetFieldSize().y))};
	pos_[i] = firstPos_[i];
	isMoon_[i] = false;
	preBlock_ = MOON_GOAL_PRE_BLOCK;
	scroll_ = 0;
	scrollMax_ = 0;
	scrollSpeed_ = MOON_SCROLL_SPEED;
}

void Moon6::Update()
{
	int height = level_->GetBlockHeight();

	if (height > DARK_MOON_TERM_HEIGHT) { DarkMoonUpdate(); }

	if (height > GOAL_MOON_TERM_HEIGHT) { GoalMoonUpdate(); }
}

void Moon6::Draw()
{
	DarkMoonDraw();

	GoalMoonDraw();
}

Moon6::DARK_MOVE Moon6::RandamDarkMove()
{
	constexpr int MOVE_TYES = 2;

	int i = rand() % MOVE_TYES;
	if (i == 0) {
		return DARK_MOVE::DIAGONAL;
	}
	else {
		return DARK_MOVE::DIAGONAL_RE;
	}
}

Vector2F Moon6::ResetPos()
{
	Vector2F pos;
	float posX = 0.0f;

	switch (darkState_)
	{
	case DARK_MOVE::DIAGONAL:
		posX = rand() % (Application::SCREEN_SIZE_X / DARK_SCREEN_DIVISOR); // ��ʂ̍��������_��
		break;

	case DARK_MOVE::DIAGONAL_RE:
		posX = Application::SCREEN_SIZE_X + (rand() % SIZE_X); // ��ʉE�O���烉���_��
		break;

	default:
		break;
	}

	// �������W��Ԃ��i������ɃI�t�Z�b�g�j
	return pos = { posX, -SIZE_Y * DARK_POS_Y_OFFSET };
}

Vector2F Moon6::ResetSpeed()
{
	float speedX = MOVE_SPEED + (rand() % 10);
	float speedY = MOVE_SPEED + (rand() % 10);
	Vector2F speed = { speedX, speedY };
	return speed;
}

void Moon6::DarkMoonUpdate()
{
	int i = static_cast<int>(MOON_TYPE::DEAD);
	auto& snd = SoundManager::GetInstance();

	switch (darkState_)
	{
		//�C���^�[�o��(�ړ���~)
	case DARK_MOVE::STOP:
		stopCnt_++;
		if (stopCnt_ > respawn_)
		{
			stopCnt_ = 0;
			downCnt_ = RANDAM_MOON_DOWN_MIN + (rand() % RANDAM_MOON_DOWN_MAX);
			darkState_ = RandamDarkMove();
			pos_[i] = ResetPos();
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC,static_cast<int>(SoundManager::GIMIC::DARK_MOON_RESPAWN));
		}
		break;

		//�΂߈ړ�����
	case DARK_MOVE::DIAGONAL:
		//�ړ�����
		pos_[i].x += speed_.x;
		pos_[i].y += speed_.x;
		//��ʊO�ɏo����
		if (pos_[i].x > Application::SCREEN_SIZE_X + SIZE_X || 
			pos_[i].y > Application::SCREEN_SIZE_Y + SIZE_Y * 2)
		{
			//�o���񐔂��܂�����ꍇ
			if(downCnt_ > 0)
			{
				darkState_ = RandamDarkMove();
				pos_[i] = ResetPos();
				speed_ = ResetSpeed();
				downCnt_--;
				snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::DARK_MOON_RESPAWN));
			}
			//0�ȉ��̏ꍇ
			else 
			{
				darkState_ = DARK_MOVE::STOP;
			}
		}
		break;

	case DARK_MOVE::DIAGONAL_RE:
		//�ړ�����
		pos_[i].x -= speed_.x;
		pos_[i].y += speed_.y;
		//��ʊO�ɏo����
		if (pos_[i].x < 0 ||
			pos_[i].y > Application::SCREEN_SIZE_Y + SIZE_Y * 2)
		{
			//�o���񐔂��܂�����ꍇ
			if (downCnt_ > 0)
			{
				darkState_ = RandamDarkMove();
				pos_[i] = ResetPos();
				speed_ = ResetSpeed();
				downCnt_--;
				snd.PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::DARK_MOON_RESPAWN));
			}
			//0�ȉ��̏ꍇ
			else
			{
				darkState_ = DARK_MOVE::STOP;
			}
		}
		break;

		//�Փˎ��̑傫���Ȃ鏈��
	case DARK_MOVE::FADE_BIG:
		drawSize_ += EXPANSION_SPEED;
		alpha_--;
		if (drawSize_ >= SIZE_MAX_RATE)
		{
			darkState_ = DARK_MOVE::STOP;
			alpha_ = Fader::FADE_MAX;
			drawSize_ = 1.0f;
			isMoon_[i] = false;
			pos_[i] = firstPos_[i];
			level_->PlayBGM();
		}
		break;

	default:
		break;
	}
}

void Moon6::GoalMoonUpdate(void)
{
	int i = static_cast<int>(MOON_TYPE::GOAL);

	//���W�ݒ�
	pos_[i] = firstPos_[i];

	//�V�F�C�N����
	pos_[i] = AsoUtility::SinShake(pos_[i].ToVector2(), AMPLITUDE, FREQUENCY).ToVector2F();

}


void Moon6::DarkMoonDraw()
{
	Vector2 cameraPos = level_->GetCameraPos().ToVector2();
	int i = static_cast<int>(MOON_TYPE::DEAD);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	DrawRotaGraph(pos_[i].x - cameraPos.x,
		pos_[i].y - cameraPos.y,
		drawSize_,		//�g��
		0.0f,			//��]
		images_[i],
		true,			//����
		false);			//���]
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Moon6::GoalMoonDraw(void)
{
	Vector2 cameraPos = level_->GetCameraPos().ToVector2();
	int i = static_cast<int>(MOON_TYPE::GOAL);
	DrawRotaGraph(pos_[i].x - cameraPos.x,
		pos_[i].y - cameraPos.y,
		1.0f,		//�g��
		0.0f,			//��]
		images_[i],
		true,			//����
		false);			//���]
}