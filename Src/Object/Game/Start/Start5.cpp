#include <DxLib.h>
#include "../../../Application.h"
#include "Start5.h"

void Start5::SetImage()
{
	imgStart_ = LoadGraph((Application::PATH_IMAGE + "UI/StartMessage5.png").c_str());

	//画像の大きさの設定
	size_ = { IMG_SIZE_X,IMG_SIZE_Y };
}
