#include <DxLib.h>
#include "../../../Application.h"
#include "Start4.h"

void Start4::SetImage()
{
	imgStart_ = LoadGraph((Application::PATH_IMAGE + "UI/StartMessage.png").c_str());
	//‰æ‘œ‚Ì‘å‚«‚³‚Ìİ’è
	size_ = { IMG_SIZE_X,IMG_SIZE_Y };
}
