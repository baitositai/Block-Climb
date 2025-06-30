#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "GameClear.h"

GameClear::GameClear()
{
	imgClear_  = -1;
	pos_ = {};
}

GameClear::~GameClear()
{
}

void GameClear::Init()
{

	//�摜�ǂݍ���
	imgClear_ = LoadGraph((Application::PATH_IMAGE + "UI/ClearUI.png").c_str());
}

void GameClear::Update()
{
	//���W�̐ݒ�
	pos_.x = POS_X;
	pos_.y = POS_Y;

	//�㉺�h�炵�̏���
	pos_ = AsoUtility::SinShake(pos_, AMPLITUDE, FREQUENCY);

}

void GameClear::Draw()
{
	//�摜�̕`��
	DrawGraph(pos_.x, pos_.y, imgClear_, true);
}

void GameClear::Release()
{
	DeleteGraph(imgClear_);
}
