#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Utility/AsoUtility.h"
#include "../Level/LevelManager.h"
#include "Moon1.h"

Moon1::Moon1()
{
	level_ = nullptr;
}

Moon1::~Moon1()
{
}

void Moon1::Reset()
{	
	Moon::Reset();

	//���F�����̏������W
	int i = static_cast<int>(MOON_TYPE::GOAL);
	firstPos_[i] = level_->GetGoalPos().ToVector2F();
	pos_[i] = firstPos_[i];
	isMoon_[i] = false;
}

void Moon1::Update()
{
	int i = static_cast<int>(MOON_TYPE::GOAL);

	//���W�ݒ�
	pos_[i] = firstPos_[i];

	//�V�F�C�N����
	pos_[i] = AsoUtility::SinShake(pos_[i].ToVector2(), AMPLITUDE, FREQUENCY).ToVector2F();
}

void Moon1::Draw()
{
	Vector2 cameraPos = level_->GetCameraPos().ToVector2();
	int i = static_cast<int>(MOON_TYPE::GOAL);

	//�S�[���̕`��
	DrawRotaGraph(pos_[i].x - cameraPos.x,
		pos_[i].y - cameraPos.y,
		1.0f,	//�g��
		0.0f,	//��]
		images_[i],
		true,	//����
		false);	//����
}
