#pragma once
#include<vector>
#include"Vector2.h"
#include"Vector2F.h"

class Scroll
{
public:
	Scroll();
	~Scroll();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="image"></param>�摜
	/// <param name="imageSize"></param>�摜�T�C�Y
	/// <param name="drawNum"></param>�`�搔
	/// <param name="scrollSpeed"></param>�X�N���[�����x
	void Init(int image, Vector2 imageSize, int drawNum, float scrollSpeed);
	void Update();	//�X�V
	void Draw();	//�`��
	void Release();	//���

	//���X�N���[���p���W�ݒ�
	void SetWidthScrollPos();
	
private:
	
	//�`��p�摜
	int imgBack_;

	//�摜�T�C�Y
	Vector2 size_;

	//�`��ʒu�p���W
	std::vector<Vector2F> pos_;

	//�X�N���[���X�s�[�h
	float speed_;
	
};

