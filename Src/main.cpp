#define _CRTDBG_MAP_ALLOC
#include <DxLib.h>
#include "Application.h"

// WinMain関数
//---------------------------------
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// インスタンスの生成
	Application::CreateInstance();

	// インスタンスの取得
	Application& instance = Application::GetInstance();

	if (instance.IsInitFail())
	{
		// 初期化失敗
		return -1;
	}

	// 実行
	instance.Run();

	// 解放
	instance.Release();

	if (instance.IsReleaseFail())
	{
		// 解放失敗
		return -1;
	}

	return 0;

}
