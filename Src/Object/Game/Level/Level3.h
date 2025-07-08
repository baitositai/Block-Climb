#pragma once
#include "LevelManager.h"

class Blast;
class Moon;

class Level3 :public LevelManager
{
public:

	static constexpr int FIELD_WIDTH = 16;                          // �t�B�[���h�̉��̃u���b�N��
	static constexpr int FIELD_HEIGHT = 12;                         // �t�B�[���h�̏c�̃u���b�N��

	static constexpr int GROUND_HEIGHT = 3;                         // �n�ʂ̏c�̃u���b�N��

	static constexpr int PLAYER_START_BLOCK_OFFSET_Y = 2;           // �v���C���[�̏c�̈ʒu�̃u���b�N���I�t�Z�b�g
	static constexpr int PLAYER_PIXEL_OFFSET_Y = 8;                 // �v���C���[�̏c�̃s�N�Z������

	static constexpr int CAMERA_BLOCK_OFFSET_Y = 2;                 // �J�����̏c�����̃u���b�N�I�t�Z�b�g

	static constexpr int GOAL_OFFSET_X = 75;                        // �S�[���̉��̃I�t�Z�b�g
	static constexpr int GOAL_POS_Y = 600;                          // �S�[���̏c�̈ʒu

	//�R���X�g���N�^
	Level3(void);

	//�f�X�g���N�^
	~Level3(void);

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

	//���̓����蔻��
	void HitMoon();

private:
	Moon* moon_;
	std::vector<Blast*> blast_;
	bool isBlast_; //���������m�F
};

