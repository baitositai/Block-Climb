#pragma once
#include "../,,/../../../Manager/SceneManager.h"
#include "SideBase.h"

class Side5:public SideBase
{
public:

	//�T�C�h�摜�C���f�b�N�X
	static constexpr int SIDE_IMG_INDEX = 4;

	//���Ԑ���
	static constexpr int TIME_LIMIT = 300 * SceneManager::DEFAULT_FPS;

	//�m�[�}���t�H���g�T�C�Y
	static constexpr int NORMAL_FONT_SIZE = 28;

	//�f�[�^�t�H���g�T�C�Y
	static constexpr int DATA_FONT_SIZE = 32;

	// �������Ԃ̕��̍ő�l�i5�������j
	static constexpr int TIME_LIMIT_MAX_MINUTES = 5;

	//�l�p�`�̘g�̑���
	static constexpr int BOX_BORDER = 3;

	//X�����̊Ԋu
	static constexpr int INTERVAL_X = 5;

	//Y�����̊Ԋu
	static constexpr int INTERVAL_Y = 10;

	//��ڂ̃{�b�N�X��X�����]���iintervalX �~ �{���j
	static constexpr int BOX1_MARGIN_X_COUNT = 4;

	//��ڂ̃{�b�N�X��Y�ʒu
	static constexpr int BOX1_POS_Y = 150;

	//��ڂ̃{�b�N�X�̍���
	static constexpr int BOX1_HEIGHT = 110;

	//��ڂ̃{�b�N�X�̉������̗]�����v�i���E�j
	static constexpr int BOX1_WIDTH_MARGIN_COUNT = 8;

	//��ڂ̃{�b�N�X��Y�ʒu
	static constexpr int BOX2_POS_Y = 300;

	//��ڂ̃{�b�N�X�̍���
	static constexpr int BOX2_HEIGHT = 110;

	//�t�H���g�ݒ�
	void SetFont() override;

	//���Z�b�g
	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw(void) override;

private:
	int minitu_;
	int second_;

};

