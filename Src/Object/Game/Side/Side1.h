#pragma once
#include "SideBase.h"

class Side1:public SideBase
{
public:

	//�T�C�h�摜��ރC���f�b�N�X�@
	static constexpr int SIDE_IMG_INDEX = 0;

	//�E�{�b�N�X��X�����}�[�W��
	static constexpr int BOX_MARGIN_X = 5;

	//�E�{�b�N�X��Y�����}�[�W��
	static constexpr int BOX_MARGIN_Y = 10;

	//�E�{�b�N�X�̘g�̑���
	static constexpr int BOX_BORDER = 3;

	//�E�{�b�N�X�̕\���ʒu�iY���W�j
	static constexpr int BOX_POS_Y = 150;

	//�E�{�b�N�X�̍���
	static constexpr int BOX_HEIGHT = 120;

	//�E�{�b�N�X�̕������l�iX�����̃}�[�W�����v�j
	static constexpr int BOX_WIDTH_MARGIN_TOTAL = BOX_MARGIN_X * 16;

	//�E�{�b�N�X�̕\���ʒuX�̒����{��
	static constexpr int BOX_POS_X_OFFSET_RATE = 8;

	//�f�[�^�\���̃I�t�Z�b�g�{��
	static constexpr int DATA_POS_X_OFFSET_RATE = 2;

	//�R���X�g���N�^
	Side1();

	//�f�X�g���N�^
	~Side1();

	//���Z�b�g
	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw(void) override;
};

