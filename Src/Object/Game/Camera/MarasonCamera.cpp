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
	//カメラの下限の値を得る
	float scrollDownMax = level_->GetFirstCameraPos().y;

	//カメラの移動制限
	//左枠
	if (pos_.x < 0)
	{
		pos_.x = 0;
	}
	//右枠(必要はない)
	if (pos_.x > Application::SCREEN_SIZE_X)
	{
		pos_.x = Application::SCREEN_SIZE_X;
	}
	//上枠
	if (pos_.y < 0)
	{
		pos_.y = 0;
	}
	//下枠
	if (pos_.y > scrollDownMax)
	{
		pos_.y = scrollDownMax;
	}
}
