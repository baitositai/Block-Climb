#pragma once
#include "LevelManager.h"

class Moon;
class FireBall;

class Level5 :public LevelManager
{
public:

	static constexpr float PLAYER_JUMP_POW = 1.2f;					// �v���C���[�̃W�����v��

	static constexpr int FIELD_WIDTH = 10;                          // �t�B�[���h�̉��̃u���b�N��
	static constexpr int FIELD_HEIGHT = 12;                         // �t�B�[���h�̏c�̃u���b�N��

	static constexpr int GROUND_WIDTH = 18;                         // �n�ʂ̉��̃u���b�N��
	static constexpr int GROUND_HEIGHT = 5;                         // �n�ʂ̏c�̃u���b�N��

	static constexpr int STAGE_GROUND_EXTRA_Y = 3;                  // �X�e�[�W�̏c�T�C�Y�ɉ�����u���b�N��

	static constexpr int PLAYER_OFFSET_X = 50;                      // �v���C���[�̏����ʒu�̉������̒����l
	static constexpr int PLAYER_OFFSET_BLOCK_Y = 2;                 // �v���C���[�̏����ʒu�̏c�̃u���b�N���I�t�Z�b�g
	static constexpr int PLAYER_PIXEL_ADJUST_Y = 8;                 // �v���C���[�̏c�����̔������Ɏg���s�N�Z����

	static constexpr int CAMERA_OFFSET_BLOCK_Y = 2;                 // �J�����̏c�̃u���b�N���I�t�Z�b�g

	static constexpr int GOAL_OFFSET_X = 75;                        // �S�[���̉������̒����l
	static constexpr int GOAL_POS_Y = 600;                          // �S�[���̏c�����̈ʒu

	//�R���X�g���N�^
	Level5();

	//�f�X�g���N�^
	~Level5();

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

	//���̓����蔻��
	void HitMoon();

	//�΂̋ʂ̍X�V
	void FireBallUpdate();

	//�΂̋ʐ���
	void CreateFireBall();

	//�΂̋ʂ�Ԃ�
	FireBall* GetValidFireBall();

	//����Ԃ�
	Moon* GetMoonInstans() override;

private:

	int fireCnt_;

	Moon* moon_;

	//�΂̋�
	std::vector<FireBall*> fire_;
};