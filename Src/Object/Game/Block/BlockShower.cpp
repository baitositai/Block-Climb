#include <DxLib.h>
#include <cmath>
#include "../../../Utility/AsoUtility.h"
#include "BlockShower.h"
#include "../../../Application.h"

BlockShower::BlockShower()
{
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			angle_[i][j] = {};
		}
	}
	step_ = 0.0f;
}

BlockShower::~BlockShower()
{
}

void BlockShower::Create()
{
	//�摜�ǂݍ���
	Load();

	//�ϐ�������
	Reset();
}

void BlockShower::Update()
{
	// ��������
	rotaCenterPos_.y += SHOWER_SPEED;

	for (int i = 0; i < MINO_HEIGHT; i++)
	{
		for (int j = 0; j < MINO_WIDTH; j++)
		{
			blockPos_[i][j].y += SHOWER_SPEED;

			// �~�O��
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
					1.0f,	//�g��
					angle,	//��]
					imgBlocks_[minoType_],
					true,	//����
					false);	//����
			}

			if (pos.y >= DELETE_LINE)
			{
				isDelete_ = true;
			}
		}
	}
}

void BlockShower::Reset()
{
	isDelete_ = false;

	//�~�m�̎�ނ����߂�
	minoType_ = rand() % static_cast<int>(MINO_TYPE::MAX);

	//�~�m���W�̏����ʒu
	minoPos_ = { static_cast<float>(rand() % (Application::SCREEN_SIZE_X - BLOCK_SIZE_X * 4)),
				-BlockBase::BLOCK_SIZE_Y * MINO_HEIGHT };

	//��ނ��Ƃɒ��S�ʒu��p�x��ݒ�
	InitMino();

	for (int i = 0; i < MINO_HEIGHT; i++)
	{
		for (int j = 0; j < MINO_WIDTH; j++)
		{
			//���a
			blockPos_[i][j] = minoPos_;
			blockPos_[i][j].x += BLOCK_SIZE_X * j;
			blockPos_[i][j].y += BLOCK_SIZE_Y * i;
		}
	}
}

void BlockShower::InitMino()
{
	MINO_TYPE mino = static_cast<MINO_TYPE>(minoType_);
	rotaCenterPos_ = { minoPos_.x + MINO_LOCAL_POS_X[minoType_],
						minoPos_.y + MINO_LOCAL_POS_Y[minoType_] };

	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			angle_[i][j] = ANGLE[minoType_][i][j];
		}
	}
}

Vector2F BlockShower::RotatePosition(Vector2F centerPos , float angle, Vector2F pos)
{

	//�@���S�����_�ɕ��s�ړ�����
	//�A���_���S�ɉ�]����
	//�B���S�����̍��W�֖߂�

	Vector2F ret;

	pos.x -= centerPos.x;
	pos.y -= centerPos.y;

	ret.x = pos.x * cos(angle) - pos.y * sin(angle);
	ret.y = pos.x * sin(angle) + pos.y * cos(angle);

	ret.x += centerPos.x;
	ret.y += centerPos.y;

	//�����ɉ�]�ϊ��������Ă�������
	return ret;//�f�t�H���g�͂��̂܂ܕԂ��Ă܂��B
	//��������������āA����̓_�𒆐S�ɉ�]���s���悤�ɂ��Ă��������B
}