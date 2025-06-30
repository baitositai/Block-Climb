#pragma once
#include "LevelManager.h"
#include "../../../Manager/SceneManager.h"

class Blast;
class FireBall;

class Level6 :public LevelManager
{
public:

	static constexpr int DEBUFF_LINE = 40;							//�f�o�t���C���̍���

	static constexpr int FIELD_WIDTH = 16;                          // �t�B�[���h�̉��̃u���b�N��
	static constexpr int FIELD_HEIGHT = 20;                         // �t�B�[���h�̏c�̃u���b�N��

	static constexpr int GROUND_HEIGHT = 3;                         // �n�ʂ̏c�̃u���b�N��

	static constexpr int PLAYER_OFFSET_BLOCK_Y = 2;                 // �v���C���[�̏����ʒu�̏c�̃u���b�N���I�t�Z�b�g
	static constexpr int PLAYER_PIXEL_ADJUST_Y = 8;                 // �v���C���[�̏c�����̔������Ɏg���s�N�Z����

	static constexpr int CAMERA_OFFSET_BLOCK_Y = 2;                 // �J�����̏c�̃u���b�N���I�t�Z�b�g

	static constexpr int GOAL_OFFSET_X = 75;                        // �S�[���̉������̒����l
	static constexpr int GOAL_POS_Y = 600;                          // �S�[���̏c�����̈ʒu

	static constexpr int ADD_LINE = 8;								//�ǉ����C��

	static constexpr int DEFAULT_CREATE_FIRE_CNT = 10 * SceneManager::DEFAULT_FPS;//�����̃C���^�[�o��
	static constexpr int CREATE_INTERVAL = 1 * SceneManager::DEFAULT_FPS;//�����̃C���^�[�o��
	static constexpr int CREATE_RAND_RANGE = 5 * SceneManager::DEFAULT_FPS;//�����̃C���^�[�o��

	static constexpr int EVENT_CHANGE = 6;							//�C�x���g�̏�ԕω��J�E���g
	static constexpr int FIRE_CHANGE = 7;							//�΂̋ʂ̏�ԕω��J�E���g

	static constexpr int HEIGHT_THRESHOLDS[EVENT_CHANGE] = { 70, 60, 50, 30, 20, 10 };  // ������臒l

	static constexpr int CNT_VALUES[FIRE_CHANGE] = { 20, 15, 10, 8, 5, 4, 3 };     // �����ɑΉ�����J�E���g�l

	static constexpr float FIRE_BALL_SPEED = 2.0f;							//�����蔻��̃X�g�b�v�J�E���g

	//�R���X�g���N�^
	Level6(void);

	//�f�X�g���N�^
	~Level6(void);

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

	//���Z�b�g
	void Reset() override;

	//�I�u�W�F�N�g���̈ʒu�����炷
	void ShiftGame() override;

	//���̓����蔻��
	void HitMoon();

	//�΂̋ʂ̏���
	void FireBallUpdate();

	//�t�@�C�A�[�{�[������
	void CreateFireBall();

	//�������Ƃɉ΂̋ʂ̐����������߂�
	int GetCreateFireBallCnt();

	//�΂̋ʂ�Ԃ�
	FireBall* GetValidFireBall();

	//��������
	void BlastUpdate();

private:

	//�C�x���g���C��
	int eventLine_;

	//�v���C���[��ԕω��p�J�E���g
	int paramCnt_;

	//�΂̋ʏo���p�J�E���g
	int fireCnt_;

	//�΂̋ʏo�������l
	int fireCreateCnt_;

	//���������m�F
	bool isBlast_;

	//�X�s�[�h�_�E�����m�F
	bool isSpeedDown_;

	//����(�|�C���^)
	std::vector<Blast*> blasts_;

	//�΂̋�
	std::vector<FireBall*> fire_;
};

