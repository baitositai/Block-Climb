#pragma once
#include <string>
#include "RabbitText.h"

class RabbitTitle : public RabbitText
{
public:

	//テキスト種類数
	static constexpr int TEXT_TYPE = 6;

	void Reset() override;
	void Update() override;
	void TextDraw(Vector2 pos) override;
	void UpdateTextDisplayIndex() override;
	void TextOff() override;
	void SetText();

private:

	//カウント
	float time_;

	//到達時間
	float arrivalTime_[TEXT_TYPE];

	//テキスト呼び出し値
	int textData_;

	//テキスト種類
	Text type_[TEXT_TYPE];

};

