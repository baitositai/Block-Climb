#pragma once
#include "BlockBase.h"


class Block1 :public BlockBase
{
public:

	//�R���X�g���N�^
	Block1();

	//�f�X�g���N�^
	~Block1();

	//���Z�b�g
	void Reset(void) override;

	//�X�e�[�W����
	void StageCreate(void) override;
};

