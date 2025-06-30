#include <DxLib.h>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Scene/GameScene.h"
#include "Pause.h"

Pause::Pause()
{
	cnt_ = 0;
	font_ = 0;
	game_ = nullptr;
	imgNewRecode_ = 0;
	imgBoard_ = 0;
	imgPause_ = 0;
	isNewRecode_ = false;
	isStick_ = false;
	size_ = 0.0f;
	sleFont_ = 0;
	state_ = CHANGE::MAX;
}

Pause::~Pause()
{
}

void Pause::Init(GameScene* parent)
{
	//�C���X�^���X�擾
	game_ = parent;

	//�摜�ǂݍ���
	imgPause_ = LoadGraph((Application::PATH_IMAGE + "UI/Pause.png").c_str());
	imgBoard_ = LoadGraph((Application::PATH_IMAGE + "UI/Board.png").c_str());
	imgNewRecode_ = LoadGraph((Application::PATH_IMAGE + "UI/NewRecode.png").c_str());

	//����������
	Reset();

	//�e�L�X�g�ݒ�
	SetText();

	//�t�H���g�ݒ�
	SetFont();
}

void Pause::Reset()
{
	size_ = 0;
	cnt_ = 0;
	state_ = static_cast<CHANGE>(cnt_);
	isNewRecode_ = false;
	isStick_ = false;
}

void Pause::Update()
{
	//�̊g�又��
	if (size_ <= BOARD_SIZE_MAX) { BoardExpansion(); }
	//�I������
	else { Select(); }
}

void Pause::Draw()
{
	//�̕`��
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2,
				Application::SCREEN_SIZE_Y / 2, 
				size_,
				0.0f,
				imgBoard_,
				true);

	//�|�[�YUI�̕`��
	if (game_->GetState() == GameScene::STATE::PAUSE)
	{
		Vector2 pPos = { PAUSE_UI_POS_X,PAUSE_UI_POS_Y };

		pPos = AsoUtility::SinShake(pPos, AMPLITUDE, FREQUENCY);

		DrawRotaGraph(pPos.x,
			pPos.y,
			size_,
			0.0f,
			imgPause_,
			true);
	}

	if (size_ >= BOARD_SIZE_MAX)
	{
		for (int i = 0; i < static_cast<int>(CHANGE::MAX); i++)
		{
			int intevel = TEXT_INTERVAL * i;
			int color = 0xffffff;
			int fontType = font_;

			//���W�̐ݒ�
			Vector2 pos = { (Application::SCREEN_SIZE_X / 2) - (static_cast<int>(text_[i].length() * FONT_SIZE) / AsoUtility::HALF_CHAR_DIV),
							TEXT_POS_Y + intevel };

			//�t�H���g�̐ݒ�
			if (i == static_cast<int>(state_))
			{
				color = 0x00ffff;
				fontType = sleFont_;
			}
			//�I���e�L�X�g�̕\��
			DrawStringToHandle(pos.x, pos.y, text_[i].c_str(), color, fontType);
		}
	}
	
}

void Pause::Release()
{
	DeleteFontToHandle(sleFont_);
	DeleteFontToHandle(font_);
	DeleteGraph(imgNewRecode_);
	DeleteGraph(imgBoard_);
	DeleteGraph(imgPause_);
}

void Pause::SetText()
{
	text_[static_cast<int>(CHANGE::RETRY)] = "���g���C";
	text_[static_cast<int>(CHANGE::MENU)] = "���j���[��";
	text_[static_cast<int>(CHANGE::TITLE)] = "�^�C�g����";
}

void Pause::SetFont()
{
	font_ = CreateFontToHandle("�x�X�g�e��DOT", FONT_SIZE, FONT_THICK);
	sleFont_ = CreateFontToHandle("�x�X�g�e��DOT", SELECT_FONT_SIZE, FONT_THICK);
}

void Pause::Select()
{
	InputManager& ins = InputManager::GetInstance();
	SoundManager& snd = SoundManager::GetInstance();
	int stickY = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;

	//�J�E���g�̃o�b�N�A�b�v��ێ�
	CHANGE preState = state_;

	//�X�e�[�W�̑I������
	if (ins.IsTrgDown(KEY_INPUT_UP) || stickY < 0 && !isStick_) 
	{
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
		cnt_--; 
		isStick_ = true;
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN) || stickY > 0 && !isStick_) 
	{
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
		cnt_++; 
		isStick_ = true;
	}

	//�X�e�[�W�I���̐���
	if (cnt_ < 0) { cnt_ = static_cast<int>(CHANGE::TITLE); }
	if (cnt_ >= static_cast<int>(CHANGE::MAX)) { cnt_ = 0; }

	//���l����ϊ�
	state_ = static_cast<CHANGE>(cnt_);

	//��ԑJ��
	if (ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		snd.StopEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::GAME_OVER));
		Change();
	}

	if (stickY == 0) { isStick_ = false; }
}

void Pause::BoardExpansion()
{
	//�̊g��
	size_ += EXPANSION_SPEED;
}

void Pause::NewRecodeDraw()
{
	DrawRotaGraph(
		NEW_RECODE_POS_X,
		NEW_RECODE_POS_Y,
		size_,
		0.0f,
		imgNewRecode_,
		true,
		false);
}

void Pause::SetIsNewRecode(const bool value)
{
	isNewRecode_ = value;
}

bool Pause::IsNewRecode()
{
	return isNewRecode_;
}

void Pause::Change()
{
	auto& snd = SoundManager::GetInstance();
	auto& scnMng = SceneManager::GetInstance();

	switch (state_)
	{
	case CHANGE::RETRY:
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::TITLE_SCENE_CHANGE));
		game_->Retry();
		break;

	case CHANGE::MENU:
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::TITLE_SCENE_CHANGE));
		scnMng.ChangeScene(SceneManager::SCENE_ID::MENU);
		break;

	case CHANGE::TITLE:
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SCENE_CHANGE));
		scnMng.ChangeScene(SceneManager::SCENE_ID::TITLE);
		break;

	default:
		break;
	}	
	
	//���������Ƃ�
	Reset();
}