#pragma once
#include "SideBase.h"

class Side6 :public SideBase
{
public:

	//�T�C�h�摜�C���f�b�N�X
	static constexpr int SIDE_IMG_INDEX = 5;

	//X�����̊Ԋu
	static constexpr int INTERVAL_X = 5;

	//Y�����̊Ԋu
	static constexpr int INTERVAL_Y = 10;

	//�l�p�`�̘g�̑���
	static constexpr int BOX_BORDER = 3;

	//�{�b�N�X��X�����]���iintervalX �~ �{���j
	static constexpr int BOX_MARGIN_X_COUNT = 8;

	//�{�b�N�X��Y�ʒu
	static constexpr int BOX_POS_Y = 150;

	//�{�b�N�X�̍���
	static constexpr int BOX_HEIGHT = 120;

	//�{�b�N�X�̉������̗]�����v�i���E�j
	static constexpr int BOX_WIDTH_MARGIN_COUNT = 16;

	//�A�C�R���{�b�N�X��X�I�t�Z�b�g
	static constexpr int ICON_BOX_OFFSET_X = 64;

	//�A�C�R���{�b�N�X��Y�ʒu
	static constexpr int ICON_BOX_POS_Y = 150;

	//�A�C�R���{�b�N�X�̕�
	static constexpr int ICON_BOX_WIDTH = 128;

	//�A�C�R���{�b�N�X�̍���
	static constexpr int ICON_BOX_HEIGHT = 128;

	//���Z�b�g
	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw(void) override;

	//�����`��
	void HeightDraw();

	//�A�C�R���`��
	void IconDraw();
};

