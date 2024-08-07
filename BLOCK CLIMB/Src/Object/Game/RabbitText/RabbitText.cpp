#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Manager/SceneManager.h"
#include "RabbitText.h"

RabbitText::RabbitText()
{
}

RabbitText::~RabbitText()
{
}

void RabbitText::Init()
{
    //画像読み込み
    imgRabbit_ = LoadGraph((Application::PATH_IMAGE + "Omuretu/オムレツ.png").c_str());
    imgSpeech_ = LoadGraph((Application::PATH_IMAGE + "Omuretu/吹き出し.png").c_str());

    Reset();
    SetFont();
    SetText();
}

void RabbitText::GameInit(LevelManager* parent)
{
}

void RabbitText::Reset()
{
    isText_ = false;
    offCnt_ = 0.0f;

}

void RabbitText::Update()
{
}

void RabbitText::Release()
{
    DeleteFontToHandle(font_);
}

void RabbitText::SetFont()
{
    fontSize_ = 32;
   /* font_ = CreateFontToHandle("ベストテンDOT", fontSize_, 3);*/
    font_ = CreateFontToHandle("ぼくたちのゴシック", fontSize_, 3);
}

void RabbitText::SetText()
{
}

void RabbitText::UpdateTextDisplayIndex()
{
}

void RabbitText::TextOff()
{
}

void RabbitText::RabbitDraw(Vector2 pos)
{
    if (isText_)
    {
        DrawRotaGraph(pos.x + RABBIT_SIZE_X / 2,
            pos.y + RABBIT_SIZE_Y / 2,
            1.0f,
            0.0f,
            imgRabbit_,
            true,
            false);
    }
}

void RabbitText::SpeechDraw(Vector2 pos)
{
    if (isText_)
    {
        DrawRotaGraph(pos.x + SPEECH_SIZE_X / 2,
            pos.y + SPEECH_SIZE_Y / 2,
            1.0f,
            0.0f,
            imgSpeech_,
            true,
            false);
    }
}

void RabbitText::TextDraw(Vector2 pos)
{
}

void RabbitText::SetTextData(int value)
{
}
