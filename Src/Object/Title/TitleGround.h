#pragma once
#include <string>

class TitleGround
{
public:

#pragma region  �n�ʊ֘A�̒萔
	//�u���b�N�摜�̕����鐔
	static constexpr int GROUND_IMG_NUM_X = 22;
	static constexpr int GROUND_IMG_NUM_Y = 11;
	static constexpr int GROUND_IMG_NUM = GROUND_IMG_NUM_X * GROUND_IMG_NUM_Y;

	//�n�ʃ`�b�v��1�T�C�Y
	static constexpr int GROUND_SIZE_X = 50;
	static constexpr int GROUND_SIZE_Y = 50;
#pragma endregion

	//CSV�f�[�^�̕��ƍ���
	static constexpr int WIDTH = 26;
	static constexpr int HEIGHT = 3;

	TitleGround();
	~TitleGround();

	void Init();
	void Draw();
	void Release();
	void LoadStageCsvData();

private:
	//�摜�ǂݍ��ݗp
	int imgGrounds_[GROUND_IMG_NUM];

	//CSV�f�[�^�̓ǂݍ���
	std::string groundCsvDate_;

	//�f�[�^�i�[�p�z��
	int grounds_[HEIGHT][WIDTH];

};

