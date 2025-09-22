#pragma once
#include <string>

class Application
{

public:
	// 色の深度
	static constexpr int COLOR_BIT_DEPTH = 32;

	// スクリーンサイズ
	static constexpr int SCREEN_SIZE_X = 1280;
	static constexpr int SCREEN_SIZE_Y = 720;

	//フォント種類
	static constexpr int FONT_TYPES = 2;

	//フォントネーム
	static const std::string FONT_DOT;
	static const std::string FONT_BOKUTATI;

	// データパス関連
	//-------------------------------------------
	static const std::string PATH_MOVIE;
	static const std::string PATH_IMAGE;
	static const std::string PATH_CSV;
	static const std::string PATH_FONT;
	static const std::string PATH_SOUND;
	static const std::string PATH_BLOCK;
	//-------------------------------------------

	// 明示的にインステンスを生成する
	static void CreateInstance(void);

	// 静的インスタンスの取得
	static Application& GetInstance(void);

	// 初期化
	void Init(void);

	// ゲームループの開始
	void Run(void);

	// リソースの解放
	void Release(void);

	// 初期化成功／失敗の判定
	bool IsInitFail(void) const;

	// 解放成功／失敗の判定
	bool IsReleaseFail(void) const;

private:

	// 静的インスタンス
	static Application* instance_;

	// 初期化失敗
	bool isInitFail_;

	// 解放失敗
	bool isReleaseFail_;

	std::string fontPath_[FONT_TYPES];

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	Application(void);

	// コピーコンストラクタも同様
	Application(const Application&);

	// デストラクタも同様
	~Application(void);

};