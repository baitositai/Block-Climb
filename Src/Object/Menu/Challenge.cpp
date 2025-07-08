#include <Dxlib.h>
#include "../../Application.h"
#include "../../Common/Scroll.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Common/Data.h"
#include "../../Scene/MenuScene.h"
#include "Challenge.h"

Challenge::Challenge()
{
	imgPoint_ = 0;
	for (int i = 0; i < static_cast<int>(Data::LEVEL::MAX); i++) { imgSle_[i] = 0; }
	pointPos_ = { 0,0 };
	sleCnt_ = { 0,0 };
	scrollCnt_ = 0;
	sleData_ = Data::LEVEL::MAX;
	isStick_ = false;
	menu_ = nullptr;
}

Challenge::~Challenge()
{
}

void Challenge::Init(MenuScene* parent)
{
	menu_ = parent;

	Load();
	
	//���W�̐ݒ�
	pointPos_ = { 0,0 };

	//�F�̐ݒ�
	sleCnt_ = { 0,0 };

	//�X�e�B�b�N����
	isStick_ = false;
}

void Challenge::Update()
{
	Data::LEVEL preData = sleData_;
	auto& ins = InputManager::GetInstance();
	auto& snd = SoundManager::GetInstance();
	int stickX = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
	int stickY = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;

	//�X�e�[�W��I�ԏ���	
	if (ins.IsTrgDown(KEY_INPUT_RIGHT) || (stickX > 0 && !isStick_))
	{
		isStick_ = true;
		sleCnt_.x++;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}
	if (ins.IsTrgDown(KEY_INPUT_LEFT) || (stickX < 0 && !isStick_))
	{ 
		sleCnt_.x--; 
		isStick_ = true;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}
	if (ins.IsTrgDown(KEY_INPUT_UP) || (stickY < 0 && !isStick_)) 
	{
		sleCnt_.y--;
		isStick_ = true;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}
	if (ins.IsTrgDown(KEY_INPUT_DOWN) || (stickY > 0 && !isStick_))
	{ 
		sleCnt_.y++; 
		isStick_ = true;
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SELECT));
	}

	//�X�e�[�W�I���̐���
	if (sleCnt_.x < 0) { sleCnt_.x = STAGE_X - 1; }
	if (sleCnt_.x > STAGE_X - 1) { sleCnt_.x = 0; }
	if (sleCnt_.y < 0) { sleCnt_.y = STAGE_Y - 1; }
	if (sleCnt_.y > STAGE_Y - 1) { sleCnt_.y = 0; }

	//���l����ϊ�
	sleData_ = static_cast<Data::LEVEL>(sleCnt_.x + sleCnt_.y * STAGE_X);

	//����
	if (ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		menu_->ChangeGameScene(sleData_);
		snd.StopBgmSound(SoundManager::BGM::MENU);
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_SCENE_CHANGE));
	}

	//���j���[�֖߂�
	if (ins.IsTrgDown(KEY_INPUT_RETURN) ||
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		menu_->SetState(MenuScene::STATE::NONE); 
		menu_->SetPlayerState(MenuPlayer::MOVE_STATE::ADMISSION);
		menu_->TextReset(); 
		snd.PlayEffectSound(SoundManager::EFFECT_TYPE::MENU, static_cast<int>(SoundManager::MENU::MENU_CANCEL));
	}

	//�e�L�X�g�f�[�^�̐؂�ւ�
	if (sleData_ != preData)
	{
		menu_->TextReset();
	}

	//�X�e�B�b�N�����߂�
	if (stickX == 0 && stickY == 0)
	{
		isStick_ = false;
	}
}

void Challenge::Draw()
{
	for (int i = 0; i < static_cast<int>(Data::LEVEL::MAX); i++)
	{
		//�`��ʒu�̐ݒ�
		Vector2 pos;
		if (i < static_cast<int>(Data::LEVEL::MAX) / 2)
		{
			pos = { SLE_UIS_UP_X * (i + 1),
				   SLE_UIS_UP_Y };
		}
		else
		{
			pos = { SLE_UIS_DOWN_X * (i - static_cast<int>(Data::LEVEL::MAX) / 2 + 1),
				   SLE_UIS_DOWN_Y };
		}

		//�I�����Ă��Ȃ��̂�h�炷
		if (i != static_cast<int>(sleData_))
		{
			//�㉺�h�炵�̏���
			pos = AsoUtility::SinShake(pos, AMPLITUDE, FREQUENCY);
		}

		//�摜�̕`��
		DrawRotaGraph(pos.x,
			pos.y,
			SLE_IMG_RATE,
			0.0f,
			imgSle_[i],
			true);

		//�|�C���g���W�̐ݒ�
		if (i == static_cast<int>(sleData_))
		{
			//���W�ݒ�
			Vector2 pointPos = { pos.x + POINT_LOCAL_POS,
								 pos.y + POINT_LOCAL_POS };
			menu_->SetPointPos(pointPos);
			//�`���MenuScene�ɂ�
		}
	}
}

void Challenge::Release()
{
	DeleteGraph(imgPoint_);
	for (int i = 0; i < static_cast<int>(Data::LEVEL::MAX); i++)
	{
		DeleteGraph(imgSle_[i]);
	}
	
}

void Challenge::Load()
{
	//�摜�ǂݍ���
	std::string path = Application::PATH_IMAGE + "StageSelect/";
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL1)] = LoadGraph((path + "Stage1.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL2)] = LoadGraph((path + "Stage2.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL3)] = LoadGraph((path + "Stage3.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL4)] = LoadGraph((path + "Stage4.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL5)] = LoadGraph((path + "Stage5.png").c_str());
	imgSle_[static_cast<int>(Data::LEVEL::LEVEL6)] = LoadGraph((path + "Stage6.png").c_str());
}

Data::LEVEL Challenge::GetChallengeData()
{
	return sleData_;
}
