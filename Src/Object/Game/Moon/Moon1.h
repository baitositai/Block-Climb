#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon1 : public Moon
{
public:

	//�R���X�g���N�^
	Moon1();

	//�f�X�g���N�^
	~Moon1();

	//���Z�b�g
	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

};

