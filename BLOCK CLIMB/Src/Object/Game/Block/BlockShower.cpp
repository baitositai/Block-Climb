#include <DxLib.h>
#include <cmath>
#include "../../../Utility/AsoUtility.h"
#include "BlockShower.h"
#include "../../../Application.h"

BlockShower::BlockShower()
{
}

BlockShower::~BlockShower()
{
}

void BlockShower::Create()
{
	//画像読み込み
	Load();

	//変数初期化
	Reset();


}

void BlockShower::Update()
{
	// 落下処理
	rotaCenterPos_.y += SHOWER_SPEED;

	for (int i = 0; i < MINO_HEIGHT; i++)
	{
		for (int j = 0; j < MINO_WIDTH; j++)
		{
			blockPos_[i][j].y += SHOWER_SPEED;

			// 円軌道
			blockPos_[i][j] = RotatePosition(rotaCenterPos_, ROTATION_SPEED, blockPos_[i][j]);
			
		}
	}
}

void BlockShower::Draw()
{
	for (int i = 0; i < MINO_WIDTH; i++)
	{
		for (int j = 0; j < MINO_HEIGHT; j++)
		{
			float angle = 0;
			Vector2F pos;
			MINO_TYPE mino = static_cast<MINO_TYPE>(minoType_);

			pos.x = rotaCenterPos_.x - blockPos_[i][j].x;
			pos.y = rotaCenterPos_.y - blockPos_[i][j].y;

			angle = atan2f(pos.y, pos.x) + angle_[j][i];

			if (minoShapes_[minoType_][j][i] == 1)
			{
				DrawRotaGraph(blockPos_[j][i].x,
					blockPos_[j][i].y,
					1.0f,	//拡大
					angle,	//回転
					imgBlocks_[minoType_],
					true,	//分からん
					false);	//向き
			}

			if (pos.y >= Application::SCREEN_SIZE_Y + BLOCK_SIZE_X * 4)
			{
				isDelete_ = true;
			}
		}
	}
}

void BlockShower::Reset()
{
	isDelete_ = false;

	//ミノの種類を決める
	minoType_ = rand() % static_cast<int>(MINO_TYPE::MAX);

	//ミノ座標の初期位置
	minoPos_ = { static_cast<float>(rand() % (Application::SCREEN_SIZE_X - BLOCK_SIZE_X * 4)),
				-BlockBase::BLOCK_SIZE_Y * MINO_HEIGHT };

	//回転の中心座標を取得
	rotaCenterPos_ = GetRotationPos();

	for (int i = 0; i < MINO_HEIGHT; i++)
	{
		for (int j = 0; j < MINO_WIDTH; j++)
		{
			//半径
			blockPos_[i][j] = minoPos_;
			blockPos_[i][j].x += BLOCK_SIZE_X * j;
			blockPos_[i][j].y += BLOCK_SIZE_Y * i;
		}
	}
}

Vector2F BlockShower::GetRotationPos()
{
	MINO_TYPE mino = static_cast<MINO_TYPE>(minoType_);
	Vector2F pos = minoPos_;

	switch (mino)
	{
	case MINO_TYPE::I:
		pos.x += BLOCK_SIZE_X;
		pos.y += BLOCK_SIZE_Y * 1.5f;
		angle_[0][1] = -DX_PI_F / 7 + DX_PI_F;
		angle_[1][1] = DX_PI_F / 2;
		angle_[2][1] = DX_PI_F / 7;
		angle_[3][1] = DX_PI_F / 14;
		break;

	case MINO_TYPE::J:
		pos.x += BLOCK_SIZE_X * 1.5;
		pos.y += BLOCK_SIZE_Y;
		angle_[0][2] = DX_PI_F / 5.5- DX_PI_F / 2;
		angle_[1][2] = -DX_PI_F / 6.5;
		angle_[2][2] = DX_PI_F / 6.5;
		angle_[2][1] = DX_PI_F / 2;
		break;

	case MINO_TYPE::L:
		pos.x += BLOCK_SIZE_X * 1.5;
		pos.y += BLOCK_SIZE_Y;
		angle_[0][1] = 0;
		angle_[1][1] = 0;
		angle_[2][1] = DX_PI_F ;
		angle_[2][2] = DX_PI_F / 7 + DX_PI_F / 2;
		break;

	case MINO_TYPE::O:
		pos.x += BLOCK_SIZE_X * 1.5f;
		pos.y += BLOCK_SIZE_Y * 1.5f;
		angle_[1][1] = DX_PI_F / 4;
		angle_[1][2] = DX_PI_F / 4 + DX_PI_F / 2;
		angle_[2][1] = DX_PI_F / 4 - DX_PI_F / 2;
		angle_[2][2] = DX_PI_F / 4 - DX_PI_F;
		break;

	case MINO_TYPE::S:
		pos.x += BLOCK_SIZE_X;
		pos.y += BLOCK_SIZE_Y * 1.5f;
		angle_[1][1] = DX_PI_F;
		angle_[1][2] = 0;
		angle_[2][0] = -DX_PI_F / 5.5- DX_PI_F;
		angle_[2][1] = DX_PI_F / 7+ DX_PI_F/2;
		break;

	case MINO_TYPE::T:
		pos.x += BLOCK_SIZE_X;
		pos.y += BLOCK_SIZE_Y * 1.5f;
		angle_[1][1] = DX_PI_F;
		angle_[1][0] = DX_PI_F;
		angle_[2][2] = -DX_PI_F / 8 + DX_PI_F / 2;
		angle_[2][1] = DX_PI_F / 7 + DX_PI_F / 2;
		break;

	case MINO_TYPE::Z:
		pos.x += BLOCK_SIZE_X;
		pos.y += BLOCK_SIZE_Y * 1.5f;
		angle_[1][1] = DX_PI_F;
		angle_[1][0] = DX_PI_F;
		angle_[2][2] = -DX_PI_F / 7 + DX_PI_F/2;
		angle_[2][1] = DX_PI_F / 7 + DX_PI_F / 2;
		break;

	default:
		break;
	}

	return pos;
}

Vector2F BlockShower::RotatePosition(Vector2F centerPos , float angle, Vector2F pos)
{

	//①中心を原点に平行移動して
	//②原点中心に回転して
	//③中心を元の座標へ戻す

	Vector2F ret;

	pos.x -= centerPos.x;
	pos.y -= centerPos.y;

	ret.x = pos.x * cos(angle) - pos.y * sin(angle);
	ret.y = pos.x * sin(angle) + pos.y * cos(angle);

	ret.x += centerPos.x;
	ret.y += centerPos.y;

	//ここに回転変換を書いてください
	return ret;//デフォルトはそのまま返してます。
	//これを書き換えて、特定の点を中心に回転を行うようにしてください。
}