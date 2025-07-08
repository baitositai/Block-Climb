#pragma once
#include "LevelManager.h"

class Moon;

class Level2 :public LevelManager
{
public:

	static constexpr float PLAYER_JUMP_BUFF = 1.2f;             // �v���C���[�̃W�����v�͂̃o�t�{��

	static constexpr int FIELD_WIDTH = 10;                         // �t�B�[���h�̉��̃u���b�N��
	static constexpr int FIELD_HEIGHT = 12;                        // �t�B�[���h�̏c�̃u���b�N��

	static constexpr int GROUND_WIDTH = 18;                        // �n�ʂ̉��̃u���b�N��
	static constexpr int GROUND_HEIGHT = 6;                        // �n�ʂ̏c�̃u���b�N��

	static constexpr int STAGE_EXTRA_HEIGHT = 3;                   // �X�e�[�W�̏c�����̒ǉ���

	static constexpr int PLAYER_OFFSET_X = 50;                     // �v���C���[�̏����ʒu�̉��̂���
	static constexpr int PLAYER_OFFSET_Y_BLOCK = 2;                // �v���C���[�̏����ʒu�̏c�̃u���b�N�ʒu
	static constexpr int PLAYER_PIXEL_ADJUST_Y = 8;                // �v���C���[�̏c�̔�����

	static constexpr int CAMERA_OFFSET_BLOCK_Y = 2;                // �J�����̏c�����̃u���b�N�I�t�Z�b�g

	static constexpr int GOAL_OFFSET_X = 75;                       // �S�[���̉������̃I�t�Z�b�g
	static constexpr int GOAL_POS_Y = 600;                         // �S�[���̏c�����̍��W

	//�R���X�g���N�^
	Level2(void);

	//�f�X�g���N�^
	~Level2(void);

	//�ǉ�������
	void AddInit()override;

	//�X�V
	void Update(void) override;

	//�`��
	void Draw(void) override;

	//���
	void Release(void) override;

	//�p�����[�^�[�̐ݒ�
	void SetParam() override;

	//���Ƃ̏Փ˔���
	void HitMoon();

	//����Ԃ�
	Moon* GetMoonInstans() override;

private:

	Moon* moon_;
};