#include <DxLib.h>
#include "../../../Application.h"
#include "Start4.h"

void Start4::SetImage()
{
	imgStart_ = LoadGraph((Application::PATH_IMAGE + "UI/StartMessage.png").c_str());
	//�摜�̑傫���̐ݒ�
	size_ = { IMG_SIZE_X,IMG_SIZE_Y };
}
