#pragma once
#include "RabbitText.h"

class LevelManager;

class RabbitMarason : public RabbitText
{
public:

	//テキスト総種類数
	static constexpr int MARASON_TEXTS = 13;

	//テキスト総種類数
	static constexpr int EVENT_TEXTS = 5;

	//テキスト総種類数
	static constexpr int TEXT_TYPES = MARASON_TEXTS + EVENT_TEXTS;

	//到達ライン
	static constexpr int ARRIVAL_LINE[MARASON_TEXTS] = {
		1,20,46,60,82,102,115,130,150,175,199,300,500 };

	//テキストのインデックス	
	static constexpr int PLAYER_BUFF_TEXT_INDEX = 13;			//プレイヤーのバフ
	static constexpr int PLAYER_DEBUFF_TEXT_INDEX = 14;			//プレイヤーのデバフ
	static constexpr int FIRE_TEXT_INDEX = 15;					//火の玉
	static constexpr int BLAST_TEXT_INDEX = 16;					//爆発
	static constexpr int BLOCK_FALL_SPEED_UP_TEXT_INDEX = 17;	//ブロックの落下速度アップ

	//コンストラクタ
	RabbitMarason();

	//デストラクタ
	~RabbitMarason();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="parent"></param>親クラスを受け取る
	void Init(LevelManager* parent);

	void Reset() override;					
	void Update() override;					
	void TextDraw(Vector2 pos) override;	
	void InitText() override;	
	
	/// <summary>
	/// テキストに関する値を設定
	/// </summary>
	/// <param name="value"></param>テキストの番号を指定
	void SetTextData(int value);

private:

	//カウント
	float time_;

	//到達ライン
	int arrivalLine_[MARASON_TEXTS];

	//親クラス
	LevelManager* level_;	

	//テキストオフ
	void TextOff()override;
};