#pragma once

class Vector2F;

class Vector2
{
public:

	int x;
	int y;

	// �R���X�g���N�^
	Vector2(void);

	// �R���X�g���N�^
	Vector2(int vX, int vY);

	// �f�X�g���N�^
	~Vector2(void);

	//Vector2F�֕ϊ�����֐�
	Vector2F ToVector2F(void);

};
