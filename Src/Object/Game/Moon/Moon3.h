#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon3 : public Moon
{
public:

	//�ړ����x
	static constexpr float MOVE_SPEED = 3.0f;

	//�Ԋu
	static constexpr int INTERVAL = 5;

	

	//�����̃����_���b��
	static constexpr int CREATE_RAND_MAX_SECOND = 3;

	//�g�呬�x
	static constexpr float EXPANSION_SPEED = 0.2f;

	//�R���X�g���N�^
	Moon3();

	//�f�X�g���N�^
	~Moon3();

	//���Z�b�g
	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

private:

	int cnt_;

	//�ړ���
	int downCnt_;

	//�o���J�E���g
	int respawn_;

	//�A���t�@�l
	int alpha_;

	//�X�s�[�h
	float move_;

};

