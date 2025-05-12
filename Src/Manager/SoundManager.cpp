#include <DxLib.h>      //DXライブラリの使用する
#include "../Application.h"
#include "SoundManager.h"

SoundManager* SoundManager::instance_ = nullptr;//忘れるな！！

//シングルトン化
void SoundManager::CreateInstance(void)
{
	//インスタンスがnullptrなら初期化されたのち生成処理を行う

	if (instance_ == nullptr)
	{
		instance_ = new SoundManager();
	}
	instance_->Init();
}

SoundManager& SoundManager::GetInstance(void)
{
	if (instance_ == nullptr)
	{
		SoundManager::CreateInstance();
	}
	return *instance_;
}

void SoundManager::Init()
{
	std::string data = (Application::PATH_SOUND + "BGM/").c_str();

	//bgmの設定
	bgm_[static_cast<int>(BGM::TITLE)] = LoadSoundMem((data + "Title.mp3").c_str());
	bgm_[static_cast<int>(BGM::MENU)] = LoadSoundMem((data + "Menu.mp3").c_str());
	bgm_[static_cast<int>(BGM::GAME1)] = LoadSoundMem((data + "Game1.mp3").c_str());
	bgm_[static_cast<int>(BGM::GAME2)] = LoadSoundMem((data + "Game2.mp3").c_str());
	bgm_[static_cast<int>(BGM::GAME3)] = LoadSoundMem((data + "Game3.mp3").c_str());
	bgm_[static_cast<int>(BGM::GAME4)] = LoadSoundMem((data + "Game4.mp3").c_str());

	data = (Application::PATH_SOUND + "Effect/").c_str();

	//タイトルの効果音設定
	se_[static_cast<int>(EFFECT_TYPE::MENU)][static_cast<int>(MENU::TITLE_SCENE_CHANGE)]
		= LoadSoundMem((data + "シーンチェンジ2.mp3").c_str());

	//メニューの効果音設定
	se_[static_cast<int>(EFFECT_TYPE::MENU)][static_cast<int>(MENU::MENU_SELECT)]
		= LoadSoundMem((data + "選択.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::MENU)][static_cast<int>(MENU::MENU_CANCEL)]
		= LoadSoundMem((data + "キャンセル.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::MENU)][static_cast<int>(MENU::MENU_DECIDE)]
		= LoadSoundMem((data + "決定.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::MENU)][static_cast<int>(MENU::MENU_SCENE_CHANGE)]
		= LoadSoundMem((data + "シーンチェンジ.mp3").c_str());

	//プレイヤーの効果音設定
	se_[static_cast<int>(EFFECT_TYPE::PLAYER)][static_cast<int>(PLAYER::JUMP)]
		= LoadSoundMem((data + "ジャンプ.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::PLAYER)][static_cast<int>(PLAYER::DEAD)]
		= LoadSoundMem((data + "死亡.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::PLAYER)][static_cast<int>(PLAYER::FALL)]
		= LoadSoundMem((data + "落下.mp3").c_str());

	//ブロックの効果音設定
	se_[static_cast<int>(EFFECT_TYPE::BLOCK)][static_cast<int>(BLOCK::MOVE)]
		= LoadSoundMem((data + "ブロック操作.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::BLOCK)][static_cast<int>(BLOCK::ROTATION)]
		= LoadSoundMem((data + "ブロック回転.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::BLOCK)][static_cast<int>(BLOCK::SET)]
		= LoadSoundMem((data + "ブロック設置.mp3").c_str());

	//ギミックの効果音再生
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::FIRE_BALL)]
		= LoadSoundMem((data + "火の玉生成時.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::FIRE_BALL_HIT)]
		= LoadSoundMem((data + "火の玉着地.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::BLAST)]
		= LoadSoundMem((data + "爆発.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::CREATE_MOON_HIT)]
		= LoadSoundMem((data + "赤い月衝突用.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::CHANGE_MOON_HIT)]
		= LoadSoundMem((data + "青い月衝突用.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::DARK_MOON_HIT)]
		= LoadSoundMem((data + "黒い月衝突用.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::DARK_MOON_RESPAWN)]
		= LoadSoundMem((data + "黒い月出現.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::TEXT)]
		= LoadSoundMem((data + "テキスト表示.mp3").c_str());

	//イベントの効果音設定
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::CLEAR)]
		= LoadSoundMem((data + "クリア音.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::GAME_OVER)]
		= LoadSoundMem((data + "ゲームオーバー.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::START)]
		= LoadSoundMem((data + "開始.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::START_GO_OUT)]
		= LoadSoundMem((data + "テキスト場外.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::SPEEDUP)]
		= LoadSoundMem((data + "足早い.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::SPEEDDOWN)]
		= LoadSoundMem((data + "足遅い.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::HAPPENING)]
		= LoadSoundMem((data + "イベント発生.mp3").c_str());

	//一部効果音の音量設定
	ChangeVolumeSoundMem(VOLUME_MAX * DEFAULT_VOLUME / 100, se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::BLAST)]);

}

void SoundManager::Update()
{
}

void SoundManager::Release()
{
	for (int i = 0; i < static_cast<int>(BGM::MAX); i++)
	{
		DeleteSoundMem(bgm_[i]);
	}

	for (int i = 0; i < static_cast<int>(EFFECT_TYPE::MAX); i++)
	{
		for (int j = 0; j < MAX_EFFECT_TYPE; j++)
		{
			DeleteSoundMem(se_[i][j]);
		}
	}
}

void SoundManager::PlayBgmSound(BGM bgm, int volume, bool topPosFlag)
{
	//音量設定
	ChangeVolumeSoundMem(VOLUME_MAX * volume / 100, bgm_[static_cast<int>(bgm)]);

	PlaySoundMem(bgm_[static_cast<int>(bgm)], DX_PLAYTYPE_LOOP, topPosFlag);
}

void SoundManager::StopBgmSound(BGM bgm)
{
	int ret;
	ret = StopSoundMem(bgm_[static_cast<int>(bgm)]);
	if (ret == -1)
	{
		return;
	}
}

void SoundManager::PlayEffectSound(EFFECT_TYPE type1, int type2)
{
	PlaySoundMem(se_[static_cast<int>(type1)][type2], DX_PLAYTYPE_BACK);
}

void SoundManager::StopEffectSound(EFFECT_TYPE type1, int type2)
{
	StopSoundMem(se_[static_cast<int>(type1)][type2]);
}

SoundManager::SoundManager(void)
{
	for (int i = 0; i < static_cast<int>(BGM::MAX); i++)
	{
		bgm_[i] = 0;
	}

	for (int i = 0; i < static_cast<int>(EFFECT_TYPE::MAX); i++)
	{
		for (int j = 0; j < MAX_EFFECT_TYPE; j++)
		{
			se_[i][j] = 0;
		}
	}
}

SoundManager::SoundManager(const SoundManager& manager)
{
	for (int i = 0; i < static_cast<int>(BGM::MAX); i++) { bgm_[i] = -1; }
	for (int i = 0; i < static_cast<int>(EFFECT_TYPE::MAX); i++)
	{
		for (int j = 0; j < MAX_EFFECT_TYPE; j++)
		{
			se_[i][j] = -1;
		}
	}
}

SoundManager::~SoundManager(void)
{
	delete instance_;
}