#include "MarasonCamera.h"

MarasonCamera::MarasonCamera()
{
}

MarasonCamera::~MarasonCamera()
{
}

void MarasonCamera::CameraScrollMove()
{
	Camera::CameraScrollMove();
}

void MarasonCamera::CameraMoveRestriction()
{
	//�J�����̉����̒l�𓾂�
	float scrollDownMax = level_->GetFirstCameraPos().y;

	//�J�����̈ړ�����
	//���g
	if (pos_.x < 0)
	{
		pos_.x = 0;
	}
	//�E�g(�K�v�͂Ȃ�)
	if (pos_.x > Application::SCREEN_SIZE_X)
	{
		pos_.x = Application::SCREEN_SIZE_X;
	}
	//��g
	if (pos_.y < 0)
	{
		pos_.y = 0;
	}
	//���g
	if (pos_.y > scrollDownMax)
	{
		pos_.y = scrollDownMax;
	}
}
