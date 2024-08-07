#pragma once
#include <vector>
#include "BlockBase.h"
#include "../Gimic/Blast.h"
#include "../Gimic/FireBall.h"

class BlockMarason :public BlockBase
{
public:

	//クリア条件
	static constexpr int CREAL_LINE = 20;

	//次の爆発を作るまでのクール時間
	static constexpr float COOL_TIME = 10.0f;

	//更新ライン
	static constexpr int UPDATE_LINE = 10;

	void HitUpdate(Vector2 pos) override;
	void Reset(void) override;
	void StageCreate(void) override;
	void LineDelete(void) override;
	void HeightUpdate();
	void CheckHeight(int y) override;

#pragma region 爆発関係
	// 有効な爆発を取得する
	Blast* GetValidBlast(void);

	//ラインを爆発させる
	void BlastLine(int y, int x, int i);
#pragma endregion

private:

	int count_;
	std::vector<std::vector<int>> fieldNeo_;
	std::vector < std::vector<BLOCK_TYPE>> roleNeo_;
	std::vector<int> decLineHeights_;
};

