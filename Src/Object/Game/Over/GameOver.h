#pragma once
#include "../../../Common/Vector2.h"

class GameScene;

class GameOver
{
public:

	//�摜�T�C�Y
	static constexpr int SIZE_X = 762;
	static constexpr int SIZE_Y = 203;

	//�h�炷���g��
	static constexpr float AMPLITUDE = 1.0f;

	//�h�炷�U��
	static constexpr float FREQUENCY = 10.0f;

	//���W�ʒu
	static constexpr int POS_X = Application::SCREEN_SIZE_X / 2 - SIZE_X / 2;
	static constexpr int POS_Y = Application::SCREEN_SIZE_Y / 2 - SIZE_Y / 2;

	//�R���X�g���N�^
	GameOver();

	//�f�X�g���N�^
	~GameOver();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���
	void Release();

private:

	//�摜�̊i�[
	int imgOver_;

	//�`��p���W
	Vector2 pos_;
};