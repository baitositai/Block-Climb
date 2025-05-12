#pragma once
#include <string>

class SoundManager
{
public:

	//BGM種類
	enum class BGM
	{
		TITLE,
		MENU,
		GAME1,
		GAME2,
		GAME3,
		GAME4,
		MAX
	};

	//効果音の種類管理
	enum class EFFECT_TYPE
	{
		MENU,
		PLAYER,
		BLOCK,
		GIMIC,
		EVENT,
		MAX
	};

	//メニュー関係
	enum class MENU
	{
		TITLE_SCENE_CHANGE,
		MENU_SELECT,
		MENU_DECIDE,
		MENU_CANCEL,
		MENU_SCENE_CHANGE,
		MAX
	};

	//プレイヤー関係
	enum class PLAYER
	{
		JUMP,
		FALL,
		DEAD,
		MAX
	};

	//ブロック関係
	enum class BLOCK
	{
		MOVE,
		ROTATION,
		FALL,
		SET,
		MAX
	};

	//ギミック関係
	enum class GIMIC
	{
		FIRE_BALL,
		FIRE_BALL_HIT,
		BLAST,
		GOAL_MOON_HIT,
		CHANGE_MOON_HIT,
		CREATE_MOON_HIT,
		DARK_MOON_HIT,
		DARK_MOON_RESPAWN,
		TEXT,
		MAX
	};

	//イベント関係
	enum class EVENT
	{
		START,
		START_GO_OUT,
		CLEAR,
		GAME_OVER,
		HAPPENING,
		SPEEDUP,
		SPEEDDOWN,
		MAX
	};

	// 効果音一種類最大数
	static constexpr int MAX_EFFECT_TYPE = static_cast<int>(GIMIC::MAX);
	static constexpr int VOLUME_MAX = 255;

	static constexpr int DEFAULT_VOLUME = 70;

	//インスタンスの生成
	//シングルトン化
	static void CreateInstance(void);
	static SoundManager& GetInstance(void);

	void Init();
	void Update();
	void Release();

	// BGMの再生
	void PlayBgmSound(BGM bgm, int volume, bool topPosFlag);

	// BGMの停止
	void StopBgmSound(BGM bgm);
	
	//メニュー関係の効果音再生
	void PlayEffectSound(EFFECT_TYPE type1, int type2);

	// 効果音停止
	void StopEffectSound(EFFECT_TYPE type1, int type2);

private:

	//BGM関係
	int bgm_[static_cast<int>(BGM::MAX)];

	//効果音関係
	int se_[static_cast<int>(EFFECT_TYPE::MAX)][MAX_EFFECT_TYPE];

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SoundManager(void);
	SoundManager(const SoundManager& manager);
	~SoundManager(void);

	//シングルトン化
	static SoundManager* instance_;

};

