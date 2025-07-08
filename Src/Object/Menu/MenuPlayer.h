#pragma once
#include "../../Application.h"
#include "../Game/PlayerBase.h"

class MenuScene;

class MenuPlayer : public PlayerBase
{
public:

	//�s�����
	enum class MOVE_STATE
	{
		NONE,
		ADMISSION,
		EXIT
	};

	//���x
	static constexpr float SPEED = 5.0f;

	//�A�j���[�V�������x
	static constexpr float ANIM_SPEED = 0.2f;

	//�v���C���[�g�嗦
	static constexpr float PLAYER_RATE = 3.5f;

	//�Œ�ʒu
	static constexpr int FIXED_POS_X = Application::SCREEN_SIZE_X - 300;
	static constexpr int FIXED_POS_Y = Application::SCREEN_SIZE_Y - (200 + SIZE_Y);

	//�ޏo�I��
	static constexpr int EXIT_FINISH = Application::SCREEN_SIZE_X + SIZE_X + 20;

	//�R���X�g���N�^
	MenuPlayer();

	//�f�X�g���N�^
	~MenuPlayer();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent"></param>�e�C���X�^���X
	void Init(MenuScene* parent);

	//�ϐ��̏�����
	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="state"></param>���̏��
	void ChangeState(const MOVE_STATE state);

private:

	//�X�e�[�g
	MOVE_STATE state_;

	//��ʒu
	Vector2F fiexdPos_;

	//�C���X�^���X
	MenuScene* menu_;	
	
	//���ꏈ��
	void Admission();

	//�ޏꏈ��
	void Exit();

};