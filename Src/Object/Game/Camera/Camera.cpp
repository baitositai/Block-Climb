#include "Camera.h"
#include "../../../Application.h"
#include "../Level/LevelManager.h"
#include "../Block/BlockBase.h"
#include "../BackGround.h"

Camera::Camera(void)
{
	level_ = nullptr;
	maxY_ = 0;
	pos_ = { 0, 0};
	scrollMax_ = 0;
	scroll_ = 0.0f;
	scrollSpeed_ = 0.0f;
	mode_ = MODE::FREE;
}

Camera::~Camera(void)
{
}

void Camera::Init(LevelManager* parent)
{
	//�C���X�^���X�̎擾
	level_ = parent;

	//�Q�[���t�B�[���h�̍����̍ő�l�𓾂�
	maxY_ = level_->GetFieldSize().y;

	//�J�����������W�̐ݒ�
	pos_ = level_->GetFirstCameraPos();

	//�X�N���[���X�s�[�h�̐ݒ�
	scrollSpeed_ = SCROLL_SPEED;

	//�J�������[�h
	mode_ = MODE::SCROLL;
}

void Camera::Update(void)
{
	switch (mode_)
	{
	case Camera::MODE::FIXED:
		break;
	case Camera::MODE::SCROLL:
		//�J�����̃X�N���[������
		CameraScrollMove();
		break;
	case Camera::MODE::FREE:
		//�f�o�b�O�J��������
		CameraMoveDebug();
		break;
	default:
		break;
	}

	//�J�����̃X�N���[������
	CameraMoveRestriction();

	//�f�o�b�O�J��������
	CameraMoveDebug();

}

void Camera::Draw(void)
{
	////��ʃX�N���[���͈̔�
	//DrawLine(
	//	0,
	//	HEIGHT,
	//	Application::SCREEN_SIZE_X,
	//	HEIGHT,
	//	0xff0000, false);

	//maxY_ = level_->GetFieldBlockY(maxY_);

	//Vector2 blockPos = { 0,BlockBase::BLOCK_SIZE_Y * maxY_ };

	////�u���b�N�̈ʒu�ƃJ�����̈ʒu�̍��������
	//int diffX = blockPos.x - pos_.x;
	//int diffY = blockPos.y - pos_.y;

	//float scrollDownMax = level_->GetFirstCameraPos().y;

	////���g�̐���
	//if (diffY > scrollDownMax) { diffY = scrollDownMax; }
	//if (diffY < Application::SCREEN_SIZE_Y) { diffY = Application::SCREEN_SIZE_Y; }

	////�J�����͈͓�
	//DrawBox(
	//	diffX,
	//	diffY + Application::SCREEN_SIZE_Y - HEIGHT,
	//	diffX + WIDTH,
	//	diffY + Application::SCREEN_SIZE_Y - HEIGHT -5,
	//	0xffff00, true);

}

void Camera::Release(void)
{
}

//�J�������W�̎擾
Vector2F Camera::GetPos(void)
{
	return pos_;
}

void Camera::CameraScrollMove()
{
	//�u���b�N���u���Ă���ŏ�ʒu�𓾂�
	maxY_ = level_->GetFieldBlockY(maxY_);

	Vector2 blockPos = { 0,BlockBase::BLOCK_SIZE_Y * maxY_ };

	//�u���b�N�̈ʒu�ƃJ�����̈ʒu�̍��������
	int diffX = blockPos.x - pos_.x;
	int diffY = blockPos.y - pos_.y;

	//�J�����̍��g����(�K�v�͂Ȃ�)
	if (diffX < WIDTH)
	{
		scrollMax_ = WIDTH - diffX;
	
		if (scrollMax_ >= scroll_)
		{
			pos_.x -= scrollSpeed_;
			scroll_ += scrollSpeed_;
		}
		else
		{
			scroll_ = 0.0f;
		}
	}
	
	//�J�����̉E�g����(�K�v�͂Ȃ�)
	if (diffX > Application::SCREEN_SIZE_X - WIDTH)
	{
		scrollMax_ = Application::SCREEN_SIZE_X - WIDTH - diffX;
	
		if (scrollMax_ >= scroll_)
		{
			pos_.x -= scrollSpeed_;
			scroll_ += scrollSpeed_;
		}
		else
		{
			scroll_ = 0.0f;
		}
	}

	//�J�����̏�g����
	if (diffY < HEIGHT)
	{
		scrollMax_ = HEIGHT - diffY;
	
		if (scrollMax_ >= scroll_)
		{
 			pos_.y -= scrollSpeed_;
			scroll_ += scrollSpeed_;
		}
		else
		{
			scroll_ = 0.0f;
		}
	}

	//�J�����̉��g����
	if (diffY > Application::SCREEN_SIZE_Y - HEIGHT)
	{
		if (pos_.x < 0)
		{
			scrollMax_ = Application::SCREEN_SIZE_Y - HEIGHT - diffY;
		}
			
		if (scrollMax_ >= scroll_)
		{
			pos_.y -= scrollSpeed_;
			scroll_ += scrollSpeed_;
		}
		else
		{
			scroll_ = 0.0f;
		}
	}
}

void Camera::CameraMoveRestriction()
{
	//�J�����̉����̒l�𓾂�
	float scrollDownMax = level_->GetFirstCameraPos().y;

	//�J�����̈ړ�����
	//���g
	if (pos_.x < 0)
	{
		pos_.x = 0;
	}
	//�E�g(�K�v�͂Ȃ�)
	if (pos_.x > Application::SCREEN_SIZE_X)
	{
		pos_.x = Application::SCREEN_SIZE_X;
	}
	//��g
	if (pos_.y < 0)
	{
		pos_.y = 0;
	}
	//���g
	if (pos_.y > scrollDownMax)
	{
		pos_.y = scrollDownMax;
	}
}

//�J�������[�h�̕ύX
void Camera::ChangeMode(MODE mode)
{
	mode_ = mode;
}

//�f�o�b�O�p�J��������
void Camera::CameraMoveDebug(void)
{
	const int SPEED_CAMERA = 8;

	if (CheckHitKey(KEY_INPUT_I)) { pos_.y -= SPEED_CAMERA; }
	if (CheckHitKey(KEY_INPUT_K)) { pos_.y += SPEED_CAMERA; }
	if (CheckHitKey(KEY_INPUT_J)) { pos_.x -= SPEED_CAMERA; }
	if (CheckHitKey(KEY_INPUT_L)) { pos_.x += SPEED_CAMERA; }
}

bool Camera::IsCameraRange(Vector2 pos, Vector2 size)
{
	Vector2 cameraPos = pos_.ToVector2();
	Vector2 targetPos = { pos.x - cameraPos.x,pos.y - cameraPos.y };
	Vector2 targetSize = size;
	float scrollDownMax = level_->GetFirstCameraPos().y;

	//�^�[�Q�b�g���J���������m�F
	//���g
	//�^�[�Q�b�g�̏㕔�̒l���擾
	int targetUp = targetPos.y - targetSize.y / 2;

	//�J�����̉��g�̒l���擾
	Vector2 blockPos = { 0,BlockBase::BLOCK_SIZE_Y * maxY_ };
	int cameraDown = blockPos.y - pos_.y + Application::SCREEN_SIZE_Y - HEIGHT;

	//���g�̐���
	if (cameraDown > scrollDownMax) { cameraDown = scrollDownMax; }
	if (cameraDown < Application::SCREEN_SIZE_Y) { cameraDown = Application::SCREEN_SIZE_Y; }

	//����
	if (targetUp > cameraDown) { return true; }

	return false;
}

void Camera::SetPos(Vector2F pos)
{
	pos_ = pos;
}
