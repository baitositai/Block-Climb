#pragma once
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"

class LevelManager;

class FireBall
{
public:

	enum class STATE
	{
		FIRE,
		BLAST,
		NONE
	};

	//�摜�̕���
	static constexpr int WIDTH = 4;
	static constexpr int HEIGHT = 1;

	//�摜�T�C�Y
	static constexpr int SIZE_X = 48;
	static constexpr int SIZE_Y = SIZE_X;

	//�A�j���[�V������
	static constexpr int ANIM_NUM = WIDTH * HEIGHT;

	//�Փ˔���p���a
	static constexpr float RADIUS = 16.0f;

	//�A�j���[�V�������x
	static constexpr float ANIM_SPEED = 0.3f;

	//�R���X�g���N�^
	FireBall();

	//�f�X�g���N�^
	~FireBall();

	//����
	void Create(LevelManager* parent, float speed);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���
	void Release();

	//�ǂݍ���
	void Load();

	//���Z�b�g
	void Reset();

	//���W���Z�b�g����
	void SetPos(Vector2F pos);

	//�X�e�[�g�̕ύX
	void SetState(STATE state);

	//���W��Ԃ�
	Vector2F GetPos();

	//�X�e�[�g��Ԃ�
	STATE GetState();

private:

	//�摜
	int imgFireBall_[static_cast<int>(STATE::NONE)][ANIM_NUM];

	//�A�j���[�V�����J�E���g
	int cntAnim_;

	//�\�����Ă���A�j���[�V�����l
	int idxAnim_;

	//�X�s�[�h
	float speed_;

	//�����̃A�j���[�V�������x
	float animSpeed_;

	//�X�e�[�g
	STATE state_;

	//���W
	Vector2F pos_;

	//�C���X�^���X
	LevelManager* level_;
};