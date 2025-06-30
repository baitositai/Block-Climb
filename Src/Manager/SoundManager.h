#pragma once
#include <string>

class SoundManager
{
public:

	//BGM���
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

	//���ʉ��̎�ފǗ�
	enum class EFFECT_TYPE
	{
		MENU,
		PLAYER,
		BLOCK,
		GIMIC,
		EVENT,
		MAX
	};

	//���j���[�֌W
	enum class MENU
	{
		TITLE_SCENE_CHANGE,
		MENU_SELECT,
		MENU_DECIDE,
		MENU_CANCEL,
		MENU_SCENE_CHANGE,
		MAX
	};

	//�v���C���[�֌W
	enum class PLAYER
	{
		JUMP,
		FALL,
		DEAD,
		MAX
	};

	//�u���b�N�֌W
	enum class BLOCK
	{
		MOVE,
		ROTATION,
		FALL,
		SET,
		MAX
	};

	//�M�~�b�N�֌W
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

	//�C�x���g�֌W
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

	// ���ʉ����ލő吔
	static constexpr int MAX_EFFECT_TYPE = static_cast<int>(GIMIC::MAX);
	static constexpr int VOLUME_MAX = 255;

	static constexpr int DEFAULT_VOLUME = 70;

	//�C���X�^���X�̐���
	//�V���O���g����
	static void CreateInstance(void);
	static SoundManager& GetInstance(void);

	void Init();
	void Update();
	void Release();

	// BGM�̍Đ�
	void PlayBgmSound(BGM bgm, int volume, bool topPosFlag);

	// BGM�̒�~
	void StopBgmSound(BGM bgm);
	
	//���j���[�֌W�̌��ʉ��Đ�
	void PlayEffectSound(EFFECT_TYPE type1, int type2);

	// ���ʉ���~
	void StopEffectSound(EFFECT_TYPE type1, int type2);

private:

	//BGM�֌W
	int bgm_[static_cast<int>(BGM::MAX)];

	//���ʉ��֌W
	int se_[static_cast<int>(EFFECT_TYPE::MAX)][MAX_EFFECT_TYPE];

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SoundManager(void);
	SoundManager(const SoundManager& manager);
	~SoundManager(void);

	//�V���O���g����
	static SoundManager* instance_;

};

