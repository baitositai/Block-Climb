#pragma once
#include "BlockBase.h"
#include "../Gimic/FireBall.h"


class Block4 :public BlockBase
{
public:

	//�΂̋ʐ����Ɋւ���v�f��
	static constexpr int FIREBALL_RULE_SIZE = 3;

	// �����������l�i�~���j
	static constexpr int FIREBALL_HEIGHT_THRESHOLDS[FIREBALL_RULE_SIZE] = {
		30, 15, 0
	};

	// �Ή����鐶����
	static constexpr int FIREBALL_COUNTS[FIREBALL_RULE_SIZE] = {
		3, 2, 1
	};	
	
	// �v�f��
	static constexpr int FIREBALL_SPEED_RULE_SIZE = 2;


	// �����������l�i�~���j
	static constexpr int FIREBALL_SPEED_HEIGHT_THRESHOLDS[FIREBALL_SPEED_RULE_SIZE] = {
		40, 0
	};

	// �Ή�����΂̋ʂ̗������x
	static constexpr float FIREBALL_SPEEDS[FIREBALL_SPEED_RULE_SIZE] = {
		5.0f, 3.0f
	};

	//�R���X�g���N�^
	Block4();

	//�f�X�g���N�^
	~Block4();

	//���ƒ҂̍X�V����
	void HitUpdate(Vector2 pos) override;

	//���Z�b�g
	void Reset(void) override;

	//�X�e�[�W��������
	void StageCreate(void) override;

	//�΂̋ʐ���
	void CreateFireBall();

	//�������Ƃ̉΂̋ʂ̐�������Ԃ�
	int GenerationNumber();

	//�������Ƃ̉΂̋ʂ̃X�s�[�h��ݒ�
	float FireBallSpeed();

	//�΂̋ʂ𐶐����ĕԂ�
	FireBall* GetValidFireBall();
};

