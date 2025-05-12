#pragma once
#include <string>
#include "../../Common/Vector2.h"
#include "../../Common/Data.h"
#include "../../Scene/MenuScene.h"
#include "Challenge.h"

class Text
{
public:

	//初期位置
	static constexpr int MENU_FIRST_POS_X = Application::SCREEN_SIZE_X / 8;
	static constexpr int MENU_FIRST_POS_Y = Application::SCREEN_SIZE_Y / 5;

	static constexpr int EXP_FIRST_POS_X = Application::SCREEN_SIZE_X / 16;
	static constexpr int EXP_FIRST_POS_Y = Application::SCREEN_SIZE_Y - 80;

	//通常
	static constexpr int FONT_SIZE = 60;

	//フォント太さ
	static constexpr int FONT_THICKNESS = 3;

	//選択中
	static constexpr int SELECT_FONT_SIZE = 75;

	//説明用
	static constexpr int EXPLANATION_FONT_SIZE = 32;

	//文字間隔
	static constexpr int FONT_INTERVAL = static_cast<int>(FONT_SIZE * 1.5f);

	//ボーダー
	static constexpr int BORDER = 3;

	//箱サイズ
	static constexpr int BOX_SIZE_X = 320;
	static constexpr int BOX_SIZE_Y = 120;

	//箱位置
	static constexpr int BOX_POS_X = Application::SCREEN_SIZE_X / 2 + 150;
	static constexpr int BOX_POS_Y = 150;

	//新記録テキスト描画位置
	static constexpr int NEW_RECO_TEXT_POS_X = BOX_POS_X + 10;
	static constexpr int NEW_RECO_TEXT_POS_Y = BOX_POS_Y + EXPLANATION_FONT_SIZE;

	//ボタンUIアルファ値
	static constexpr int BUTTON_UI_ALPHA = 150;

	//ボタンUI長さ
	static constexpr int BUTTON_UI_LENGTH = 18 ;

	//ボタンUI用箱座標左上
	static constexpr int BUTTON_UI_BOX_L_TOP_X = Application::SCREEN_SIZE_X;
	static constexpr int BUTTON_UI_BOX_L_TOP_Y = 0;

	//ボタンUI用箱座標右下
	static constexpr int BUTTON_UI_BOX_R_BOTTOM_X = Application::SCREEN_SIZE_X;
	static constexpr int BUTTON_UI_BOX_R_BOTTOM_Y = EXPLANATION_FONT_SIZE + 8;

	//コンストラクタ
	Text();

	//デストラクタ
	~Text();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="parent"></param>親インスタンス
	void Init(MenuScene* parent);

	//変数の初期化
	void Reset();

	//解放
	void Release();

	/// <summary>
	/// テキストのスクロール処理
	/// </summary>
	/// <param name="pos"></param>位置
	/// <param name="length"></param>長さ
	/// <returns></returns>
	Vector2 TextScroll(const Vector2 pos ,const int length);

	/// <summary>
	/// 指定したテキストサイズを返す
	/// </summary>
	/// <param name="index"></param>テキスト番号
	/// <returns></returns>
	int GetMenuTextSize(const int index);

	//新記録の描画
	void NewRecodeDraw();

	//メニューテキスト描画
	void MenuText();

	//チャレンジ用選択テキスト描画
	void ChallengeText();

	//ボタンUI描画
	void ButtonUIDraw();

private:

	//ボタンUIフォント
	int buttonUIFont_;

	//通常フォント
	int normalFont_;

	//選択用テキスト
	int selectFont_;

	//説明用テキスト
	int explanationFont_;

	//新記録用のテキスト
	std::string newRecodeText_;

	//ボタンUIテキスト
	std::string buttonUIText_;

	//メニューテキスト
	std::string menuText_[static_cast<int>(MenuScene::STATE::NONE)];

	//メニュー説明用テキスト
	std::string menuExpText_[static_cast<int>(MenuScene::STATE::NONE)];

	//チャレンジ説明用テキスト
	std::string chlExpText_[static_cast<int>(Data::LEVEL::MAX)];

	//描画用座標
	Vector2 pos_;

	//スクロール用変数
	int cnt_;

	//インスタンス
	MenuScene* menu_;	
	
	//フォントの設定
	void SetFont();

	//テキストの設定
	void TextData(); 

};

