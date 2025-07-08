#include <DxLib.h>
#include "../../../Application.h"
#include "Start3.h"

void Start3::SetImage()
{
	imgStart_ = LoadGraph((Application::PATH_IMAGE + "UI/StartMessage3.png").c_str());

	//‰æ‘œ‚Ì‘å‚«‚³‚Ìİ’è
	size_ = { IMG_SIZE_X,IMG_SIZE_Y };
}