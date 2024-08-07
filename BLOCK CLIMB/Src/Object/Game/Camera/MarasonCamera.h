#pragma once
#include "Camera.h"

class MarasonCamera:public Camera
{
public:

	void CameraScrollMove() override;
	void CameraMoveRestriction() override;

private:

};

