#pragma once
#include <string>

class TitleGround
{
public:

#pragma region  地面関連の定数
	//ブロック画像の分ける数
	static constexpr int GROUND_IMG_NUM_X = 22;
	static constexpr int GROUND_IMG_NUM_Y = 11;
	static constexpr int GROUND_IMG_NUM = GROUND_IMG_NUM_X * GROUND_IMG_NUM_Y;

	//地面チップの1サイズ
	static constexpr int GROUND_SIZE_X = 50;
	static constexpr int GROUND_SIZE_Y = 50;
#pragma endregion

	//CSVデータの幅と高さ
	static constexpr int WIDTH = 26;
	static constexpr int HEIGHT = 3;

	TitleGround();
	~TitleGround();

	void Init();
	void Draw();
	void Release();
	void LoadStageCsvData();

private:
	//画像読み込み用
	int imgGrounds_[GROUND_IMG_NUM];

	//CSVデータの読み込み
	std::string groundCsvDate_;

	//データ格納用配列
	int grounds_[HEIGHT][WIDTH];

};

