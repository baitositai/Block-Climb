#include <DxLib.h>
#include "../../../Application.h"
#include "Start2.h"

void Start2::SetImage()
{
	imgStart_ = LoadGraph((Application::PATH_IMAGE + "UI/StartMessage2.png").c_str());

	//�摜�̑傫���̐ݒ�
	size_ = { IMG_SIZE_X,IMG_SIZE_Y };
}