#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Manager/SceneManager.h"
#include "RabbitText.h"

RabbitText::RabbitText()
{
    fontSize_ = 0;
    font_ = 0;
    imgRabbit_ = 0;
    imgSpeech_ = 0;
    isText_ = false;
    lastTime_ = 0;
    offCnt_ = 0;
    speed_ = 0;
    step_ = 0;
    textData_ = 0;
    type_.clear();
}

RabbitText::~RabbitText()
{
}

void RabbitText::Init()
{
    //�摜�ǂݍ���
    std::string path = Application::PATH_IMAGE + "Omuretu/";
    imgRabbit_ = LoadGraph((path + "�I�����c.png").c_str());
    imgSpeech_ = LoadGraph((path + "�����o��.png").c_str());

    //�ϐ�������
    Reset();

    //�t�H���g�ݒ�
    InitFont();

    //�e�L�X�g�ݒ�
    InitText();
}

void RabbitText::Reset()
{
    isText_ = false;
    offCnt_ = 0.0f;
}

void RabbitText::Release()
{
    DeleteFontToHandle(font_);
    DeleteGraph(imgSpeech_);
    DeleteGraph(imgRabbit_);
}

void RabbitText::InitFont()
{
    font_ = CreateFontToHandle("�ڂ������̃S�V�b�N", FONT_SIZE, FONT_THICK);
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

void RabbitText::UpdateTextDisplayIndex()
{
    if (type_[textData_].isDisPlayingText_ && 
        type_[textData_].index_ < type_[textData_].text_.size())
    {
        step_ += SceneManager::GetInstance().GetDeltaTime();
        if (step_ >= INTERVAL)
        {
            type_[textData_].index_ += 2;
            step_ = 0.0f;
        }
    }
    else
    {
        // �S�Ă̕������\�����ꂽ��t���O���I�t�ɂ���
        type_[textData_].isDisPlayingText_ = false;
    }
}