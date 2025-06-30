#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon6 : public Moon
{
public:

	//�ړ����x
	static constexpr float MOVE_SPEED = 3.0f;

	//�Ԋu
	static constexpr int INTERVAL = 5;

	//�S�[�����ʒu�����p
	static constexpr int GOAL_MOON_HEIGHT_OFFSET = 80;

	//���̈ʒu�����o�b�N�A�b�v�l
	static constexpr int MOON_GOAL_PRE_BLOCK = 24;

	//���̃X�N���[�����x
	static constexpr float MOON_SCROLL_SPEED = 2.0f;

	//���̍s�����������l
	static constexpr int DARK_MOON_TERM_HEIGHT = 20;	//����
	static constexpr int GOAL_MOON_TERM_HEIGHT = 70;	//�S�[��

	//�����I�t�Z�b�g
	static constexpr float DARK_POS_Y_OFFSET = 1.5f;

	//�����̃����_�����o������
	static constexpr int DARK_SCREEN_DIVISOR = 3;

	//�����_�������p�l
	static constexpr int RANDAM_MOON_DOWN_MIN = 2;
	static constexpr int RANDAM_MOON_DOWN_MAX = 4;

	//�R���X�g���N�^
	Moon6();

	//�f�X�g���N�^
	~Moon6();

	//���Z�b�g
	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�������̓��������_������
	DARK_MOVE RandamDarkMove();

	//���W�̃��Z�b�g
	Vector2F ResetPos();

	//�X�s�[�h�̃��Z�b�g
	Vector2F ResetSpeed();
	
	//�������̏���
	void DarkMoonUpdate(void);	//�X�V
	void DarkMoonDraw(void);	//�`��


	//���F���̏���
	void GoalMoonUpdate(void);	//�X�V
	void GoalMoonDraw(void);	//�`��

private:

	//��~�J�E���g
	float stopCnt_;

	//�ړ���
	int downCnt_;

	//�o���J�E���g
	int respawn_;

	//�A���t�@�l
	int alpha_;

	//�u���b�N�̑O�l
	int preBlock_;

	float scroll_;
	float scrollSpeed_;
	float scrollMax_;

	//�X�s�[�h
	Vector2F speed_;

};

