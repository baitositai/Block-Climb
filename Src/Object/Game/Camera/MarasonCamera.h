#pragma once
#include "Camera.h"

class MarasonCamera:public Camera
{
public:

	//�R���X�g���N�^
	MarasonCamera();

	//�f�X�g���N�^
	~MarasonCamera();

	//�J�����̃X�N���[������
	void CameraScrollMove() override;

	//�J�����̈ړ�����
	void CameraMoveRestriction() override;


};

