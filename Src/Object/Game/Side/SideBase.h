#pragma once
#include "../../../Common/Vector2.h"

class LevelManager;

class SideBase
{
public:

	//�t�H���g�T�C�Y
	static constexpr int FONT_SIZE = 32;

	//�t�H���g����
	static constexpr int FONT_THICK = 3;

	//�T�C�h��ʂɗp����摜�T�C�Y
	static constexpr int SIDE_IMAGE_SIZE_X = 50;
	static constexpr int SIDE_IMAGE_SIZE_Y = 50;

	static constexpr int SIDE_DRAW_SIZE_X = 48;
	static constexpr int SIDE_DRAW_SIZE_Y = 48;

	//�摜��������
	static constexpr int SIDE_IMAGES_X = 7;
	static constexpr int SIDE_IMAGES_Y = 1;

	//��ޑ���
	static constexpr int SIDE_IMAGES = SIDE_IMAGES_X * SIDE_IMAGES_Y;

	//�`��u���b�N���i���j
	static constexpr int DRAW_BLOCK_X = 8;

	//�`��u���b�N���̗]���ȏc�ǉ���
	static constexpr int DRAW_BLOCK_Y_EXTRA = 2;

	//�T�C�h�u���b�N�̏����^�C�v
	static constexpr int INIT_SIDE_BLOCK_TYPE = 0;

	//�E�[�ʒu�̕␳�l
	static constexpr int RIGHT_POS_OFFSET = 5;

	//�t�H���g�f�[�^�T�C�Y
	static constexpr int FONT_DATA_SIZE = 64;

	// Next�u���b�N�\���g�̃{�[�_�[�T�C�Y
	static constexpr int NEXT_BLOCK_BORDER = 3;

	// Next�u���b�N�\���̊Ԋu
	static constexpr int NEXT_BLOCK_INTERVAL_X = 40;
	static constexpr int NEXT_BLOCK_INTERVAL_Y = 20;

	// Next�u���b�N�\���g�̈ʒu
	static constexpr int NEXT_BLOCK_BOX_POS_X = NEXT_BLOCK_INTERVAL_X;
	static constexpr int NEXT_BLOCK_BOX_POS_Y = 150;

	// Next�u���b�N�\���g�̃T�C�Y
	static constexpr int NEXT_BLOCK_BOX_SIZE_X = 160; // �l�͎��s���ɒ�������Ă��邪���Őݒ�
	static constexpr int NEXT_BLOCK_BOX_SIZE_Y = 220;

	//Next�u���b�N��Y�����I�t�Z�b�g�{��
	static constexpr int NEXT_BLOCK_Y_OFFSET_RATE = 3;

	//����
	static constexpr int SECONDS_IN_AN_HOUR = 3600;
	static constexpr int SECONDS_IN_A_MINUTE = 60;

	//�R���X�g���N�^
	SideBase(void);	
	
	//�f�X�g���N�^						
	~SideBase(void);						

	//�����������i�ŏ��̈��̂ݎ��s)
	void Init(LevelManager* parent);
	
	//�ϐ�����������		
	virtual void Reset();		
	
	//�X�V�����i���x���s�j			
	virtual void Update(void);		
	
	//�`�揈���i���x���s�j		
	virtual void Draw(void);					
	
	//������� (�I�������̂ݎ��s)
	void Release(void);					

	//�t�H���g�ݒ�
	virtual void SetFont();

	//�l�N�X�g�~�m�p���̕`��
	void NextMinoDraw();

	//�ӂ�����̎l�p�`�`��
	void WBorderRectangle(Vector2 size, Vector2 pos, int border);

protected:
	
	//�摜�̊i�[�p
	int imgSideBlock_[SIDE_IMAGES];

	//�T�C�h��ʂ̎��
	int sideBlockType_;

	//�t�H���g
	int normalFont_;

	//�����p�t�H���g
	int dataFont_;

	//�t�H���g�T�C�Y
	int nmlFontSize_;

	//�����p�t�H���g�T�C�Y
	int dataFontSize_;

	//�u���b�N�̕`�搔
	int drawBlockX;
	int drawBlockY;

	//���S�ɕ`��p�̒����l
	Vector2 center_;

	//�T�C�h��ʂ������Q�[����ʂ̃T�C�Y
	Vector2 gameSize_;

	//�E�n�_
	Vector2 rightPos_;

	//�E�T�C�h�̃T�C�Y
	Vector2 rightSideSize_;

	//���n�_
	Vector2 leftPos_;

	//���T�C�h�̃T�C�Y
	Vector2 leftSideSize_;

	//����
	int time_;

	//�C���X�^���X
	LevelManager* level_;

};

