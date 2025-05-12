#pragma once
#include <string>

class GameScene;

class Pause
{
public:

	//ポーズの画面項目
	enum class CHANGE
	{
		RETRY,
		MENU,
		TITLE,
		MAX
	};	
	
	//フォントサイズ
	static constexpr int FONT_SIZE = 48;
	static constexpr int SELECT_FONT_SIZE = 54;

	//フォント太さ
	static constexpr int FONT_THICK = 3;

	//板画像サイズ
	static constexpr int BOARD_SIZE_X = 297;
	static constexpr int BOARD_SIZE_Y = 345;

	//拡大スピード
	static constexpr float EXPANSION_SPEED = 0.1f;

	//板最大サイズ
	static constexpr float BOARD_SIZE_MAX = 1.0f;

	//ニューレコード描画位置
	static constexpr int NEW_RECODE_POS_X = Application::SCREEN_SIZE_X / 4;
	static constexpr int NEW_RECODE_POS_Y = Application::SCREEN_SIZE_Y / 5;

	//ニューレコード用インターバル
	static constexpr int NEW_RECODE_INTERVAL = 1;

	//揺らす周波数
	static constexpr float AMPLITUDE = 0.3f;

	//揺らす振幅
	static constexpr float FREQUENCY = 5.0f;

	//ポーズUI位置
	static constexpr int PAUSE_UI_POS_X = Application::SCREEN_SIZE_X / 2;
	static constexpr int PAUSE_UI_POS_Y = Application::SCREEN_SIZE_Y / 2- 200;

	//テキストの描画間隔
	static constexpr int TEXT_INTERVAL = static_cast<int>(FONT_SIZE * 1.7f);

	//テキスト描画位置
	static constexpr int TEXT_POS_Y = 250;

	//コンストラクタ
	Pause();

	//デストラクタ
	~Pause();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="parent"></param>親インスタンス
	void Init(GameScene* parent);

	//変数の初期化
	void Reset();

	//更新
	void Update();

	//描画
	void Draw();

	//解放
	void Release();

	//画像の描画
	void NewRecodeDraw();

	/// <summary>
	/// 新記録UI描画の許可
	/// </summary>
	/// <param name="value"></param>許可
	void SetIsNewRecode(const bool value);

	//新記録UI描画許可の確認
	bool IsNewRecode();

private:

	bool isStick_;

	//ポーズUI画像
	int imgPause_;

	//板サイズ率
	float size_;

	//板画像
	int imgBoard_;

	//選択用カウント
	int cnt_;

	//テキスト
	std::string text_[static_cast<int>(CHANGE::MAX)];

	//フォント
	int font_;

	//セレクトフォント
	int sleFont_;

	//画像読み込み
	int imgNewRecode_;

	//新記録の描画許可
	bool isNewRecode_;

	//選択してるステート
	CHANGE state_;

	//インスタンス
	GameScene* game_;	
	
	//テキストの設定
	void SetText();

	//フォントの設定
	void SetFont();

	//選択処理
	void Select();

	//板の拡大
	void BoardExpansion();

	//切り替え処理
	void Change();
};

