#pragma once
#include "../../Utility/AsoUtility.h"
#include "../../Manager/InputManager.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"


class LevelManager;

class PlayerBase
{
public:
	//列挙型
	//----------------------------------------------
	//プレイヤー種類
	enum class PLAYER_TYPE
	{
		DUDU,
		FROG,
		MAN,
		GUY,
		MAX
	};

	//アニメーション状態
	enum class ANIM_STATE
	{
		IDLE,
		RUN,
		JUMP,
		FALL,
		HIT,
		DIE,
		MAX
	};

	//衝突座標(左右)
	enum class COL_LR
	{
		C,
		L,
		R
	};

	//衝突座標(上下)
	enum class COL_TD
	{
		C,
		T,
		D
	};

	//衝突座標
	enum class COL_LRTD
	{
		C,		//中心
		L,		//左
		R,		//右
		T,		//頭
		D		//足
	};

	//衝突判定の確認
	enum class HIT
	{
		NONE,
		RIGHT,
		LEFT,
		UP,
		DOWN
	};

	//定数
	//------------------------------------------------

#pragma region  画像関連
	//画像サイズ
	static constexpr int SIZE_X = 50;						
	static constexpr int SIZE_Y = 50;						

	//立ちの画像サイズ
	static constexpr int IDLE_SIZE_X = 550;					
	static constexpr int IDLE_SIZE_Y = 50;					

	//走りの画像サイズ
	static constexpr int RUN_SIZE_X = 600;					
	static constexpr int RUN_SIZE_Y = 50;	

	//衝突時の画像サイズ
	static constexpr int HIT_SIZE_X = 350;
	static constexpr int HIT_SIZE_Y = 50;
#pragma endregion

#pragma region  アニメーション関連
	//立ちのアニメーション数
	static constexpr int IDLE_NUM_ANIM = 11;	

	//走りのアニメーション数
	static constexpr int RUN_NUM_ANIM = 12;	
	
	//ダメージのアニメーション数
	static constexpr int HIT_NUM_ANIM = 7;	

#pragma endregion

#pragma region 移動関連
	//加速(accelerator=アクセレレーター)
	static constexpr float MOVE_ACC = 0.25f;	

	//減速
	static constexpr float MOVE_DEC = 0.15f;			

	//移動速度の最大値
	static constexpr float MAX_MOVE_SPEED = 3.5f;			
#pragma endregion

#pragma region ジャンプ関連
	//最大ジャンプ力
	static constexpr float MAX_JUMP_POW = 8.0;

	static constexpr float DEATH_JUMP_POW = 6.0f;		

	//重力
	static constexpr float GRAVITY = 0.25;		

	//ジャンプのフレーム量
	static constexpr float INPUT_JUMP_FRAME = 4.0f;			
#pragma endregion

	//メンバー関数													
	//------------------------------------------------
	PlayerBase(void);									//コンストラクタ
	~PlayerBase(void);									//デストラクタ

	virtual void Init(LevelManager* parent);			//初期化処理（最初の一回のみ実行)
	virtual void Update(void);							//更新処理（毎度実行）
	virtual void Draw(void);							//描画処理（毎度実行）
	bool Release(void);									//解放処理 (終了時一回のみ実行)

	//変数の初期化
	virtual void Reset();

	//画像の読み込み
	void Load(PLAYER_TYPE type);

#pragma region 移動関連
	void ProcessMove();					//プレイヤーの操作	
	void Move();						//移動(実際の座標移動)
	void Accele(float speed);			//加速に関する処理
	void Decelerate(float speed);		//減速に関する処理
#pragma endregion

#pragma region ジャンプ関連
	void AddGravity(void);				//重力をかける
	void ProcessJump(void);
	void Jump(void);					//ジャンプ
	void SetJumpPow(float pow);			//ジャンプ力の設定
#pragma endregion

#pragma region 死亡関連
	void CheckDeath();
	void DeathAnimation();
#pragma endregion

#pragma region 衝突判定	
	bool CollisionHead(void);			//頭の衝突判定
	bool CollisionRight(void);			//右の衝突判定
	bool CollisionLeft(void);			//左の衝突判定
	int CollisionFoot(void);			//足元の衝突判定
#pragma endregion

#pragma region 値を返す
	Vector2F GetPos();
	Vector2 GetColPos(COL_LR lr, COL_TD td);
	Vector2 GetSize();
	bool IsDeath();
#pragma endregion
	
#pragma region 外部からの設定
	void SetPos(Vector2F value);
	void SetState(ANIM_STATE state);
	void SetIsDeath(bool value);
	void SetParam(float speed_, float jumpPow);
#pragma endregion

protected:

#pragma region ステータス関連
	//画像の格納
	int Images_[static_cast<int>(ANIM_STATE::MAX)][RUN_NUM_ANIM];

	//プレイヤーサイズ
	Vector2 size_;			

	//方向
	bool dir_;		

	//スピード
	float speed_;

	//スピード
	float maxSpeed_;

	//角度
	float rot_;

	//座標
	Vector2F pos_;	

	//バックアップ用座標
	Vector2F prePos_;	
#pragma endregion

#pragma region アニメーション関連
	//アニメの状態	
	ANIM_STATE animState_;	

	//アニメカウンター
	int cntAnim_;			

	//アニメの種類の数値
	int numAnim_;		

	//アニメーションスピード
	float animSpeed_;									
#pragma endregion

private:

#pragma region ジャンプ
	float cntJumpInput_;
	bool isJump_;
	float jumpPow_;
	float maxJumpPow_;
#pragma endregion

#pragma region 衝突判定用
	//中心座標(pos_からの相対座標)
	Vector2 hitPos_;	

	//範囲
	Vector2 hitBox_;	

	//衝突判定の確認
	HIT hit_;

	bool hits_[12];

#pragma endregion

	//操作用スティック変数
	Vector2 stick_;

	int deathCnt_;

	bool isDeath_;

	bool fallSound_;

	Vector2F deathPos_;

	//操作主情報
	InputManager::JOYPAD_NO pad_;

	//インスタンス
	LevelManager* level_;

};

