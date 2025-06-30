#include <Dxlib.h>
#include "../Application.h"
#include "../Common/Scroll.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Common/Data.h"
#include "MenuScene.h"
#include "../Object/Menu/Challenge.h"
#include "../Object/Menu/Manual.h"
#include "../Object/Menu/TagPlay.h"
#include "../Object/Menu/Credit.h"
#include "../Object/Menu/Text.h"
#include "../Object/Game/PlayerBase.h"
#include "../Object/Game/Block/BlockBase.h"
#include "../Object/Game/Block/BlockShower.h"
#include "../Object/Menu/MenuPlayer.h"

MenuScene::MenuScene(void)
{
	challenge_ = nullptr;
	credit_ = nullptr;
	imgBack_ = 0;
	imgPoint_ = 0;
	isStick_ = false;
	manual_ = nullptr;
	menuCnt_ = 0;
	player_ = nullptr;
	scroll_ = nullptr;
	sleState_ = STATE::MARASON;
	state_ = STATE::NONE;
	blockCreateCnt_ = 0.0f;
	tag_ = nullptr;
	text_ = nullptr;
}

MenuScene::~MenuScene(void)
{
}

void MenuScene::Init(void)
{
	//���x���Z���N�g�̓ǂݍ���
	challenge_ = new Challenge();
	challenge_->Init(this);

	//�}�j���A���̓ǂݍ���
	manual_ = new Manual();
	manual_->Init(this);

	//�ΐ�p�Z���N�g�̓ǂݍ���
	tag_ = new TagPlay();
	tag_->Init(this);

	//�e�L�X�g�̓ǂݍ���
	text_ = new Text();
	text_->Init(this);

	//�v���C���[�̓ǂݍ���
	player_ = new MenuPlayer();
	player_->Init(this);

	//�N���W�b�g�̓ǂݍ���
	credit_ = new Credit();
	credit_->Init(this);

	//�摜�ǂݍ���
	Load();
	
	//�ϐ��̏�����
	Reset();
	
	//�w�i�摜�̐ݒ�
	InitBackImage();

	//bgm�̍Đ�
	SoundManager::GetInstance().PlayBgmSound(SoundManager::BGM::MENU, BGM_VOLUME, true);
}

void MenuScene::Update(void)
{
	//�w�i�̏���
	scroll_->Update();

	switch (state_)
	{
	case STATE::SELECT:
		challenge_->Update();
		break;

	case STATE::MANYUAL:
		manual_->Update();
		break;

	case STATE::TAG:
		tag_->Update();
		break;

	case STATE::CREDIT:
		credit_->Update();
		break;

	case STATE::NONE:
		MenuUpdate();
		break;

	default:
		break;
	}

	//�L�����N�^�[�̍X�V
	player_->Update();

	//�u���b�N�X�V����
	BlockUpdate();

}

void MenuScene::Draw(void)
{
	//�w�i�̕`��
	scroll_->Draw();

	//�u���b�N�̕`��
	for (auto block : blocks_)
	{
		block->Draw();
	}

	switch (state_)
	{
	case STATE::SELECT:
		TextBoxDraw();
		challenge_->Draw();
		PointDraw();
		text_->ChallengeText();
		break;

	case STATE::MANYUAL:
		manual_->Draw();
		break;

	case STATE::MARASON:
		break;

	case STATE::TAG:
		tag_->Draw();
		break;

	case STATE::CREDIT:
		credit_->Draw();
		break;

	case STATE::NONE:
		TextBoxDraw();
		text_->MenuText();
		text_->NewRecodeDraw();
		PointDraw();
		break;

	default:
		break;
	}

	if (state_ != STATE::CREDIT) 
{ 
		text_->ButtonUIDraw();
		player_->Draw();
	}
}

void MenuScene::Release(void)
{
	DeleteGraph(imgPoint_);
	DeleteGraph(imgBack_);

	for (int i = 0; i < blocks_.size(); i++)
	{
		blocks_[i]->Release();
		delete blocks_[i];
	}
	credit_->Release();
	delete credit_;
	scroll_->Release();
	delete scroll_;
	player_->Release();
	delete player_;
	text_->Release();
	delete text_;
	tag_->Release();
	delete tag_;
	manual_->Release();
	delete manual_;
	challenge_->Release();
	delete challenge_;
}

void MenuScene::Load(void)
{
	imgBack_ = LoadGraph((Application::PATH_IMAGE + "StageSelect/Brich.png").c_str()); 
	imgPoint_ = LoadGraph((Application::PATH_IMAGE + "StageSelect/Point.png").c_str());
}

void MenuScene::Reset(void)
{
	//�X�e�B�b�N�p����
	isStick_ = false;

	//�I�����Ă���X�e�[�g�������
	sleState_ = STATE::MARASON;

	//�������
	state_ = STATE::NONE;

	//���j���[�J�E���g
	menuCnt_ = static_cast<int>(sleState_);

	//�|�C���g�̏������W
	pointPos_ = GetPointPos(0);

	//�u���b�N�����J�E���g
	blockCreateCnt_ = BLOCK_CREATE_CNT;
}

void MenuScene::InitBackImage()
{
	//�w�i�摜�̃T�C�Y
	Vector2 imgBackSize = { BRICH_SIZE_X, BRICH_SIZE_Y };

	//�w�i�p�̓ǂݍ���
	scroll_ = new Scroll;
	scroll_->Init(imgBack_, imgBackSize, BACK_DRAW_NUM, BACK_SCROLL_SPEED);
}

void MenuScene::MenuUpdate()
{
	auto& ins = InputManager::GetInstance();
	int stickY = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;
	auto& snd = SoundManager::GetInstance();

	//�J�E���g�̃o�b�N�A�b�v��ێ�
	STATE preState = sleState_;

	//�X�e�[�W�̑I������
	if (ins.IsTrgDown(KEY_INPUT_UP) || (stickY < 0 && !isStick_))
	{
		menuCnt_--; TextReset();
		isStick_ = true;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN) || (stickY > 0 && !isStick_))
	{
		menuCnt_++; TextReset(); 
		isStick_ = true;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}

	//�X�e�[�W�I���̐���
	if (menuCnt_ < 0) { menuCnt_ = static_cast<int>(STATE::MANYUAL); }
	if (menuCnt_ > static_cast<int>(STATE::MANYUAL)) { menuCnt_ = 0; }

	//���l����ϊ�
	sleState_ = static_cast<STATE>(menuCnt_);

	//��ԑJ��
	if (ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{ 
		//�X�e�[�g�̕ύX
		state_ = sleState_;

		//�e�L�X�g���Z�b�g
		TextReset(); 

		//�L�����N�^�[�̑ޏo
		SetPlayerState(MenuPlayer::MOVE_STATE::EXIT);

		//���ʉ��Đ�
		if (state_ == STATE::MARASON) 
		{ 
			snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SCENE_CHANGE));
			snd.StopBgmSound(SoundManager::BGM::MENU);
		}
		else { snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_DECIDE)); }
	}
	if (ins.IsTrgDown(KEY_INPUT_RETURN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_CANCEL));
		snd.StopBgmSound(SoundManager::BGM::MENU);
	}

	//�|�C���g���W�̐ݒ�
	for (int i = 0; i < static_cast<int>(STATE::NONE); i++)
	{
		if(i == static_cast<int>(sleState_))
		{
			//���W�ݒ�
			pointPos_ = GetPointPos(i);
		}
	}

	//�X�e�[�g���}���\���̎��A�V�[����؂�ւ���
	if (state_ == STATE::MARASON)
	{
		ChangeGameScene(Data::LEVEL::MARASON);
	}
	if (state_ == STATE::TAG)
	{
		state_ = STATE::NONE;
	}

	//�X�e�B�b�N�̔����߂�
	if (stickY == 0)
	{
		isStick_ = false;
	}
}

void MenuScene::PointDraw()
{
	DrawRotaGraph(pointPos_.x,
		pointPos_.y,
		1.0f,
		0.0f,
		imgPoint_,
		true);
}

void MenuScene::TextBoxDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, TEXT_BOX_ALPHA);

	//�e�L�X�g�`��w�i(��)
	DrawBox(
		0,
		Application::SCREEN_SIZE_Y - TEXT_BOX_SIZE_Y,
		TEXT_BOX_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0x000000,
		true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MenuScene::TextReset()
{
	text_->Reset();
}

void MenuScene::SetPointPos(const Vector2 pos)
{
	pointPos_ = pos;
}

void MenuScene::SetPlayerState(const MenuPlayer::MOVE_STATE state)
{
	player_->ChangeState(state);
}

MenuScene::STATE MenuScene::GetMenuState()
{
	return state_;
}

void MenuScene::ChangeGameScene(const Data::LEVEL level)
{
	//�Q�[�����x����ݒ�
	Data::GetInstance().ChangeLevelData(level);

	//�V�[����ς���
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
}

BlockBase* MenuScene::GetValidBlock()
{
	BlockBase* block = new BlockShower();
	blocks_.push_back(block);
	return block;
}

Vector2 MenuScene::GetPointPos(const int index)
{
	//�`��p�Ԋu
	int interval = static_cast<int>(Text::FONT_SIZE * index * 1.5f);	
	//Y���W������
	int addPosY = 80;
	return { text_->GetMenuTextSize(index) * Text::FONT_SIZE,
		Text::MENU_FIRST_POS_Y + interval + addPosY };
}

void MenuScene::BlockUpdate()
{
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

void MenuScene::SetState(const STATE state)
{
	state_ = state;
}

MenuScene::STATE MenuScene::GetMenuSetState()
{
	return sleState_;
}

Data::LEVEL MenuScene::GetChallengeState()
{
	return challenge_->GetChallengeData();
}