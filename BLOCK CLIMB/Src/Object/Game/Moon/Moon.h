#pragma once
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"

class LevelManager;

class Moon
{
public:

	enum class MOON_TYPE
	{
		GOAL,		//黄色
		CREATE,		//赤
		CHANGE,		//青
		DEAD,		//黒
		MAX
	};

	enum class DARK_MOVE
	{
		STOP,		//停止
		DOWN,		//下へ落ちる
		FADE_BIG,	//大きくなってフェードする
		WIDTH,		//横移動
		DIAGONAL,	//斜め移動
		DIAGONAL_RE	//斜め移動逆
	};

	//ゴールサイズ
	static constexpr int SIZE_X = 100;
	static constexpr int SIZE_Y = SIZE_X;

	//半径
	static constexpr int RADIUS = SIZE_X / 2;

	Moon();
	~Moon();

	void Init(LevelManager* parent);
	virtual void Reset();
	virtual void Update();
	virtual void Draw();
	void Release();
	void Load();

	//判定の設定
	void SetIsMoon(MOON_TYPE type, bool value);

	//黒月用ステートの設定
	void SetDarkMove(DARK_MOVE move);

	//判定を返す
	bool IsMoon(MOON_TYPE type);

	void SetPos(MOON_TYPE type, Vector2F pos);
	void SetFirstPos(MOON_TYPE type, Vector2F pos);

	//座標を返す
	Vector2F GetPos(MOON_TYPE type);

	//サイズを返す
	Vector2 GetSize();

	//黒月の行動ステートを返す
	DARK_MOVE GetDarkMove();

protected:

	//画像
	int images_[static_cast<int>(MOON_TYPE::MAX)];
	
	//描画サイズ
	float drawSize_;

	//月の判定
	bool isMoon_[static_cast<int>(MOON_TYPE::MAX)];

	//黒月用行動ステート
	DARK_MOVE darkState_;

	//座標
	Vector2F pos_[static_cast<int>(MOON_TYPE::MAX)];

	//初期座標
	Vector2F firstPos_[static_cast<int>(MOON_TYPE::MAX)];

	//画像サイズ
	Vector2 size_;

	//インスタンスの生成
	LevelManager* level_;

};

