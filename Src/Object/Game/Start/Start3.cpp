#include <DxLib.h>
#include "../../../Application.h"
#include "Start3.h"

void Start3::SetImage()
{
	imgStart_ = LoadGraph((Application::PATH_IMAGE + "UI/StartMessage3.png").c_str());

	//�摜�̑傫���̐ݒ�
	size_ = { IMG_SIZE_X,IMG_SIZE_Y };
}