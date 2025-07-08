#pragma once
#include <ctime>
#include <string>
#include <vector>
#include "../../../Common/Vector2.h"

class RabbitText
{
public: 

	//�����o���摜�T�C�Y
	static constexpr int SPEECH_SIZE_X = 542;
	static constexpr int SPEECH_SIZE_Y = 128;

	//�E�T�M�摜
	static constexpr int RABBIT_SIZE_X = 160;
	static constexpr int RABBIT_SIZE_Y = 160;

	//������\������Ԋu
	static constexpr float INTERVAL = 0.02f;

	//�t�H���g�T�C�Y
	static constexpr int FONT_SIZE = 32;

	//�t�H���g����
	static constexpr int FONT_THICK = 6;

	//�e�L�X�g��\���J�E���g
	static constexpr int TEXT_OFF_CNT = 5;

	//�R���X�g���N�^
	RabbitText();

	//�f�X�g���N�^
	~RabbitText();

	//������
	void Init();

	//���Z�b�g
	virtual void Reset();

	//�X�V
	virtual void Update() = 0;

	//���
	virtual void Release();
	
	//�t�H���g�ݒ�
	virtual void InitFont();

	//�e�L�X�g�ݒ�
	virtual void InitText() = 0;

	/// <summary>
	/// �E�T�M�̕`��
	/// </summary>
	/// <param name="pos"></param>�ʒu
	void RabbitDraw(Vector2 pos);

	/// <summary>
	/// �����o���̕`��
	/// </summary>
	/// <param name="pos"></param>�ʒu
	void SpeechDraw(Vector2 pos);
	
	/// <summary>
	/// �e�L�X�g�̕`��
	/// </summary>
	/// <param name="pos"></param>�`��ʒu���󂯎��
	virtual void TextDraw(Vector2 pos) = 0;

protected:

	//�e�L�X�g�Ɋւ�����
	struct Text
	{
		//���ݕ\�����Ă��镶���̃C���f�b�N�X
		int index_;

		//�e�L�X�g�̕\�����m�F
		bool isTexts_;

		//�e�L�X�g
		std::string text_;

		//�e�L�X�g�o����������
		bool isDisPlayingText_;
	};
	//�t�H���g
	int font_;

	//�t�H���g�T�C�Y
	int fontSize_;

	//�����o���p�J�E���g
	float step_;

	//�����o���X�s�[�h
	float speed_;

	//�e�L�X�g��\����
	bool isText_;

	// �Ō�ɕ�����\����������
	clock_t lastTime_;

	//������\���p�J�E���g
	float offCnt_;

	//���W
	Vector2 pos_;

	//�e�L�X�g�Ăяo���l
	int textData_;

	//�e�L�X�g���
	std::vector<Text> type_;	
	
	//�e�L�X�g�\���̍X�V
	void UpdateTextDisplayIndex();

private:

	//�E�T�M�摜
	int imgRabbit_;

	//�����o���摜
	int imgSpeech_;	
	
	//�e�L�X�g�̕\������������
	virtual void TextOff() = 0;
};