#include <DxLib.h>
#include "../../../Application.h"
#include "Start2.h"

void Start2::SetImage()
{
	imgStart_ = LoadGraph((Application::PATH_IMAGE + "UI/StartMessage2.png").c_str());

	//‰æ‘œ‚Ì‘å‚«‚³‚Ìİ’è
	size_ = { 816,280 };
}