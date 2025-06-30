#pragma once
#include "../../Application.h"
#include "../../Common/Vector2.h"

class GameScene;

class GameClear
{
public:

	//�摜�T�C�Y
	static constexpr int SIZE_X = 491;
	static constexpr int SIZE_Y = 206;

	//�h�炷���g��
	static constexpr float AMPLITUDE = 1.0f;

	//�h�炷�U��
	static constexpr float FREQUENCY = 10.0f;

	//���W�ʒu
	static constexpr int POS_X = Application::SCREEN_SIZE_X / 2 - SIZE_X / 2;
	static constexpr int POS_Y = Application::SCREEN_SIZE_Y / 2 - SIZE_Y / 2;

	//�R���X�g���N�^
	GameClear();

	//�f�X�g���N�^
	~GameClear();

	// ������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���
	void Release();

private:

	//�摜�̊i�[
	int imgClear_;

	//�`��p���W
	Vector2 pos_;

};

