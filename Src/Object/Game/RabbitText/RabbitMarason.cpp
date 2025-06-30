#include <DxLib.h>
#include "RabbitMarason.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"
#include "../Level/LevelManager.h"

RabbitMarason::RabbitMarason()
{
	time_ = 0.0f;
	for (int i = 0; i < MARASON_TEXTS; i++) { arrivalLine_[i] = 0; }
	level_ = nullptr;
}

RabbitMarason::~RabbitMarason()
{
}

void RabbitMarason::Init(LevelManager* parent)
{
	//�e�C���X�^���X���󂯎��
	level_ = parent;

	//������
	RabbitText::Init();
}

void RabbitMarason::Reset()
{
	RabbitText::Reset();
	pos_ = { 0,0 };
	textData_ = 0;

	for (int i = 0; i < MARASON_TEXTS; i++) {
		arrivalLine_[i] = ARRIVAL_LINE[i];
	}
	//�z��T�C�Y��ݒ�
	type_.resize(TEXT_TYPES);
	for (int i = 0; i < type_.size(); i++) {
		type_[i].isTexts_ = false;
		type_[i].isDisPlayingText_ = false;
		type_[i].index_ = 0;
	}
}

void RabbitMarason::Update()
{
	//���Ԍv��
	time_ += SceneManager::GetInstance().GetDeltaTime();

	//�������ƂɃZ���t��b������
	for (int i = 0; i < MARASON_TEXTS; i++) {
		//�������ԂɒB�������m�F
		if (level_->GetBlockHeight() >= arrivalLine_[i] &&
			!type_[i].isTexts_)
		{
			//�e�L�X�g�֌W�̐ݒ�
			SetTextData(i);
			//���ʉ��𗬂�
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::TEXT));
		}
	}

	//�ꕶ�����\�������鏈��
	UpdateTextDisplayIndex();

	//�e�L�X�g���\��
	if (isText_) { TextOff(); }
}

void RabbitMarason::TextOff()
{
	if (type_[textData_].isTexts_ && !type_[textData_].isDisPlayingText_)
	{
		offCnt_ += SceneManager::GetInstance().GetDeltaTime();
		if (offCnt_ > TEXT_OFF_CNT)
		{
			isText_ = false;
			offCnt_ = 0.0f;

			if (textData_ >= MARASON_TEXTS)
			{
				type_[textData_].isTexts_ = false;
			}
		}
	}
}

void RabbitMarason::TextDraw(Vector2 pos)
{
	if (isText_) {
		DrawStringToHandle(pos.x,
			pos.y,
			type_[textData_].text_.substr(0, type_[textData_].index_).c_str(),
			0x000000,
			font_);
	}
}

void RabbitMarason::InitText()
{
	//�������Ƃɘb���Z���t
	//����1m
	type_[0].text_ = "�������`����΂낤�I�I";
	//����20m
	type_[1].text_ = "�܂��܂����ꂩ�炾�]";
	//����46m
	type_[2].text_ = "�I��肪�Ȃ����Ďc�������";
	//����60m
	type_[3].text_ = "������������������";
	//����82m
	type_[4].text_ = "�����܂ŗ������M�l��";
	//����102m
	type_[5].text_ = "�R���˔j�����˂�";
	//����115m
	type_[6].text_ = "�ւ��I";
	//����130m
	type_[7].text_ = "��`�������ق�Ƃ�����";
	//����150m
	type_[8].text_ = "�Z���t�l����̂߂�ǂ��Ȃ��Ă���";
	//����175m
	type_[9].text_ = "���i�����Ă�";
	//����199m
	type_[10].text_ = "���΂炭�x�e����₷";
	//����300m
	type_[11].text_ = "�܂����Ă񂩂�";
	//����500m
	type_[12].text_ = "�����l�Ԃ���˂���";

	//�C�x���g���ƂŘb���Z���t
	//���̃X�s�[�h�A�b�v
	type_[13].text_ = "���킧";
	//���̃X�s�[�h�_�E��
	type_[14].text_ = "�ݑ���Y��";
	//�΂̋�
	type_[15].text_ = "�e���󂩂�΂̋ʂ�";
	//����
	type_[16].text_ = "�A�u�i�[�C";
	//�u���b�N�̃X�s�[�h�A�b�v
	type_[17].text_ = "�N�͑���邩��";
}

void RabbitMarason::SetTextData(int value)
{
	//�e�L�X�g�f�[�^�̊i�[
	textData_ = value;

	//�e�L�X�g�\��
	isText_ = true;

	//�������s�̋�������
	type_[textData_].isDisPlayingText_ = true;

	//�\���ς݂ɂ���
	type_[textData_].isTexts_ = true;
}
