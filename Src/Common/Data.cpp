#include <DxLib.h>      //DX���C�u�����̎g�p����
#include "../Application.h"
#include "Data.h"
#include "../Scene/MenuScene.h"

Data* Data::instance_ = nullptr;//�Y���ȁI�I

//�V���O���g����
void Data::CreateInstance(void)
{
	//�C���X�^���X��nullptr�Ȃ珉�������ꂽ�̂������������s��

	if (instance_ == nullptr)
	{
		instance_ = new Data();
	}
	//instance_->Init();
}

Data& Data::GetInstance(void)
{
	return*instance_;
}

void Data::Destory(void)
{
	delete instance_;
	instance_ = nullptr;
}


//�����o�[�֐�
Data::Data(void)
{
	Data_ = DEFAULT_DATA;
	marasonData_ = 0;
}

Data::~Data(void)
{

}

void Data::SetDeta(int pos)
{
	Data_ = pos;
}

int Data::GetDeta(void)
{
	return Data_;
}


//���x���f�[�^��ύX
void Data::ChangeLevelData(Data::LEVEL Data)
{
	type_ = Data;
}

//���x���f�[�^��Ԃ�
Data::LEVEL Data::GetStageData(void)
{
	return type_;
}

int Data::GetMarasonData()
{
	return marasonData_;
}

void Data::SetMarasonData(int value)
{
	marasonData_ = value;
}
