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
	//インスタンスの取得
	level_ = parent;

	//ゲームフィールドの高さの最大値を得る
	maxY_ = level_->GetFieldSize().y;

	//カメラ初期座標の設定
	pos_ = level_->GetFirstCameraPos();

	//スクロールスピードの設定
	scrollSpeed_ = SCROLL_SPEED;

	//カメラモード
	mode_ = MODE::SCROLL;
}

void Camera::Update(void)
{
	switch (mode_)
	{
	case Camera::MODE::FIXED:
		break;
	case Camera::MODE::SCROLL:
		//カメラのスクロール処理
		CameraScrollMove();
		break;
	case Camera::MODE::FREE:
		//デバッグカメラ処理
		CameraMoveDebug();
		break;
	default:
		break;
	}

	//カメラのスクロール制限
	CameraMoveRestriction();

	//デバッグカメラ処理
	CameraMoveDebug();

}

void Camera::Draw(void)
{
	////画面スクロールの範囲
	//DrawLine(
	//	0,
	//	HEIGHT,
	//	Application::SCREEN_SIZE_X,
	//	HEIGHT,
	//	0xff0000, false);

	//maxY_ = level_->GetFieldBlockY(maxY_);

	//Vector2 blockPos = { 0,BlockBase::BLOCK_SIZE_Y * maxY_ };

	////ブロックの位置とカメラの位置の差分を取る
	//int diffX = blockPos.x - pos_.x;
	//int diffY = blockPos.y - pos_.y;

	//float scrollDownMax = level_->GetFirstCameraPos().y;

	////下枠の制限
	//if (diffY > scrollDownMax) { diffY = scrollDownMax; }
	//if (diffY < Application::SCREEN_SIZE_Y) { diffY = Application::SCREEN_SIZE_Y; }

	////カメラ範囲内
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

//カメラ座標の取得
Vector2F Camera::GetPos(void)
{
	return pos_;
}

void Camera::CameraScrollMove()
{
	//ブロックが置いてある最上位置を得る
	maxY_ = level_->GetFieldBlockY(maxY_);

	Vector2 blockPos = { 0,BlockBase::BLOCK_SIZE_Y * maxY_ };

	//ブロックの位置とカメラの位置の差分を取る
	int diffX = blockPos.x - pos_.x;
	int diffY = blockPos.y - pos_.y;

	//カメラの左枠処理(必要はない)
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
	
	//カメラの右枠処理(必要はない)
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

	//カメラの上枠処理
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

	//カメラの下枠処理
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
	//カメラの下限の値を得る
	float scrollDownMax = level_->GetFirstCameraPos().y;

	//カメラの移動制限
	//左枠
	if (pos_.x < 0)
	{
		pos_.x = 0;
	}
	//右枠(必要はない)
	if (pos_.x > Application::SCREEN_SIZE_X)
	{
		pos_.x = Application::SCREEN_SIZE_X;
	}
	//上枠
	if (pos_.y < 0)
	{
		pos_.y = 0;
	}
	//下枠
	if (pos_.y > scrollDownMax)
	{
		pos_.y = scrollDownMax;
	}
}

//カメラモードの変更
void Camera::ChangeMode(MODE mode)
{
	mode_ = mode;
}

//デバッグ用カメラ操作
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

	//ターゲットがカメラ内か確認
	//下枠
	//ターゲットの上部の値を取得
	int targetUp = targetPos.y - targetSize.y / 2;

	//カメラの下枠の値を取得
	Vector2 blockPos = { 0,BlockBase::BLOCK_SIZE_Y * maxY_ };
	int cameraDown = blockPos.y - pos_.y + Application::SCREEN_SIZE_Y - HEIGHT;

	//下枠の制限
	if (cameraDown > scrollDownMax) { cameraDown = scrollDownMax; }
	if (cameraDown < Application::SCREEN_SIZE_Y) { cameraDown = Application::SCREEN_SIZE_Y; }

	//判定
	if (targetUp > cameraDown) { return true; }

	return false;
}

void Camera::SetPos(Vector2F pos)
{
	pos_ = pos;
}
