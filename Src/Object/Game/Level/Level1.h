#pragma once
#include "LevelManager.h"


class Level1:public LevelManager
{
public:

	static constexpr int FIELD_WIDTH = 16;                          // �t�B�[���h�̉����i�u���b�N���j
	static constexpr int FIELD_HEIGHT = 30;                         // �t�B�[���h�̏c���i�u���b�N���j
	static constexpr int GROUND_HEIGHT = 3;                         // �n�ʂ̏c���i�u���b�N���j
	static constexpr int PLAYER_START_OFFSET_Y = 2;                 // �v���C���[�����ʒu��Y���␳�i�����牽�u���b�N�ځj
	static constexpr int PLAYER_PIXEL_OFFSET_Y = 8;                 // �v���C���[�����ʒu�̔������i�s�N�Z���j
	static constexpr int CAMERA_OFFSET_Y_BLOCKS = 2;                // �J����Y���I�t�Z�b�g�i�u���b�N�P�ʁj
	static constexpr int GOAL_OFFSET_X = 75;                        // �S�[����X���W�␳�i��ʒ�������̂���j
	static constexpr int GOAL_POS_Y = 150;                          // �S�[����Y���W
	static constexpr int DRAW_CENTER_BLOCK_OFFSET_X = 1;            // �`�撆�S��X�␳�i1�u���b�N���E�ɂ��炷�j

	//�R���X�g���N�^
	Level1(void);

	//�f�X�g���N�^
	~Level1(void);

	//�ǉ�������
	void AddInit()override;

	//�X�V
	void Update(void) override;

	//�`��
	void Draw(void) override;

	//����@
	void Release(void) override;

	//�p�����[�^�[�̐ݒ�
	void SetParam() override;
};

