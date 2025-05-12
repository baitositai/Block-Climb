#pragma once
#include "BlockBase.h"

class Moon;

class Block5:public BlockBase
{

public:
	//中央描画
	static constexpr int CENTER_DRAW_X = 4;

	//ブロックのセット状態
	enum class STATE
	{
		NONE,			//なし
		NO_SET,
		SET				//ブロックを置く場所
	};

	void Init(LevelManager* parent) override;
	void Update() override;
	void HitUpdate(Vector2 pos) override;
	void Reset(void) override;
	void StageCreate(void) override;
	void LoadStageCsvData(void) override;
	void LoadPositionCsvData(void) override;
	void PutBlockZoneDraw() override;
	void BlockSet(int MinoX,int MinoY,int MinoType_) override;
	
private:

	//ブロック置くゾーン用CSVデータ読み込み
	std::string putZoneCsvData_;

	//CSVデータの格納用配列
	std::vector<std::vector<int>> setBlockField_;	

	//ブロック置くゾーンの状態用配列
	std::vector<std::vector<STATE>> setBlockRole_;	

	//月のインスタンス生成
	Moon* moon_;

};