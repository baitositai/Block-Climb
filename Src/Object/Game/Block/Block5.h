#pragma once
#include "BlockBase.h"

class Moon;

class Block5:public BlockBase
{

public:
	//中央描画
	static constexpr int CENTER_DRAW_X = 4;

	//ミノの初期位置
	static constexpr int MINO_DEFAULT_POS = -500;

	//ブロックのセット状態
	enum class STATE
	{
		NONE,			//なし
		NO_SET,
		SET				//ブロックを置く場所
	};

	//コンストラクタ
	Block5();

	//デストラクタ
	~Block5();

	//初期化
	void Init(LevelManager* parent) override;

	//更新
	void Update() override;
	
	//衝突時の更新
	void HitUpdate(Vector2 pos) override;
	
	//リセット
	void Reset(void) override;
	
	//ステージ生成
	void StageCreate(void) override;

	//ステージのcsvデータの読み込み
	void LoadStageCsvData(void) override;

	//配置エリアのcsvデータ読み込み
	void LoadPositionCsvData(void) override;

	//配置エリアの描画
	void PutBlockZoneDraw() override;

	//ブロックの配置
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