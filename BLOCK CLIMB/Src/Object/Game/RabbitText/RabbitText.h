#pragma once
#include <ctime>
#include <string>
#include "../../../Common/Vector2.h"

class LevelManager;

class RabbitText
{
public: 

#pragma region 画像サイズ
	//吹き出し画像サイズ
	static constexpr int SPEECH_SIZE_X = 542;
	static constexpr int SPEECH_SIZE_Y = 128;

	//ウサギ画像
	static constexpr int RABBIT_SIZE_X = 160;
	static constexpr int RABBIT_SIZE_Y = 160;
#pragma endregion

	//文字を表示する間隔
	static constexpr float INTERVAL = 0.02f;

	RabbitText();
	~RabbitText();

	void Init();
	virtual void GameInit(LevelManager* parent);
	virtual void Reset();
	virtual void Update();
	virtual void Release();
	
	//フォント設定
	virtual void SetFont();

	//テキスト設定
	virtual void SetText();

	//ウサギの描画
	void RabbitDraw(Vector2 pos);

	//吹き出しの描画
	void SpeechDraw(Vector2 pos);
	
	//テキストの描画
	virtual void TextDraw(Vector2 pos);
	
	virtual void SetTextData(int value);

protected:

	//テキスト構造体
	struct Text
	{
		//現在表示している文字のインデックス
		int index_;

		//テキストの表示を確認
		bool isTexts_;

		//テキスト
		std::string text_;

		//テキスト出現処理中か
		bool isDisPlayingText_;
	};
	
	//テキスト表示の更新
	virtual void UpdateTextDisplayIndex();

	//テキストの表示を消す処理
	virtual void TextOff();

#pragma region フォント関連
	//フォント
	int font_;

	//フォントサイズ
	int fontSize_;
#pragma endregion

#pragma region 文字の出現処理関連

	//文字出現用カウント
	float step_;

	//文字出現スピード
	float speed_;

	//テキストを表示中
	bool isText_;

	// 最後に文字を表示した時間
	clock_t lastTime_;
#pragma endregion

	//文字非表示用カウント
	float offCnt_;

	//座標
	Vector2 pos_;

	//レベルインスタンス
	LevelManager* level_;

private:

	//ウサギ画像
	int imgRabbit_;

	//吹き出し画像
	int imgSpeech_;
};

