#pragma once
#include "SideBase.h"

class Side4:public SideBase
{
public:
	//�u���b�N���\���G���A�̉������̗]��
	static constexpr int INTERVAL_X = 5;

	//�u���b�N���\���G���A�̏c�����̗]��
	static constexpr int INTERVAL_Y = 10;

	//�u���b�N���\���G���A�̘g�̑���
	static constexpr int BOX_BORDER = 3;

	//�u���b�N���\���G���A�̍���
	static constexpr int BOX_HEIGHT = 120;

	//�u���b�N���\���G���A�̈ʒuY
	static constexpr int BOX_POS_Y = 150;

	//�u���b�N���\���G���A�̉������̗]���̌��i�E�j
	static constexpr int BOX_MARGIN_X_COUNT = 8;

	//�u���b�N���\���G���A�̉������̗]���̌��i�������v�j
	static constexpr int BOX_WIDTH_MARGIN_COUNT = 16;

	//�T�C�h�摜��ރC���f�b�N�X�@
	static constexpr int SIDE_IMG_INDEX = 3;

	//���Z�b�g
	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw(void) override;

private:
};

