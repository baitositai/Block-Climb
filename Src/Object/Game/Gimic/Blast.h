#pragma once
#include <vector>
#include "../../../Common/Vector2.h"

class LevelManager;
class BlockBase;

class Blast
{
public:
	//爆発状態
	enum class STATE
	{
		NONE,
		WAIT,
		BLAST
	};

	//画像分割数
	static constexpr int BLAST_X = 16;
	static constexpr int BLAST_Y = 1;

	//爆発のアニメーション数
	static constexpr int BLAST_ANIM_NUM = BLAST_X * BLAST_Y;

	//画像サイズ
	static constexpr int BLAST_SIZE_X = 1024 / BLAST_X;
	static constexpr int BLAST_SIZE_Y = 87 / BLAST_Y;

	//衝突判定サイズ
	static constexpr int HIT_SIZE = 48;

	//爆発アニメーションスピード
	static constexpr float ANIM_SPEED = 0.3f;

	//爆発アニメーションインデックスオフセット
	static constexpr int BLAST_ANIM_OFFSET = 4;

	Blast(void);								//コンストラクタ
	~Blast(void);								//デストラクタ

	//void Init(LevelManager* parent);			//初期化処理（最初の一回のみ実行)
	void Create(LevelManager* parent, BlockBase* block, Vector2 pos, float coolTime);		// 弾の生成(表示開始座標、弾の進行方向)
	void Update(void);							//更新処理（毎度実行）
	void Draw(void);							//描画処理（毎度実行）
	void Release(void);							//解放処理 (終了時一回のみ実行)

	//座標
	void SetPos(Vector2 pos);

	//爆発座標を返す
	Vector2 GetPos();

	//爆発サイズを返す
	Vector2 GetSize();

	//爆発生成数を返す
	int GetCreateCnt();

	float GetRadius();

	//爆発の状態を返す
	STATE GetState();

private:

	//画像の格納
	int imgBlasts_[BLAST_ANIM_NUM];

	//爆発の状態
	STATE state_;

	//爆発の大きさ
	Vector2 size_;
	float radius_;

	//爆発位置
	Vector2 pos_;

	//爆発のアニメーション用カウンタ
	int blastCntAnim_;

	//表示しているアニメーション値
	int blastIdxAnim_;

	//爆発のアニメーション速度
	float blastSpeedAnim_;

	//爆破の生成数
	float createCnt_;	

	//クール時間
	float coolTime_;

	//インスタンス
	LevelManager* level_;
	BlockBase* block_;
};

