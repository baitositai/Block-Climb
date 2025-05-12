#pragma once
#include <vector>
#include "BlockBase.h"
#include "../Gimic/Blast.h"

class Block3 :public BlockBase
{
public:

	//クリア条件
	static constexpr int CREAL_LINE = 20;

	//次の爆発を作るまでのクール時間
	static constexpr float COOL_TIME = 10.0f;

	//コンストラクタ
	Block3();

	//デストラクタ
	~Block3();

	//リセット
	void Reset(void) override;

	//ステージ生成
	void StageCreate(void) override;

	//ライン削除
	void LineDelete(void) override;

	// 有効な弾を取得する
	Blast* GetValidBlast(void);

	//ラインを爆発させる
	void BlastLine(int y, int x, int cnt);

	//爆発処理
	void AllDeleteLine() override;

	//ラインをずらす
	void ShiftLine() override;

private:

	std::vector<std::vector<int>> fieldNeo_;
	std::vector<std::vector<BLOCK_TYPE>> roleNeo_;
	std::vector<int> decLineHeights_;
};

