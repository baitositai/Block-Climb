#include <DxLib.h>      //DX���C�u�����̎g�p����
#include "../Application.h"
#include "SoundManager.h"

SoundManager* SoundManager::instance_ = nullptr;//�Y���ȁI�I

//�V���O���g����
void SoundManager::CreateInstance(void)
{
	//�C���X�^���X��nullptr�Ȃ珉�������ꂽ�̂������������s��

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

	//bgm�̐ݒ�
	bgm_[static_cast<int>(BGM::TITLE)] = LoadSoundMem((data + "Title.mp3").c_str());
	bgm_[static_cast<int>(BGM::MENU)] = LoadSoundMem((data + "Menu.mp3").c_str());
	bgm_[static_cast<int>(BGM::GAME1)] = LoadSoundMem((data + "Game1.mp3").c_str());
	bgm_[static_cast<int>(BGM::GAME2)] = LoadSoundMem((data + "Game2.mp3").c_str());
	bgm_[static_cast<int>(BGM::GAME3)] = LoadSoundMem((data + "Game3.mp3").c_str());
	bgm_[static_cast<int>(BGM::GAME4)] = LoadSoundMem((data + "Game4.mp3").c_str());

	data = (Application::PATH_SOUND + "Effect/").c_str();

	//�^�C�g���̌��ʉ��ݒ�
	se_[static_cast<int>(EFFECT_TYPE::MENU)][static_cast<int>(MENU::TITLE_SCENE_CHANGE)]
		= LoadSoundMem((data + "�V�[���`�F���W2.mp3").c_str());

	//���j���[�̌��ʉ��ݒ�
	se_[static_cast<int>(EFFECT_TYPE::MENU)][static_cast<int>(MENU::MENU_SELECT)]
		= LoadSoundMem((data + "�I��.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::MENU)][static_cast<int>(MENU::MENU_CANCEL)]
		= LoadSoundMem((data + "�L�����Z��.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::MENU)][static_cast<int>(MENU::MENU_DECIDE)]
		= LoadSoundMem((data + "����.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::MENU)][static_cast<int>(MENU::MENU_SCENE_CHANGE)]
		= LoadSoundMem((data + "�V�[���`�F���W.mp3").c_str());

	//�v���C���[�̌��ʉ��ݒ�
	se_[static_cast<int>(EFFECT_TYPE::PLAYER)][static_cast<int>(PLAYER::JUMP)]
		= LoadSoundMem((data + "�W�����v.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::PLAYER)][static_cast<int>(PLAYER::DEAD)]
		= LoadSoundMem((data + "���S.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::PLAYER)][static_cast<int>(PLAYER::FALL)]
		= LoadSoundMem((data + "����.mp3").c_str());

	//�u���b�N�̌��ʉ��ݒ�
	se_[static_cast<int>(EFFECT_TYPE::BLOCK)][static_cast<int>(BLOCK::MOVE)]
		= LoadSoundMem((data + "�u���b�N����.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::BLOCK)][static_cast<int>(BLOCK::ROTATION)]
		= LoadSoundMem((data + "�u���b�N��].mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::BLOCK)][static_cast<int>(BLOCK::SET)]
		= LoadSoundMem((data + "�u���b�N�ݒu.mp3").c_str());

	//�M�~�b�N�̌��ʉ��Đ�
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::FIRE_BALL)]
		= LoadSoundMem((data + "�΂̋ʐ�����.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::FIRE_BALL_HIT)]
		= LoadSoundMem((data + "�΂̋ʒ��n.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::BLAST)]
		= LoadSoundMem((data + "����.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::CREATE_MOON_HIT)]
		= LoadSoundMem((data + "�Ԃ����Փ˗p.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::CHANGE_MOON_HIT)]
		= LoadSoundMem((data + "�����Փ˗p.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::DARK_MOON_HIT)]
		= LoadSoundMem((data + "�������Փ˗p.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::DARK_MOON_RESPAWN)]
		= LoadSoundMem((data + "�������o��.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::GIMIC)][static_cast<int>(GIMIC::TEXT)]
		= LoadSoundMem((data + "�e�L�X�g�\��.mp3").c_str());

	//�C�x���g�̌��ʉ��ݒ�
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::CLEAR)]
		= LoadSoundMem((data + "�N���A��.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::GAME_OVER)]
		= LoadSoundMem((data + "�Q�[���I�[�o�[.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::START)]
		= LoadSoundMem((data + "�J�n.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::START_GO_OUT)]
		= LoadSoundMem((data + "�e�L�X�g��O.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::SPEEDUP)]
		= LoadSoundMem((data + "������.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::SPEEDDOWN)]
		= LoadSoundMem((data + "���x��.mp3").c_str());
	se_[static_cast<int>(EFFECT_TYPE::EVENT)][static_cast<int>(EVENT::HAPPENING)]
		= LoadSoundMem((data + "�C�x���g����.mp3").c_str());

	//�ꕔ���ʉ��̉��ʐݒ�
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
	//���ʐݒ�
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