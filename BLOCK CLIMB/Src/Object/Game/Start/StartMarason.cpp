#include <DxLib.h>
#include "../../../Application.h"
#include "StartMarason.h"

void StartMarason::SetImage()
{
	imgStart_ = LoadGraph((Application::PATH_IMAGE + "UI/StartMessageM.png").c_str());

	//‰æ‘œ‚Ì‘å‚«‚³‚Ìİ’è
	size_ = { 1106,280 };
}
