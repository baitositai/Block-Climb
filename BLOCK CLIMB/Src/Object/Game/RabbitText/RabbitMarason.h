#pragma once
#include "RabbitText.h"

class RabbitMarason : public RabbitText
{
public:

	//テキスト総種類数
	static constexpr int HEIGHT_TEXT = 13;

	//テキスト総種類数
	static constexpr int EVENT_TEXT = 5;

	//テキスト総種類数
	static constexpr int TEXT_TYPE = HEIGHT_TEXT + EVENT_TEXT;

	void GameInit(LevelManager* parent) override;
	void Reset() override;
	void Update() override;
	void TextDraw(Vector2 pos) override;
	void UpdateTextDisplayIndex() override;
	void TextOff() override;
	void SetText();

	//テキスト表示の設定
	void SetTextData(int value) override;

private:

	//カウント
	float time_;

	//到達ライン
	int arrivalLine_[HEIGHT_TEXT];

	//テキスト呼び出し値
	int textData_;

	//テキスト種類
	Text type_[TEXT_TYPE];
};