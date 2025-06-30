#pragma once
#include "RabbitText.h"

class LevelManager;

class RabbitMarason : public RabbitText
{
public:

	//�e�L�X�g����ސ�
	static constexpr int MARASON_TEXTS = 13;

	//�e�L�X�g����ސ�
	static constexpr int EVENT_TEXTS = 5;

	//�e�L�X�g����ސ�
	static constexpr int TEXT_TYPES = MARASON_TEXTS + EVENT_TEXTS;

	//���B���C��
	static constexpr int ARRIVAL_LINE[MARASON_TEXTS] = {
		1,20,46,60,82,102,115,130,150,175,199,300,500 };

	//�e�L�X�g�̃C���f�b�N�X	
	static constexpr int PLAYER_BUFF_TEXT_INDEX = 13;			//�v���C���[�̃o�t
	static constexpr int PLAYER_DEBUFF_TEXT_INDEX = 14;			//�v���C���[�̃f�o�t
	static constexpr int FIRE_TEXT_INDEX = 15;					//�΂̋�
	static constexpr int BLAST_TEXT_INDEX = 16;					//����
	static constexpr int BLOCK_FALL_SPEED_UP_TEXT_INDEX = 17;	//�u���b�N�̗������x�A�b�v

	//�R���X�g���N�^
	RabbitMarason();

	//�f�X�g���N�^
	~RabbitMarason();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent"></param>�e�N���X���󂯎��
	void Init(LevelManager* parent);

	void Reset() override;					
	void Update() override;					
	void TextDraw(Vector2 pos) override;	
	void InitText() override;	
	
	/// <summary>
	/// �e�L�X�g�Ɋւ���l��ݒ�
	/// </summary>
	/// <param name="value"></param>�e�L�X�g�̔ԍ����w��
	void SetTextData(int value);

private:

	//�J�E���g
	float time_;

	//���B���C��
	int arrivalLine_[MARASON_TEXTS];

	//�e�N���X
	LevelManager* level_;	

	//�e�L�X�g�I�t
	void TextOff()override;
};