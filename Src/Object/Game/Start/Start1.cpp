#include <DxLib.h>
#include "../../../Application.h"
#include "Start1.h"

void Start1::SetImage()
{
	imgStart_ = LoadGraph((Application::PATH_IMAGE + "UI/StartMessage.png").c_str());

	//�摜�̑傫���̐ݒ�
	size_ = { IMG_SIZE_X,IMG_SIZE_Y };
}
