#pragma once
#include <string>

class GameScene;

class SceneSelect
{
public:

	enum class CHANGE
	{
		RETRY,
		//STAGE_SELECT,
		MENU,
		TITLE,
		MAX
	};	
	
	//フォントサイズ
	static constexpr int FONT_SIZE = 48;
	static constexpr int SELECT_FONT_SIZE = 54;

	//板画像サイズ
	static constexpr int BOARD_SIZE_X = 297;
	static constexpr int BOARD_SIZE_Y = 345;

	//拡大スピード
	static constexpr float EXPANSION_SPEED = 0.1f;

	//板最大サイズ
	static constexpr float BOARD_SIZE_MAX = 1.0f;

	SceneSelect();
	~SceneSelect();

	void Init(GameScene* parent);
	void Reset();
	void Update();
	void Draw();
	void Release();

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

	//画像の描画
	void NewRecodeDraw();

	//描画の許可
	void SetIsNewRecode(bool value);

	//許可の確認
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
};

