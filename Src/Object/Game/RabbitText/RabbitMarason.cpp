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
	//親インスタンスを受け取る
	level_ = parent;

	//初期化
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
	//配列サイズを設定
	type_.resize(TEXT_TYPES);
	for (int i = 0; i < type_.size(); i++) {
		type_[i].isTexts_ = false;
		type_[i].isDisPlayingText_ = false;
		type_[i].index_ = 0;
	}
}

void RabbitMarason::Update()
{
	//時間計測
	time_ += SceneManager::GetInstance().GetDeltaTime();

	//高さごとにセリフを話す処理
	for (int i = 0; i < MARASON_TEXTS; i++) {
		//条件時間に達したか確認
		if (level_->GetBlockHeight() >= arrivalLine_[i] &&
			!type_[i].isTexts_)
		{
			//テキスト関係の設定
			SetTextData(i);
			//効果音を流す
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::TEXT));
		}
	}

	//一文字ずつ表示させる処理
	UpdateTextDisplayIndex();

	//テキストを非表示
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
	//高さごとに話すセリフ
	//高さ1m
	type_[0].text_ = "よっしゃ～がんばろう！！";
	//高さ20m
	type_[1].text_ = "まだまだこれからだゾ";
	//高さ46m
	type_[2].text_ = "終わりがないって残酷だよね";
	//高さ60m
	type_[3].text_ = "すごいぞぉ高いぞぉ";
	//高さ82m
	type_[4].text_ = "ここまで来たか貴様も";
	//高さ102m
	type_[5].text_ = "３桁突破したねぇ";
	//高さ115m
	type_[6].text_ = "へっ！";
	//高さ130m
	type_[7].text_ = "わ～すごいほんとすごい";
	//高さ150m
	type_[8].text_ = "セリフ考えるのめんどくなってきた";
	//高さ175m
	type_[9].text_ = "寿司くいてぇ";
	//高さ199m
	type_[10].text_ = "しばらく休憩入りやす";
	//高さ300m
	type_[11].text_ = "まだしてんかい";
	//高さ500m
	type_[12].text_ = "もう人間じゃねえよ";

	//イベントごとで話すセリフ
	//足のスピードアップ
	type_[13].text_ = "うわぉ";
	//足のスピードダウン
	type_[14].text_ = "鈍足野郎が";
	//火の玉
	type_[15].text_ = "親方空から火の玉が";
	//爆発
	type_[16].text_ = "アブナーイ";
	//ブロックのスピードアップ
	type_[17].text_ = "君は操れるかな";
}

void RabbitMarason::SetTextData(int value)
{
	//テキストデータの格納
	textData_ = value;

	//テキスト表示
	isText_ = true;

	//処理実行の許可をする
	type_[textData_].isDisPlayingText_ = true;

	//表示済みにする
	type_[textData_].isTexts_ = true;
}
