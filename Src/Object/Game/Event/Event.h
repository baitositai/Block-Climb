#pragma once
#include "../../../Common/Vector2.h"

class LevelManager;

class Event
{
public:

	enum class EVENT
	{
		SPEED_UP,
		BLOCK_SPEED_UP,
		SPEED_DOWN,
		BLAST_LINE,
		FIRE_BALL,
		NONE,
	};

	enum class EFECT
	{
		SPEED_UP,
		SPEED_DOWN,
		NONE
	};

	//�C�x���g�̎��
	static constexpr int EVENT_TYPE = static_cast<int>(EVENT::NONE);

	//�G�t�F�N�g�̃A�j���[�V�����X�s�[�h
	static constexpr float EFECT_ANIM_SPEED = 0.03f;

	//�G�t�F�N�g���
	static constexpr int EFECT_TYPE = static_cast<int>(EFECT::NONE);

	//�G�t�F�N�g�̊g��k��
	static constexpr float EFFECT_RATE_MAX = 1.5f;
	static constexpr float EFFECT_RATE_MIN = 1.0f;


	//�e�C�x���g�̔�����
	static constexpr int BLAST_FREQUENCY = 3;
	static constexpr int FIRE_BALL_FREQUENCY = 3;
	static constexpr int SPEED_UP_FREQUENCY = 3;
	static constexpr int BLOCK_SPEED_UP_FREQUENCY = 3;
	static constexpr int SPEED_DOWN_FREQUENCY = 3;
	static constexpr int FREQUENCY = 15;


	//�R���X�g���N�^
	Event();

	//�f�X�g���N�^
	~Event();

	//������
	void Init(LevelManager* parent);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���
	void Release();

	//���Z�b�g
	void Reset();

	//�ǂݍ���
	void Load();

	//�A�C�R���̕`��
	void IconDraw(Vector2 pos);

	//�G�t�F�N�g�̕`��
	void EfectDraw();

	//�C�x���g�������_���m���Ŕ���
	void EventOccurs();

	//�C�x���g��Ԃ̐ݒ�
	void SetEvent(EVENT value);

	//�G�t�F�N�g�̍��W�̐ݒ�
	void SetEfectPos(Vector2 pos);

	//�C�x���g��Ԃ�Ԃ�
	EVENT GetEvent();

private:

	//�A�C�R���摜
	int icon_[EVENT_TYPE];

	//�G�t�F�N�g�摜
	int efect_[EFECT_TYPE];

	//�G�t�F�N�g�T�C�Y
	float size_;

	//�G�t�F�N�g�A�j���[�V�����X�s�[�h
	float efectAnimSpeed_;

	//�G�t�F�N�g�̕`��ʒu
	Vector2 efectPos_;

	//�C�x���g���
	EVENT eventState_;

	//�G�t�F�N�g���
	EFECT efeState_;

	//�C���X�^���X
	LevelManager* level_;

};

