#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Common/Fader.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Object/Title/TitlePlayer.h"
#include "../Object/Title/TitleGround.h"
#include "../Object/Game/PlayerBase.h"
#include "../Object/Game/Block/BlockBase.h"
#include "../Object/Game/Block/BlockShower.h"
#include "../Object/Game/RabbitText/RabbitTitle.h"
#include "../Object/Game/BackGround.h"
#include "../Object/FadeText.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
	back_ = nullptr;
	fadeText_ = nullptr;
	font_ = 0;
	ground_ = nullptr;
	imgLogo_ = 0;
	isText_ = false;
	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++) { player_[i] = nullptr; }
	rabbit_ = nullptr;
	blockCreateCnt_ = 0;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	//�摜�ǂݍ���
	imgLogo_ = LoadGraph((Application::PATH_IMAGE + "UI/TitleLogo.png").c_str());

	//�L�����N�^�[�̓ǂݍ���
	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++)
	{
		player_[i] = new TitlePlayer;
		player_[i]->Init(this, static_cast<PlayerBase::PLAYER_TYPE>(i));
	}

	//�w�i�ǂݍ���
	back_ = new BackGround;
	back_->Init();

	//�n�ʓǂݍ���
	ground_ = new TitleGround;
	ground_->Init();

	//�E�T�M�ǂݍ���
	rabbit_ = new RabbitTitle;
	rabbit_->Init();

	//BGM�̍Đ�
	SoundManager::GetInstance().PlayBgmSound(SoundManager::BGM::TITLE, BGM_VOLUME, true);
	
	//�e�L�X�g�̏����ݒ�
	InitText();

	//�u���b�N�̐����J�E���g��ݒ�
	blockCreateCnt_ = BLOCK_CREATE_CNT;
}

void TitleScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT);
	int stickX = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;

	//��ʐ؂�ւ��̏���
	if (ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		auto& snd = SoundManager::GetInstance();
		//���ʉ��Đ�
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU,static_cast<int>(SoundManager::MENU::TITLE_SCENE_CHANGE));
		//BGM��~
		snd.StopBgmSound(SoundManager::BGM::TITLE);
		//�V�[����J��
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::MENU);
	}

	//�v���C���[�B�̍X�V����
	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++)
	{
		player_[i]->Update();
	}

	//�w�i����
	back_->Update();

	//�e�L�X�g����
	fadeText_->Update();

	//�E�T�M����
	rabbit_->Update();

	//�e�L�X�g�֌W�̍X�V����
	TextUpdate();

	//�u���b�N�֌W�̍X�V����
	BlockUpdate();
	
}

void TitleScene::Draw(void)
{
	//�A���t�@�l��ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fader::FADE_MAX);

	//�w�i
	back_->Draw();

	//�u���b�N�̕`��
	for (auto & block : blocks_)
	{
		block->Draw();
	}

	//�n��
	ground_->Draw();

	//���S
	DrawGraph(LOGO_POS_X, LOGO_POS_Y, imgLogo_, true);

	//�E�T�M
	RabbitDraw();

	//�v���C���[�`��
	for (int i = 0; i < static_cast<int>(PlayerBase::PLAYER_TYPE::MAX); i++)
	{
		player_[i]->Draw();
	}

	//�t�F�[�h�e�L�X�g
	if (isText_)
	{
		fadeText_->Draw();
	}
}

void TitleScene::Release(void)
{
	DeleteFontToHandle(font_);
	DeleteGraph(imgLogo_);

	for (BlockBase* block : blocks_) {
		if (block) 
		{
			block->Release();
			delete block;
		}
	}
	blocks_.clear();
	rabbit_->Release();
	delete rabbit_;
	fadeText_->Release();
	delete fadeText_;
	ground_->Release();
	delete ground_;
	back_->Release();
	delete back_;
	for (auto* player : player_)
	{
		if (player)
		{
			player->Release();
			delete player;
		}
	}
}

void TitleScene::SetIsText(bool value)
{
	isText_ = value;
}

void TitleScene::RabbitDraw()
{
	Vector2 pos = { RAB_POS_X,RAB_POS_Y };
	rabbit_->RabbitDraw(pos);

	pos = { RAB_SPEECH_POS_X, RAB_SPEECH_POS_Y};
	rabbit_->SpeechDraw(pos);

	pos = { RAB_TEXT_POS_X , RAB_TEXT_POS_Y};
	rabbit_->TextDraw(pos);
}

BlockBase* TitleScene::GetValidBlock()
{
	BlockBase* block = new BlockShower();
	blocks_.push_back(block);
	return block;
}

Vector2 TitleScene::GetTitlePosMes(const std::string & mes)
{
	return { Application::SCREEN_SIZE_X / 2 - static_cast<int>(mes.length() * TEXT_FONT_SIZE / 4),
	MES_POS_Y };
}

void TitleScene::InitText()
{
	//�t�H���g
	font_ = CreateFontToHandle("�x�X�g�e��DOT", FONT_SIZE, TEXT_FONT_THICK);
	
	//���b�Z�[�W
	const std::string mes = "PLEASE SPACE OR B BUTTON !";

	//���W�ʒu
	textPos_ = GetTitlePosMes(mes);

	//�e�L�X�g��\��
	isText_ = false;

	//�t�F�[�h�e�L�X�g
	fadeText_ = new FadeText();

	//�ݒ�
	fadeText_->SetText(font_, TEXT_COLOR, TEXT_FONT_SIZE, textPos_, mes);
}

void TitleScene::TextUpdate()
{
	//�e�L�X�g�̃V�F�C�N����
	Vector2 pos = textPos_;

	//�㉺�h�炵�̏���
	pos = AsoUtility::SinShake(pos, AMPLITUDE, FREQUENCY);
	fadeText_->SetPos(pos);
}

void TitleScene::BlockUpdate()
{
	//�����̃e�L�X�g���\������ĂȂ��Ƃ��͏������s��Ȃ�
	if (!isText_)
	{
		return;
	}

	//�X�e�b�v�X�V
	blockCreateCnt_ -= SceneManager::GetInstance().GetDeltaTime();
	//�����𖞂����ꍇ�u���b�N�𐶐�
	if (blockCreateCnt_ <= 0.0f)
	{
		//�J�E���g��߂�
		blockCreateCnt_ = BLOCK_CREATE_CNT;

		//�u���b�N���󂯎��
		BlockBase* block = GetValidBlock();

		//�u���b�N�𐶐�
		block->Create();
	}

	for (auto it = blocks_.begin(); it != blocks_.end(); )
	{
		//��������u���b�N���R�s�[
		BlockBase* block = *it;

		//�X�V
		block->Update();

		//�����ɒB�����ꍇ
		if (block->IsDelete())
		{
			//������ď���
			block->Release();
			//���������
			delete block;
			//�z�񂩂�|�C���^����菜��
			it = blocks_.erase(it);  
		}
		else
		{
			//���̃u���b�N��
			++it;
		}
	}
}
