#pragma once
#include "Camera.h"

class MarasonCamera:public Camera
{
public:

	//コンストラクタ
	MarasonCamera();

	//デストラクタ
	~MarasonCamera();

	//カメラのスクロール処理
	void CameraScrollMove() override;

	//カメラの移動制限
	void CameraMoveRestriction() override;


};

