#include <DxLib.h>      //DXライブラリの使用する
#include "../Application.h"
#include "Data.h"
#include "../Scene/MenuScene.h"

Data* Data::instance_ = nullptr;//忘れるな！！

//シングルトン化
void Data::CreateInstance(void)
{
	//インスタンスがnullptrなら初期化されたのち生成処理を行う

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


//メンバー関数
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


//レベルデータを変更
void Data::ChangeLevelData(Data::LEVEL Data)
{
	type_ = Data;
}

//レベルデータを返す
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
