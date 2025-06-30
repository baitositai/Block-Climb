#pragma once
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"

class LevelManager;

class Moon
{
public:

	enum class MOON_TYPE
	{
		GOAL,		//���F
		CREATE,		//��
		CHANGE,		//��
		DEAD,		//��
		MAX
	};

	enum class DARK_MOVE
	{
		STOP,		//��~
		DOWN,		//���֗�����
		FADE_BIG,	//�傫���Ȃ��ăt�F�[�h����
		WIDTH,		//���ړ�
		DIAGONAL,	//�΂߈ړ�
		DIAGONAL_RE	//�΂߈ړ��t
	};

	//�S�[���T�C�Y
	static constexpr int SIZE_X = 100;
	static constexpr int SIZE_Y = SIZE_X;

	//���a
	static constexpr int RADIUS = SIZE_X / 2;

	//�h�炷���g��
	static constexpr float AMPLITUDE = 1.0f;

	//�h�炷�U��
	static constexpr float FREQUENCY = 5.0f;

	//�g�呬�x
	static constexpr float EXPANSION_SPEED = 0.2f;

	//�g�嗦
	static constexpr float SIZE_MAX_RATE = 30.0f;

	//�R���X�g���N�^
	Moon();

	//�f�X�g���N�^
	~Moon();

	//������
	void Init(LevelManager* parent);

	//���Z�b�g
	virtual void Reset();

	//�X�V
	virtual void Update();

	//�`��
	virtual void Draw();

	//���
	void Release();

	//�ǂݍ���
	void Load();

	//����̐ݒ�
	void SetIsMoon(MOON_TYPE type, bool value);

	//�����p�X�e�[�g�̐ݒ�
	void SetDarkMove(DARK_MOVE move);

	//�����Ԃ�
	bool IsMoon(MOON_TYPE type);

	//�ʒu�ݒ�
	void SetPos(MOON_TYPE type, Vector2F pos);

	//�����ʒu�̐ݒ�
	void SetFirstPos(MOON_TYPE type, Vector2F pos);

	//���W��Ԃ�
	Vector2F GetPos(MOON_TYPE type);

	//�T�C�Y��Ԃ�
	Vector2 GetSize();

	//�����̍s���X�e�[�g��Ԃ�
	DARK_MOVE GetDarkMove();

protected:

	//�摜
	int images_[static_cast<int>(MOON_TYPE::MAX)];
	
	//�`��T�C�Y
	float drawSize_;

	//���̔���
	bool isMoon_[static_cast<int>(MOON_TYPE::MAX)];

	//�����p�s���X�e�[�g
	DARK_MOVE darkState_;

	//���W
	Vector2F pos_[static_cast<int>(MOON_TYPE::MAX)];

	//�������W
	Vector2F firstPos_[static_cast<int>(MOON_TYPE::MAX)];

	//�摜�T�C�Y
	Vector2 size_;

	//�C���X�^���X�̐���
	LevelManager* level_;

};

