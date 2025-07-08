#include <DxLib.h>
#include "../../../Application.h"
#include "../Level/LevelManager.h"
#include "Event.h"

Event::Event()
{
	eventState_ = EVENT::NONE;
	efectAnimSpeed_ = 0.0f;
	efectPos_ = { 0,0 };
	efeState_ = EFECT::NONE;
	for (int i = 0; i < EFECT_TYPE; i++)
	{
		efect_[i] = 0;
	}
	for (int i = 0; i < EVENT_TYPE; i++)
	{
		icon_[i] = 0;
	}
}

Event::~Event()
{
}

void Event::Init(LevelManager* parent)
{
	level_ = parent;
	Load();
	Reset();
}

void Event::Update()
{
	switch (eventState_)
	{
	case EVENT::NONE:
		efeState_ = EFECT::NONE;
		size_ = 1.0f;
		break;

	case EVENT::SPEED_UP:
		efeState_ = EFECT::SPEED_UP;
		break;

	case EVENT::SPEED_DOWN:
		efeState_ = EFECT::SPEED_DOWN;
		break;

	default:
		break;
	}

	if (efeState_ != EFECT::NONE)
	{		
		if (size_ < EFFECT_RATE_MIN || size_ >= EFFECT_RATE_MAX)
		{
			efectAnimSpeed_ *= -1;
		}
		size_ += efectAnimSpeed_;
	}

}

void Event::Draw()
{
}

void Event::Release()
{
	for (int i = 0; i < EFECT_TYPE; i++)
	{
		DeleteGraph(efect_[i]);
	}
	for (int i=0; i< EVENT_TYPE; i++)
	{
		DeleteGraph(icon_[i]);
	}
}

void Event::Reset()
{
	eventState_ = EVENT::NONE;
	efectAnimSpeed_ = EFECT_ANIM_SPEED;
	efectPos_ = { 0,0 };
	efeState_ = EFECT::NONE;
}

void Event::Load()
{
	icon_[static_cast<int>(EVENT::BLAST_LINE)] = LoadGraph((Application::PATH_IMAGE + "Icon/IconBlast.png").c_str());
	icon_[static_cast<int>(EVENT::FIRE_BALL)] = LoadGraph((Application::PATH_IMAGE + "Icon/IconFireBall.png").c_str());
	icon_[static_cast<int>(EVENT::SPEED_UP)] = LoadGraph((Application::PATH_IMAGE + "Icon/IconSpeedUp.png").c_str());
	icon_[static_cast<int>(EVENT::SPEED_DOWN)] = LoadGraph((Application::PATH_IMAGE + "Icon/IconSpeedDown.png").c_str());
	icon_[static_cast<int>(EVENT::BLOCK_SPEED_UP)] = LoadGraph((Application::PATH_IMAGE + "Icon/BlockSpeedUp.png").c_str());

	efect_[static_cast<int>(EFECT::SPEED_UP)] = LoadGraph((Application::PATH_IMAGE + "Efect/UpEfect.png").c_str());
	efect_[static_cast<int>(EFECT::SPEED_DOWN)] = LoadGraph((Application::PATH_IMAGE + "Efect/DownEfect.png").c_str());
}

void Event::IconDraw(Vector2 pos)
{
	if (eventState_ != EVENT::NONE)
	{
		DrawGraph(pos.x, pos.y, icon_[static_cast<int>(eventState_)], true);
	}
}

void Event::EfectDraw()
{
	if (efeState_ != EFECT::NONE)
	{
		Vector2 cameraPos = level_->GetCameraPos().ToVector2();
		DrawRotaGraph(efectPos_.x,
			efectPos_.y - cameraPos.y,
			size_,
			0.0f,
			efect_[static_cast<int>(efeState_)],
			true,
			false);
	}
}

void Event::EventOccurs()
{
	int cnt = rand() % FREQUENCY;
	int speedUpFrequency = SPEED_DOWN_FREQUENCY + SPEED_UP_FREQUENCY;
	int blastFrequency = speedUpFrequency + BLAST_FREQUENCY;
	int fireBallFrequency = blastFrequency + FIRE_BALL_FREQUENCY;
	int blockFrequency = fireBallFrequency + BLOCK_SPEED_UP_FREQUENCY;

	if (cnt < SPEED_DOWN_FREQUENCY) { eventState_ = EVENT::SPEED_DOWN; }
	else if (cnt < speedUpFrequency) { eventState_ = EVENT::SPEED_UP; }
	else if (cnt < blastFrequency) { eventState_ = EVENT::BLAST_LINE; }
	else if (cnt < fireBallFrequency) { eventState_ = EVENT::FIRE_BALL; }
	else if (cnt < blockFrequency) { eventState_ = EVENT::BLOCK_SPEED_UP; }
}

void Event::SetEvent(EVENT value)
{
	eventState_ = value;
}

void Event::SetEfectPos(Vector2 pos)
{
	efectPos_ = pos;
}

Event::EVENT Event::GetEvent()
{
	return eventState_;
}
