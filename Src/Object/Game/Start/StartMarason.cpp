#include <DxLib.h>
#include "../../../Application.h"
#include "StartMarason.h"

void StartMarason::SetImage()
{
	imgStart_ = LoadGraph((Application::PATH_IMAGE + "UI/StartMessageM.png").c_str());

	//�摜�̑傫���̐ݒ�
	size_ = { IMG_SIZE_X,IMG_SIZE_Y };
}
