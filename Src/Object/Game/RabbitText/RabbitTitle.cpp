#include <DxLib.h>
#include "RabbitTitle.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"

RabbitTitle::RabbitTitle()
{
	time_ = 0.0f;
	textData_ = 0;
}

RabbitTitle::~RabbitTitle()
{
}

void RabbitTitle::Reset()
{
	RabbitText::Reset();
	pos_ = { 0,0 };
	textData_ = 0;
	//�e�L�X�g�֌W�̐ݒ�
	type_.resize(TEXT_TYPE);
	for (int i = 0; i < TEXT_TYPE; i++) {
		type_[i].isTexts_ = false;
		type_[i].isDisPlayingText_ = false;
		type_[i].index_ = 0;
	}
}

void RabbitTitle::Update()
{
	//���Ԍv��
	time_ += SceneManager::GetInstance().GetDeltaTime();

	for (int i = 0; i < TEXT_TYPE; i++) {
		//�������ԂɒB�������m�F
		if (time_ > ARRIVAL_TIME[i] &&
			!type_[i].isTexts_)
		{
			//�e�L�X�g�f�[�^�̊i�[
			textData_ = i;

			//�e�L�X�g�\��
			isText_ = true;

			//�������s�̋�������
			type_[i].isDisPlayingText_ = true;

			//�\���ς݂ɂ���
			type_[i].isTexts_ = true;

			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::TEXT));
		}
	}
	
	//�ꕶ�����\�������鏈��
	UpdateTextDisplayIndex();

	//�e�L�X�g��\��
	if (isText_) { TextOff(); }
}

void RabbitTitle::TextOff()
{
	if (type_[textData_].isTexts_ && !type_[textData_].isDisPlayingText_)
	{
		offCnt_ += SceneManager::GetInstance().GetDeltaTime();
		if (offCnt_ > TEXT_OFF_CNT)
		{
			isText_ = false;
			offCnt_ = 0.0f;
		}
	}
}

void RabbitTitle::TextDraw(Vector2 pos)
{
	if (isText_) {
		DrawStringToHandle(pos.x,
			pos.y,
			type_[textData_].text_.substr(0, type_[textData_].index_).c_str(),
			0x000000,
			font_);
	}
}

void RabbitTitle::InitText()
{
	type_[0].text_ = "�X�y�[�X�������񂾂�";
	type_[1].text_ = "�Q�[�����Ȃ��́`�H";
	type_[2].text_ = "�e�g���X�Ƃ͏����Ⴄ�̂�R��";
	type_[3].text_ = "���Ȃ݂ɖl�͂��̃Q�[���ɂ͏o�Ȃ���";
	type_[4].text_ = "���̔w�i�͎��Ԃ��Ƃŕς��񂾂�";
	type_[5].text_ = "�����Ă񂾂��O";
}
