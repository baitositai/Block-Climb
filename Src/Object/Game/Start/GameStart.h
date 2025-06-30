#pragma once
#include <string>
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"

class GameScene;

class GameStart
{
public:
	enum class STATE
	{
		NONE,
		UP,
		WAIT,
		EXIT,
	};

	//�摜�T�C�Y
	static constexpr int SIZE_X = 491;
	static constexpr int SIZE_Y = 206;

	//�摜�g���
	static constexpr float EXPANSION = 0.05f;
	static constexpr float EXPANSION_MAX = 1.0f;

	//�҂��b��
	static constexpr float WAIT_SECOND = 1.5f;

	//���W�ړ����x
	static constexpr float MOVE_SPEED = 0.02f;

	//��]��
	static constexpr float ROTATION = 0.33f;

	//�R���X�g���N�^
	GameStart(void);

	//�f�X�g���N�^
	~GameStart(void);

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent"></param>�e�C���X�^���X
	void Init(GameScene* parent);

	//�X�V
	void Update(void);

	//�`��
	void Draw(void);

	//���
	void Release(void);

	//�ϐ��̏�����
	void Reset();

	//�摜�ݒ�
	virtual void SetImage()  = 0;

protected:

	//�摜�̊i�[
	int imgStart_;

	//�摜�̑傫��
	Vector2 size_;

	//�摜�g��T�C�Y
	float expansion_;

	//�摜��]�p
	float angle_;

	//�҂��p�J�E���g�ϐ�
	int cnt_;

	//��Ԋi�[
	STATE state_;

	//�`��p���W
	Vector2F pos_;

	//�C���X�^���X
	GameScene* gameScene_;

};

