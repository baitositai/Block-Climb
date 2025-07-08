#pragma once
#include <DxLib.h>
#include "../../../Application.h"
#include "../Level/LevelManager.h"
#include "../../../Common/Vector2.h"

class Camera
{

public:

	//�J�������[�h
	enum class MODE
	{
		FIXED,
		SCROLL,
		FREE
	};

	//�J�����͈�
	static constexpr int WIDTH = Application::SCREEN_SIZE_X;		//�J�����̉���
	static constexpr int HEIGHT = 480;								//�J�����̏c��

	//�J�����X�N���[���X�s�[�h
	static constexpr float SCROLL_SPEED = 2.0f;

	//�R���X�g���N�^
	Camera(void);

	//�f�X�g���N�^
	~Camera(void);

	//������
	void Init(LevelManager* parent);

	//�X�V
	void Update(void);

	//�`��
	void Draw(void);

	//���
	void Release(void);

	//�J�����̃X�N���[���ړ�
	virtual void CameraScrollMove();

	//�f�o�b�O�p�J�����ړ�
	void CameraMoveDebug();

	//�J�����̈ړ�����
	virtual void CameraMoveRestriction();

	//�J�����̃��[�h�ύX
	void ChangeMode(MODE mode);

	//�J�����͈͓������f
	bool IsCameraRange(Vector2 pos, Vector2 size);

	//���W�̐ݒ�
	void SetPos(Vector2F pos);
	
	//���W��Ԃ�
	Vector2F GetPos(void);

protected:

	//�u���b�N�̍����̍ő�l
	int maxY_; 

	//�J�����̃��[�h
	MODE mode_;

	//�X�N���[���ő��
	int scrollMax_;

	//�X�N���[���l����p
	float scroll_;

	//�X�N���[���X�s�[�h
	float scrollSpeed_;

	//�J�������W
	Vector2F pos_;

	//�C���X�^���X
	LevelManager* level_;

};