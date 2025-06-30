#pragma once
#include <DxLib.h>
#include "../../../Application.h"
#include "../Level/LevelManager.h"
#include "../../../Common/Vector2.h"

class Camera
{

public:

	//カメラモード
	enum class MODE
	{
		FIXED,
		SCROLL,
		FREE
	};

	//カメラ範囲
	static constexpr int WIDTH = Application::SCREEN_SIZE_X;		//カメラの横幅
	static constexpr int HEIGHT = 480;								//カメラの縦幅

	//カメラスクロールスピード
	static constexpr float SCROLL_SPEED = 2.0f;

	//コンストラクタ
	Camera(void);

	//デストラクタ
	~Camera(void);

	//初期化
	void Init(LevelManager* parent);

	//更新
	void Update(void);

	//描画
	void Draw(void);

	//解放
	void Release(void);

	//カメラのスクロール移動
	virtual void CameraScrollMove();

	//デバッグ用カメラ移動
	void CameraMoveDebug();

	//カメラの移動制限
	virtual void CameraMoveRestriction();

	//カメラのモード変更
	void ChangeMode(MODE mode);

	//カメラ範囲内か判断
	bool IsCameraRange(Vector2 pos, Vector2 size);

	//座標の設定
	void SetPos(Vector2F pos);
	
	//座標を返す
	Vector2F GetPos(void);

protected:

	//ブロックの高さの最大値
	int maxY_; 

	//カメラのモード
	MODE mode_;

	//スクロール最大量
	int scrollMax_;

	//スクロール値代入用
	float scroll_;

	//スクロールスピード
	float scrollSpeed_;

	//カメラ座標
	Vector2F pos_;

	//インスタンス
	LevelManager* level_;

};