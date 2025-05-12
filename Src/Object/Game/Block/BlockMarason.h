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

	//ライン消しの最大値
	static constexpr int LINE_DELETE_MAX = 3;

	//コンストラクタ
	BlockMarason();

	//デストラクタ
	~BlockMarason();

	//衝突更新処理
	void HitUpdate(Vector2 pos) override;

	//リセット
	void Reset(void) override;

	//ステージを作成
	void StageCreate(void) override;

	//ライン削除
	void LineDelete(void) override;

	//高さの更新
	void HeightUpdate();

	//指定した値から現在の高さを調べる
	void CheckHeight(int y) override;

	// 有効な爆発を取得する
	Blast* GetValidBlast(void);

	//ラインを爆発させる
	void BlastLine(int y, int x, int i);

private:

	int count_;
	std::vector<std::vector<int>> fieldNeo_;
	std::vector < std::vector<BLOCK_TYPE>> roleNeo_;
	std::vector<int> decLineHeights_;
};

