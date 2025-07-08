#pragma once
#include "../../Common/Vector2F.h"
#include "../../Application.h"

class BackGround
{
public:
	//�w�i�̎��
	enum class TYPE
	{
		SKY,
		NIGHT,
		SUNSET,
		MAX
	};

	//�w�i�̉摜�T�C�Y
	static constexpr int IMAGE_SIZE_X = 1864;	
	static constexpr int IMAGE_SIZE_Y = 720;	

	//�w�i�̕`�搔
	static constexpr int DRAW_IMAGES = 2;

	//�X�N���[���X�s�[�h
	static constexpr float SCR_SPEED = 0.5f;

	//�X�J�C�X�^�[�g
	static constexpr int SKY_START = 8;

	//�X�J�C�I���
	static constexpr int SKY_FIN = 15;	
	
	//�T���Z�b�g��
	static constexpr int SUN_NUM = 2;

	//�T���Z�b�g�X�^�[�g
	static constexpr int SUN_START[SUN_NUM] = { 16,5 };

	//�T���Z�b�g�I���
	static constexpr int SUN_FIN[SUN_NUM] = { 19,7 };

	//�w�i�X�N���[���ő�l
	static constexpr float SCROLL_MAX = IMAGE_SIZE_X;
	
	BackGround(void);							//�R���X�g���N�^
	~BackGround(void);							//�f�X�g���N�^

	void Init(void);							//������
	virtual void Update(void);					//�X�V�����i���x���s�j
	virtual void Draw(void);					//�`�揈���i���x���s�j
	void Release(void);							//������� (�I�������̂ݎ��s)

	//�ϐ��̏�����
	virtual void Reset();

private:

	//�摜�̊i�[�p
	int imgSky_[static_cast<int>(TYPE::MAX)];

	//�w�i�̎�ނ̊i�[
	int skyType_;

	//�X�N���[���p�ϐ�
	Vector2F drawPos_[DRAW_IMAGES];
	float scrollSpeed_;

	//�摜�̓ǂݍ���
	void Load();

};

