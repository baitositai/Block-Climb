#include <DxLib.h>
#include "Moon.h"
#include "../../../Application.h"
#include "../level/LevelManager.h"

Moon::Moon()
{
	for (int i = 0; i < static_cast<int>(MOON_TYPE::MAX); i++)
	{
		images_[i] = -1; 
		isMoon_[i] = false;
		pos_[i] = {};
		firstPos_[i] = {};
	}
	drawSize_ = 0.0f;
	darkState_ = DARK_MOVE::STOP;
	size_ = {};
	level_ = nullptr;
}

Moon::~Moon()
{
}

void Moon::Init(LevelManager* parent)
{
	level_ = parent;
	Load();
	Reset();
}

void Moon::Reset()
{
	//ëÂÇ´Ç≥ÇÃê›íË
	size_ = { SIZE_X, SIZE_Y };
}

void Moon::Update()
{
	
}

void Moon::Draw()
{
	for (int i = 0; i < static_cast<int>(MOON_TYPE::MAX); i++)
	{
		DrawRotaGraph(pos_[i].x,
			pos_[i].y,
			1.0f,
			0.0f,
			images_[i],
			true,
			false);
	}
}

void Moon::Release()
{
	for (int i = 0; i < static_cast<int>(MOON_TYPE::MAX); i++) { DeleteGraph(images_[i]); }
}

void Moon::Load()
{
	images_[static_cast<int>(MOON_TYPE::GOAL)] = LoadGraph((Application::PATH_IMAGE + "Moon/Goal.png").c_str());
	images_[static_cast<int>(MOON_TYPE::CHANGE)] = LoadGraph((Application::PATH_IMAGE + "Moon/Change.png").c_str());
	images_[static_cast<int>(MOON_TYPE::CREATE)] = LoadGraph((Application::PATH_IMAGE + "Moon/Create.png").c_str());
	images_[static_cast<int>(MOON_TYPE::DEAD)] = LoadGraph((Application::PATH_IMAGE + "Moon/Dark.png").c_str());
}

void Moon::SetIsMoon(MOON_TYPE type, bool value)
{
	isMoon_[static_cast<int>(type)] = value;
}

void Moon::SetDarkMove(DARK_MOVE move)
{
	darkState_ = move;
}

bool Moon::IsMoon(MOON_TYPE type)
{
	return isMoon_[static_cast<int>(type)];
}

void Moon::SetPos(MOON_TYPE type, Vector2F pos)
{
	pos_[static_cast<int>(type)].x += pos.x;
	pos_[static_cast<int>(type)].y += pos.y;
}

void Moon::SetFirstPos(MOON_TYPE type, Vector2F pos)
{
	firstPos_[static_cast<int>(type)].x += pos.x;
	firstPos_[static_cast<int>(type)].y += pos.y;
}

Vector2F Moon::GetPos(MOON_TYPE type)
{
	return pos_[static_cast<int>(type)];
}

Vector2 Moon::GetSize()
{
	return size_;
}

Moon::DARK_MOVE Moon::GetDarkMove()
{
	return darkState_;
}
