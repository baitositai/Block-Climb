#pragma once
#include <string>
#include "../Application.h"
#include "../Object/Game/PlayerBase.h"
#include "../Object/Game/RabbitText/RabbitText.h"
#include "SceneBase.h"

class BackGround;
class TitleGround;
class TitlePlayer;
class FadeText;
class RabbitText;
class BlockBase;

class TitleScene : public SceneBase
{

public: 
	
	//フォントサイズ
	static constexpr int FONT_SIZE = 32;

	//画像サイズ
	static constexpr int LOGO_SIZE_X = 682;
	static constexpr int LOGO_SIZE_Y = 512;

	//BGMの音量
	static constexpr int BGM_VOLUME = 70;

	//ブロックの生成カウント
	static constexpr float BLOCK_CREATE_CNT = 1.5f;

	//揺らす周波数
	static constexpr float AMPLITUDE = 0.3f;

	//揺らす振幅
	static constexpr float FREQUENCY = 5.0f;

	//テキストカラー
	static constexpr int TEXT_COLOR = 0xffffff;

	//テキストフォントサイズ
	static constexpr int TEXT_FONT_SIZE = 32;

	//テキストフォント太さ
	static constexpr int TEXT_FONT_THICK = 6;

	//タイトルロゴ座標
	static constexpr int LOGO_POS_X = Application::SCREEN_SIZE_X / 2 - LOGO_SIZE_X / 2;
	static constexpr int LOGO_POS_Y = Application::SCREEN_SIZE_Y / 2 - 335;

	//ラビット座標
	static constexpr int RAB_POS_X = 30;
	static constexpr int RAB_POS_Y = Application::SCREEN_SIZE_Y - RabbitText::RABBIT_SIZE_Y;

	//ラビット吹き出し位置
	static constexpr int RAB_SPEECH_POS_X = 40 + RabbitText::RABBIT_SIZE_X;
	static constexpr int RAB_SPEECH_POS_Y = Application::SCREEN_SIZE_Y - RabbitText::SPEECH_SIZE_Y + 5;

	//ラビットテキスト位置
	static constexpr int RAB_TEXT_POS_X = 70 + RabbitText::RABBIT_SIZE_X;
	static constexpr int RAB_TEXT_POS_Y = Application::SCREEN_SIZE_Y - RabbitText::RABBIT_SIZE_Y + 80;	

	//メッセージテキスト位置
	static constexpr int MES_POS_Y = Application::SCREEN_SIZE_Y / 5 * 4;
											
	TitleScene(void);
	~TitleScene(void) override;

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	/// <summary>
	/// テキスト表示確認
	/// </summary>
	/// <param name="value"></param>表示するか否か
	void SetIsText(bool value);

	//ウサギの描画
	void RabbitDraw();

	//ブロックを生成し返す
	BlockBase* GetValidBlock();

	//タイトルメッセージの位置を返す
	static Vector2 GetTitlePosMes(const std::string & mes);

private:

	//フォント
	int font_;

	//ブロック生成用カウント
	float blockCreateCnt_;

	//テキスト表示用
	bool isText_;

	//テキスト座標
	Vector2 textPos_;

	//ロゴ画像の読み込み
	int imgLogo_;

	//タイトル背景
	BackGround* back_;

	//地面
	TitleGround* ground_;

	//プレイキャラクターたち
	TitlePlayer* player_[static_cast<int>(PlayerBase::PLAYER_TYPE::MAX)];

	//フェードテキスト
	FadeText* fadeText_;

	//ウサギ
	RabbitText* rabbit_;

	//ブロック
	std::vector<BlockBase*> blocks_;
	
	//テキスト初期設定
	void InitText();

	//テキスト用更新処理
	void TextUpdate();

	//ブロック用更新処理
	void BlockUpdate();

};
