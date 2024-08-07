#pragma once
#include <string>
#include "../../Common/Vector2.h"
#include "../../Common/Data.h"
#include "../../Scene/MenuScene.h"
#include "Challenge.h"

class Text
{
public:

#pragma region 初期位置
	static constexpr int MENU_FIRST_POS_X = Application::SCREEN_SIZE_X / 8;
	static constexpr int MENU_FIRST_POS_Y = Application::SCREEN_SIZE_Y / 5;

	static constexpr int EXP_FIRST_POS_X = Application::SCREEN_SIZE_X / 16;
	static constexpr int EXP_FIRST_POS_Y = Application::SCREEN_SIZE_Y - 80;
#pragma endregion

#pragma region フォントサイズ
	//通常
	static constexpr int FONT_SIZE = 60;
	//選択中
	static constexpr int SELECT_FONT_SIZE = 75;
	//説明用
	static constexpr int EXPLANATION_FONT_SIZE = 32;
#pragma endregion

	Text();
	~Text();

	void Init(MenuScene* parent);
	void Reset();
	void Release();

	//フォントの設定
	void SetFont();

	//テキストの設定
	void TextData(); 

	//ボタンUI描画
	void BottanUIDraw();

	//新記録の描画
	void NewRecodeDraw();

	//メニューテキスト描画
	void MenuText();

	//チャレンジ用選択テキスト描画
	void ChallengeText();

	//テキストスクロール処理
	Vector2 TextScroll(Vector2 pos ,int length);

	//メニューテキストのサイズを得る
	int GetMenuTextSize(int i);

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
};

