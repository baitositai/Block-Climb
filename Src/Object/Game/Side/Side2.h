#pragma once
#include "../,,/../../../Manager/SceneManager.h"
#include "SideBase.h"

class Side2:public SideBase
{
public:

	//�T�C�h�摜��ރC���f�b�N�X�@
	static constexpr int SIDE_IMG_INDEX = 1;

	//�m�[�}���t�H���g�T�C�Y
	static constexpr int NORMAL_FONT_SIZE = 28;

	//�f�[�^�t�H���g�T�C�Y
	static constexpr int DATA_FONT_SIZE = 32;

	// �������Ԃ̕��̍ő�l�i3�������j
	static constexpr int TIME_LIMIT_MAX_MINUTES = 3;

	//���Ԑ���
	static constexpr int TIME_LIMIT = 180 * SceneManager::DEFAULT_FPS;

	// �{�b�N�X�̘g�̑���
	static constexpr int SIDE_BOX_BORDER = 3;

	// �{�b�N�X��X�����}�[�W��
	static constexpr int SIDE_BOX_INTERVAL_X = 5;

	// �{�b�N�X��Y�����}�[�W��
	static constexpr int SIDE_BOX_INTERVAL_Y = 10;

	// 1�ڂ̃{�b�N�X��Y���W
	static constexpr int BLOCK_COUNT_BOX_POS_Y = 150;

	// 2�ڂ̃{�b�N�X��Y���W�i�������ԁj
	static constexpr int TIME_LIMIT_BOX_POS_Y = 300;

	// �{�b�N�X�̍���
	static constexpr int SIDE_BOX_HEIGHT = 110;

	// �{�b�N�X�̉��������l�i�}�[�W���̔{���j
	static constexpr int SIDE_BOX_WIDTH_MARGIN = SIDE_BOX_INTERVAL_X * 8;

	// �{�b�N�XX���W�I�t�Z�b�g�{��
	static constexpr int SIDE_BOX_POS_X_OFFSET = SIDE_BOX_INTERVAL_X * 4;

	// �f�[�^�`�掞��X�I�t�Z�b�g�{��
	static constexpr int SIDE_DATA_OFFSET_X_RATE = 2;

	// �f�[�^�`�掞��Y�I�t�Z�b�g�{���i�t�H���g�{�}�[�W���j
	static constexpr int SIDE_DATA_OFFSET_Y_RATE = 2;

	//�R���X�g���N�^
	Side2();

	//�f�X�g���N�^
	~Side2();

	//�t�H���g�ݒ�
	void SetFont() override;

	//���Z�b�g
	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw(void) override;

private:

	int minute_;
	int second_;
};

