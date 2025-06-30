#pragma once
#include "../../Common/Vector2F.h"
#include "../Game/PlayerBase.h"

class TitleScene;

class TitlePlayer :public PlayerBase
{
public:

	//�^�C�g���v���C���[�̉^�����
	enum class MOVE_STATE
	{
		NONE,
		MOVE,
		STOP
	};

	//�ړ�
	static constexpr int MOVES = 500;

	//�ړ��X�s�[�h
	static constexpr float SPEED = 3.0f;

	//�A�j���[�V�����X�s�[�h
	static constexpr float ANIM_SPEED = 0.2f;

	//�L�����N�^�[�g��l
	static constexpr float CHARA_RATE = 1.8f;

	//�Œ�ʒu
	static constexpr int POS_X = Application::SCREEN_SIZE_X / 5;
	static constexpr int POS_Y = Application::SCREEN_SIZE_Y - 145 - (SIZE_Y * 1.8 / 2);

	TitlePlayer();
	~TitlePlayer();

	void Init(TitleScene* parent, PLAYER_TYPE type);
	void Reset() override;
	void Update() override;
	void Draw() override;
	void Release();

	bool IsText();

private:
	//�L�����N�^�[�̎��
	PLAYER_TYPE type_;

	//�^�C�g���p�L�����N�^�[�X�e�[�g
	MOVE_STATE titState_;

	//��ʒu
	Vector2F fixedPos_;

	bool isText_;

	TitleScene* title_;

};

