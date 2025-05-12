#pragma once
#include <string>
#include "RabbitText.h"

class RabbitTitle : public RabbitText
{
public:

	//コンストラクタ
	RabbitTitle();

	//デストラクタ
	~RabbitTitle();

	//テキスト種類数
	static constexpr int TEXT_TYPE = 6;

	//到達時間
	static constexpr int ARRIVAL_TIME[TEXT_TYPE] = {10, 30, 50, 180, 300, 500};

	void Reset() override;
	void Update() override;
	void TextDraw(Vector2 pos) override;
	void InitText() override;

private:

	//カウント
	float time_;
	
	//テキストオフ
	void TextOff()override;

};

