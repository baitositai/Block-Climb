#pragma once
#include "LevelManager.h"

class Blast;
class FireBall;
class RabbitMarason;

class Marason :public LevelManager
{
public:

	static constexpr int ADD_LINE = 8;								//�ǉ����C��

	static constexpr int FIELD_WIDTH = 16;                          // �t�B�[���h�̉��̃u���b�N��
	static constexpr int FIELD_HEIGHT = 20;                         // �t�B�[���h�̏c�̃u���b�N��
	static constexpr int GROUND_HEIGHT = 3;                         // �n�ʂ̏c�̃u���b�N��

	static constexpr int BUFF_SECOND = 15;							//�o�t�̕b��
	static constexpr int FIRE_SECOND = 15;							//�΂̋ʂ̗����b��

	static constexpr int PLAYER_OFFSET_BLOCK_Y = 2;                 // �v���C���[�̈ʒu�̃u���b�N���I�t�Z�b�g
	static constexpr int PLAYER_PIXEL_ADJUST_Y = 8;                 // �v���C���[�̏c�̔������s�N�Z����

	static constexpr int CAMERA_OFFSET_BLOCK_Y = 2;                 // �J�����̈ʒu�̃u���b�N���I�t�Z�b�g

	static constexpr int GOAL_OFFSET_X = 75;                        // �S�[���̉��ʒu�̒����l
	static constexpr int GOAL_POS_Y = 600;                          // �S�[���̏c�ʒu

	static constexpr int RABBIT_DRAW_OFFSET_X = 30;                  // �������摜�̉��ʒu�̒����l
	static constexpr int SPEECH_DRAW_OFFSET_X = 40;                  // �����o���摜�̊�ʒu�̉������l
	static constexpr int SPEECH_DRAW_OFFSET_Y = 5;                   // �����o���摜�̏c�ʒu�̔������l
	static constexpr int TEXT_DRAW_OFFSET_X = 70;                    // �e�L�X�g�摜�̊�ʒu�̉������l
	static constexpr int TEXT_DRAW_OFFSET_Y = 80;                    // �e�L�X�g�摜�̏c�ʒu�̒ǉ������l

	//�������̕ύX��
	static constexpr int CREATE_RULE_SIZE = 6;

	// �����������l�i�~���j
	static constexpr int CREATE_HEIGHT_THRESHOLDS[CREATE_RULE_SIZE] = {
		100, 80, 60, 40, 20, 0
	};

	// �Ή����鐶�����iCREATE_HEIGHT_THRESHOLDS �Ɠ������сj
	static constexpr int CREATE_COUNTS[CREATE_RULE_SIZE] = {
		15, 10, 7, 5, 4, 3
	};

	// ��莞�ԁi�b �~ FPS�j
	static constexpr int FIRE_INTERVAL_SECOND = 5;

	//�R���X�g���N�^
	Marason(void);

	//�f�X�g���N�^
	~Marason(void);

	//������
	void Init(GameScene* parent) override;

	//�X�V
	void Update(void) override;

	//�`��
	void Draw(void) override;

	//���
	void Release(void) override;

	//�p�����[�^�[�ݒ�
	void SetParam() override;

	//�I�u�W�F�N�g�̈ʒu����
	void ShiftGame() override;

	//�C�x���g�����̏���
	void GameEvent();

	//�΂̋ʂ̏���
	void FireBallUpdate();

	//�t�@�C�A�[�{�[������
	void CreateFireBall();

	//�΂̋ʂ̏o���J�E���g�̐ݒ�
	void SetTimeCount(int value);

	//�΂̋ʂ�Ԃ�
	FireBall* GetValidFireBall();

	//��������
	void BlastUpdate();

	//��ԕω��̃J�E���g����
	bool PlayerSpeedCount();

	//�v���C���[��ԕω��p�J�E���g�Z�b�g
	void SetParamCount(int value);

	//�E�T�M�̕`��
	void RabbitDraw();

private:

	//�C�x���g���C��
	int eventLine_;

	//�v���C���[��ԕω��p�J�E���g
	int paramCnt_;

	//�΂̋ʏo���p�J�E���g
	int fireCnt_;

	//�ύX����
	bool isChange_;

	//�C���X�^���X
	RabbitMarason* rabbit_;

	//����(�|�C���^)
	std::vector<Blast*> blasts_;

	//�΂̋�
	std::vector<FireBall*> fire_;
};

