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
	//テキスト関係の設定
	type_.resize(TEXT_TYPE);
	for (int i = 0; i < TEXT_TYPE; i++) {
		type_[i].isTexts_ = false;
		type_[i].isDisPlayingText_ = false;
		type_[i].index_ = 0;
	}
}

void RabbitTitle::Update()
{
	//時間計測
	time_ += SceneManager::GetInstance().GetDeltaTime();

	for (int i = 0; i < TEXT_TYPE; i++) {
		//条件時間に達したか確認
		if (time_ > ARRIVAL_TIME[i] &&
			!type_[i].isTexts_)
		{
			//テキストデータの格納
			textData_ = i;

			//テキスト表示
			isText_ = true;

			//処理実行の許可をする
			type_[i].isDisPlayingText_ = true;

			//表示済みにする
			type_[i].isTexts_ = true;

			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::TEXT));
		}
	}
	
	//一文字ずつ表示させる処理
	UpdateTextDisplayIndex();

	//テキスト非表示
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
	type_[0].text_ = "スペースを押すんだよ";
	type_[1].text_ = "ゲームしないの～？";
	type_[2].text_ = "テトリスとは少し違うのよコレ";
	type_[3].text_ = "ちなみに僕はこのゲームには出ないよ";
	type_[4].text_ = "この背景は時間ごとで変わるんだよ";
	type_[5].text_ = "何見てんだお前";
}
