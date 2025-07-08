#pragma once
#include "LevelManager.h"


class Level4:public LevelManager
{
public:

	static constexpr int FIELD_WIDTH = 16;                          // �t�B�[���h�̉��̃u���b�N��
	static constexpr int FIELD_HEIGHT = 60;                         // �t�B�[���h�̏c�̃u���b�N��

	static constexpr int GROUND_HEIGHT = 3;                         // �n�ʂ̏c�̃u���b�N��

	static constexpr int PLAYER_OFFSET_BLOCK_Y = 2;                 // �v���C���[�̏����ʒu�̏c�̃u���b�N���I�t�Z�b�g
	static constexpr int PLAYER_PIXEL_ADJUST_Y = 8;                 // �v���C���[�̏c�̔������Ɏg���s�N�Z����

	static constexpr int CAMERA_OFFSET_BLOCK_Y = 2;                 // �J�����̏����ʒu�̏c�̃u���b�N���I�t�Z�b�g

	static constexpr int GOAL_OFFSET_X = 75;                        // �S�[���̉��̈ʒu�̒����l
	static constexpr int GOAL_POS_Y = 300;                          // �S�[���̏c�̈ʒu

	//�R���X�g���N�^
	Level4();

	//�f�X�g���N�^
	~Level4();

	//�ǉ�������
	void AddInit()override;

	//�X�V
	void Update() override;
	
	//�`��
	void Draw() override;
	
	//���
	void Release() override;

	//�p�����[�^�[�̐ݒ�
	void SetParam() override;

	//�΂̋ʂƂ̏Փ˔���
	void FireBallCollision();
};

