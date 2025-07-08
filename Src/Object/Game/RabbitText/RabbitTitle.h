#pragma once
#include <string>
#include "RabbitText.h"

class RabbitTitle : public RabbitText
{
public:

	//�R���X�g���N�^
	RabbitTitle();

	//�f�X�g���N�^
	~RabbitTitle();

	//�e�L�X�g��ސ�
	static constexpr int TEXT_TYPE = 6;

	//���B����
	static constexpr int ARRIVAL_TIME[TEXT_TYPE] = {10, 30, 50, 180, 300, 500};

	void Reset() override;
	void Update() override;
	void TextDraw(Vector2 pos) override;
	void InitText() override;

private:

	//�J�E���g
	float time_;
	
	//�e�L�X�g�I�t
	void TextOff()override;

};

