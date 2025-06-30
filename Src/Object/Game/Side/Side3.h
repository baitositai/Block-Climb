#pragma once
#include "SideBase.h"

class Side3:public SideBase
{
public:

	//�T�C�h�摜��ރC���f�b�N�X�@
	static constexpr int SIDE_IMG_INDEX = 2;

	//�m�[�}���t�H���g�T�C�Y
	static constexpr int NORMAL_FONT_SIZE = 28;

	//�f�[�^�t�H���g�T�C�Y
	static constexpr int DATA_FONT_SIZE = 48;

	//���ʒuY���W
	static constexpr int BOX_POS_Y = 150;

	// �{�b�N�X�̘g���̑���
	static constexpr int SIDE_BOX_BORDER = 3;

	// �{�b�N�X���̉��̗]��
	static constexpr int SIDE_BOX_INTERVAL_X = 5;

	// �{�b�N�X���̏c�̗]��
	static constexpr int SIDE_BOX_INTERVAL_Y = 10;

	// �T�C�h�{�b�N�X�̏c�T�C�Y
	static constexpr int SIDE_BOX_HEIGHT = 110;

	// �{�b�N�XX���W�����i�E�[����̗]���j
	static constexpr int SIDE_BOX_RIGHT_OFFSET_X = SIDE_BOX_INTERVAL_X * 4;

	// �{�b�N�X������
	static constexpr int SIDE_BOX_WIDTH_MARGIN = SIDE_BOX_INTERVAL_X * 8;

	//�R���X�g���N�^
	Side3();

	//�f�X�g���N�^
	~Side3();

	void SetFont() override;
	void Reset() override;
	void Draw(void) override;

};

