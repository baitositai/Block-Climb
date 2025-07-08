#pragma once
#include <string>
#include "../Common/Vector2.h"



class FadeText
{
public:

	//�R���X�g���N�^
	FadeText();

	//�f�X�g���N�^
	~FadeText();

	/// <summary>
	/// �e�L�X�g�̐ݒ�
	/// </summary>
	/// <param name="font"></param>�t�H���g
	/// <param name="color"></param>�F
	/// <param name="fontSize"></param>�T�C�Y
	/// <param name="pos"></param>���W
	/// <param name="text"></param>�e�L�X�g
	void SetText(int font, int color,int fontSize,Vector2 pos,std::string text);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���
	void Release();

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos"></param>���W
	void SetPos(Vector2 pos);

private:

	//�t�H���g
	int font_;

	//�A���t�@�l
	int alpha_;

	//�t�F�[�h�l
	int fade_;

	//�F
	int color_;

	//�傫��
	int size_;

	//���W
	Vector2 pos_;

	//�e�L�X�g
	std::string text_;

};

