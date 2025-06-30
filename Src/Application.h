#pragma once
#include <string>

class Application
{

public:
	// �F�̐[�x
	static constexpr int COLOR_BIT_DEPTH = 32;

	// �X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = 1280;
	static constexpr int SCREEN_SIZE_Y = 720;

	//�t�H���g���
	static constexpr int FONT_TYPES = 2;

	//�t�H���g�l�[��
	static const std::string FONT_DOT;
	static const std::string FONT_BOKUTATI;

	// �f�[�^�p�X�֘A
	//-------------------------------------------
	static const std::string PATH_MOVIE;
	static const std::string PATH_IMAGE;
	static const std::string PATH_CSV;
	static const std::string PATH_FONT;
	static const std::string PATH_SOUND;
	static const std::string PATH_BLOCK;
	//-------------------------------------------

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static Application& GetInstance(void);

	// ������
	void Init(void);

	// �Q�[�����[�v�̊J�n
	void Run(void);

	// ���\�[�X�̉��
	void Release(void);

	// �����������^���s�̔���
	bool IsInitFail(void) const;

	// ��������^���s�̔���
	bool IsReleaseFail(void) const;

private:

	// �ÓI�C���X�^���X
	static Application* instance_;

	// ���������s
	bool isInitFail_;

	// ������s
	bool isReleaseFail_;

	std::string fontPath_[FONT_TYPES];

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	Application(void);

	// �R�s�[�R���X�g���N�^�����l
	Application(const Application&);

	// �f�X�g���N�^�����l
	~Application(void);

};