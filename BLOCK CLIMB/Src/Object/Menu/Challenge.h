#pragma once
#include <string>
#include "../../Common/Data.h"
#include "../../Common/Vector2.h"

class MenuScene;

class Challenge
{
public:

	//ステージ選択配列
	static constexpr int STAGE_X = 3;
	static constexpr int STAGE_Y = 2;

	Challenge(void);
	~Challenge(void);

	void Init(MenuScene* parent);
	void Update(void);
	void Draw(void);
	void Release(void);
	void Load();

	//選択しているデータを返す
	Data::LEVEL GetChallengeData();

private:

	//画像関係
	int imgSle_[static_cast<int>(Data::LEVEL::MAX)];
	int imgPoint_;

	//テキスト
	std::string expText_[static_cast<int>(Data::LEVEL::MAX)];

	//選択しているステージ
	Vector2 sleCnt_;

	//選択してるステージのデータ格納
	Data::LEVEL sleData_;

	//ポイント用座標
	Vector2 pointPos_;

	//インスタンス
	MenuScene* menu_;

	//スクロール
	int scrollCnt_;

	//スティック判定
	bool isStick_;

};

