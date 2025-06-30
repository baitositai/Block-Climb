#pragma once
#include <ctime>
#include <string>
#include <vector>
#include "../../../Common/Vector2.h"

class RabbitText
{
public: 

	//吹き出し画像サイズ
	static constexpr int SPEECH_SIZE_X = 542;
	static constexpr int SPEECH_SIZE_Y = 128;

	//ウサギ画像
	static constexpr int RABBIT_SIZE_X = 160;
	static constexpr int RABBIT_SIZE_Y = 160;

	//文字を表示する間隔
	static constexpr float INTERVAL = 0.02f;

	//フォントサイズ
	static constexpr int FONT_SIZE = 32;

	//フォント太さ
	static constexpr int FONT_THICK = 6;

	//テキスト非表示カウント
	static constexpr int TEXT_OFF_CNT = 5;

	//コンストラクタ
	RabbitText();

	//デストラクタ
	~RabbitText();

	//初期化
	void Init();

	//リセット
	virtual void Reset();

	//更新
	virtual void Update() = 0;

	//解放
	virtual void Release();
	
	//フォント設定
	virtual void InitFont();

	//テキスト設定
	virtual void InitText() = 0;

	/// <summary>
	/// ウサギの描画
	/// </summary>
	/// <param name="pos"></param>位置
	void RabbitDraw(Vector2 pos);

	/// <summary>
	/// 吹き出しの描画
	/// </summary>
	/// <param name="pos"></param>位置
	void SpeechDraw(Vector2 pos);
	
	/// <summary>
	/// テキストの描画
	/// </summary>
	/// <param name="pos"></param>描画位置を受け取る
	virtual void TextDraw(Vector2 pos) = 0;

protected:

	//テキストに関する情報
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
	//フォント
	int font_;

	//フォントサイズ
	int fontSize_;

	//文字出現用カウント
	float step_;

	//文字出現スピード
	float speed_;

	//テキストを表示中
	bool isText_;

	// 最後に文字を表示した時間
	clock_t lastTime_;

	//文字非表示用カウント
	float offCnt_;

	//座標
	Vector2 pos_;

	//テキスト呼び出し値
	int textData_;

	//テキスト種類
	std::vector<Text> type_;	
	
	//テキスト表示の更新
	void UpdateTextDisplayIndex();

private:

	//ウサギ画像
	int imgRabbit_;

	//吹き出し画像
	int imgSpeech_;	
	
	//テキストの表示を消す処理
	virtual void TextOff() = 0;
};