#include <DxLib.h>
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"
#include "../../../Common/Data.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Utility/Collision.h"
#include "../../../Scene/GameScene.h"
#include "../../../Manager/InputManager.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../BackGround.h"
#include "../Camera/Camera.h"
#include "../Moon/Moon.h"
#include "../Side/SideBase.h"
#include "../Event/Event.h"
#include "LevelManager.h"

LevelManager::LevelManager(void)
{
	gameScene_ = nullptr;
	block_ = nullptr;
	camera_ = nullptr;
	moon_ = nullptr;
	player_ = nullptr;
	backGround_ = nullptr;
	side_ = nullptr;
	event_ = nullptr;
	isGameClear_ = false;
	isGameOver_ = false;
	hitStopCnt_ = 0;
	tmpScreen_ = 0;
}

LevelManager::~LevelManager(void)
{
}

void LevelManager::Init(GameScene* parent)
{
	SetParam();

	gameScene_ = parent;

	camera_ = new Camera();
	camera_->Init(this);

	player_ = new PlayerBase();
	player_->Init(this);

	backGround_ = new BackGround();
	backGround_->Init();

	// �ꎞ�I�ȕ`��̈�
	tmpScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	//����������
	Reset();

	//�e���x�����Ƃɒǉ��̓ǂݍ���
	AddInit();
}

void LevelManager::SetParam()
{
}

void LevelManager::Reset()
{
	hitStopCnt_ = 0;
	isGameClear_ = false;
	isGameOver_ = false;
}

void LevelManager::Update(void)
{
	//�Q�[���I�[�o�[�`�F�b�N
	GameOverCheck();

	//�Q�[���N���A�`�F�b�N
	GameClearCheck();

	block_->Update();
	player_->Update();
	backGround_->Update();
	camera_->Update();
	side_->Update();
	
}

void LevelManager::Draw(void)
{
	backGround_->Draw();
	block_->Draw();
	player_->Draw();
	camera_->Draw();
	side_->Draw();
	//DebagDraw();
}

void LevelManager::Release(void)
{
	backGround_->Release();
	delete backGround_;
	player_->Release();
	delete player_;
	camera_->Release();
	delete camera_;
}

void LevelManager::AddInit()
{
}

void LevelManager::GoalHit()
{
	//�v���C���[���̎擾
	Vector2 pPos = player_->GetPos().ToVector2();
	Vector2 pSize = player_->GetSize();			//�v���C���[��x���W�̔����𔼌a�Ƃ���
	int pRadius = pSize.x / 2;

	//�S�[�����̎擾
	Vector2 mPos = moon_->GetPos(Moon::MOON_TYPE::GOAL).ToVector2();

	if (Collision::IsCollisionCircle(pPos, pRadius, mPos, Moon::RADIUS))
	{
		SetStopCnt(HIT_STOP_CNT);
		isGameClear_ = true;
	}
}

void LevelManager::GameClearCheck()
{
	if (isGameClear_)
	{
		StopBGM();
		gameScene_->ChangeState(GameScene::STATE::CLEAR);
	}
}

void LevelManager::GameOverCheck()
{
	IsCameraRange();

	if (isGameOver_)
	{
		gameScene_->ChangeState(GameScene::STATE::OVER);
	}
}

//�v���C���[�ƃu���b�N�̏Փ˔���
bool LevelManager::IsHitBlocks(Vector2 Pos, Vector2 Size)
{
	//�t�B�[���h�Ƃ̓����蔻��
	if (IsHitField(Pos))
	{
		return true;
	}
	//�~�m�Ƃ̓����蔻��
	if (IsHitMino(Pos , Size))
	{
		return true;
	}
	return false;
}

bool LevelManager::IsHitField(Vector2 Ppos)
{
	//�v���C���[���W���e�g���X�̕`��ʒu������
	Vector2 pPos = { Ppos.x + BlockBase::BLOCK_SIZE_X / 2 - game_Draw_Center_.x,
					Ppos.y + BlockBase::BLOCK_SIZE_Y / 2 };
	
	//���W���t�B�[���h���W�֕ϊ�����
	Vector2 fieldPpos = Field2Pos(pPos);
	
	//�Փ˔���
	if (block_->IsHitBlock(fieldPpos))
	{
		return true;
	}
	return false;
}

bool LevelManager::IsHitMino(Vector2 Ppos ,Vector2 Psize)
{
	//�~�m�̍��W�𓾂�
	Vector2 minoPos = block_->GetMinoPos().ToVector2();

	//�~�m�̎�ނ𓾂�
	int minoType = block_->GetMinoType();

	//�����蔻��p�̃T�C�Y�𓾂�
	Vector2 mSize = block_->GetSize();
	mSize.x = mSize.x / (BlockBase::BLOCK_SIZE_X);
	mSize.y = mSize.y / (BlockBase::BLOCK_SIZE_Y);

	for (int i = 0; i < BlockBase::MINO_HEIGHT; i++)
	{
		for (int j = 0; j < BlockBase::MINO_WIDTH; j++)
		{
			//�~�m�̃u���b�N�̈ʒu���m�F
			if (block_->GetMinoShapes(minoType, j, i) == 1)
			{
				//�u���b�N�̍��W�𓾂�
				Vector2 minoBlockPos = block_->GetMinoBlockPos(minoPos, j, i);

				//�Փ˔���
				if (Collision::IsCollisionRectCenter(Ppos, Psize, minoBlockPos, mSize))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//�~�m�̈ړ��O�̓����蔻��m�F
bool LevelManager::IsPlayerCheck(AsoUtility::DIR value, Vector2 Mino, int MinoType)
{
	////�~�m�̍��W�𓾂�
	//Vector2 minoPos = block_->GetMinoPos().ToVector2();

	////�~�m�̎�ނ𓾂�
	//int minoType = block_->GetMinoType();

	////�v���C���[�T�C�Y�𓾂�
	//Vector3\

	//Vector2 PlayerPosC;
	//Vector2 PlayerPosL;
	//Vector2 PlayerPosR;

	//switch (value)
	//{
	//case AsoUtility::DIR::RIGHT:

	//	minoPos.x += BlockBase::BLOCK_SIZE_X;

	//	//�E�����W
	//	PlayerPosC = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::R, PlayerBase::COL_TD::C));
	//	PlayerPosL = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::R, PlayerBase::COL_TD::T));
	//	PlayerPosR = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::R, PlayerBase::COL_TD::D));
	//	if (IsHitMino(PlayerPosC) ||
	//		IsHitMino(PlayerPosL) ||
	//		IsHitMino(PlayerPosR))
	//	{
	//		return true;
	//	}
	//	break;

	//case AsoUtility::DIR::DOWN:

	//	//�������W
	//	PlayerPosC = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::C, PlayerBase::COL_TD::T));
	//	PlayerPosL = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::L, PlayerBase::COL_TD::T));
	//	PlayerPosR = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::R, PlayerBase::COL_TD::T));
	//	if (IsHitMino(PlayerPosC) ||
	//		IsHitMino(PlayerPosL) ||
	//		IsHitMino(PlayerPosR))
	//	{
	//		return true;
	//	}
	//	break;

	//case AsoUtility::DIR::LEFT:

	//	minoPos.x -= BlockBase::BLOCK_SIZE_X;

	//	//�������W
	//	PlayerPosC = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::L, PlayerBase::COL_TD::C));
	//	PlayerPosL = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::L, PlayerBase::COL_TD::T));
	//	PlayerPosR = Field2Pos(player_->GetColPos(PlayerBase::COL_LR::L, PlayerBase::COL_TD::D));
	//	if (IsHitMino(PlayerPosC) ||
	//		IsHitMino(PlayerPosL) ||
	//		IsHitMino(PlayerPosR))
	//	{
	//		return true;
	//	}
	//	break;

	//default:
	//	break;
	//}
	return false;
}

void LevelManager::IsCameraRange()
{
	if (camera_->IsCameraRange(player_->GetPos().ToVector2(), player_->GetSize()))
	{
		if (!player_->IsDeath())
		{
			SetStopCnt(HIT_STOP_CNT);
			player_->SetIsDeath(true);
			return;
		}

		isGameOver_ = true;
	}

	if (camera_->IsCameraRange(block_->GetMinoPos().ToVector2(), block_->GetSize()))
	{
		if (!player_->IsDeath())
		{
			block_->ResetMino();
		}
	}
}

//�v���C���[�̍��W�����炷����
void LevelManager::PlayerShift(AsoUtility::DIR value)
{
	Vector2F shift = { 0,0 };

	switch (value)
	{

	case AsoUtility::DIR::RIGHT:
		shift = { BlockBase::BLOCK_SIZE_X ,0 };
		break;

	case AsoUtility::DIR::DOWN:
		shift = { 0, BlockBase::BLOCK_SIZE_Y };
		break;

	case AsoUtility::DIR::LEFT:
		shift = { -BlockBase::BLOCK_SIZE_X,0 };
		break;

	default:
		break;
	}

	player_->SetPos(shift);
}

//���W���e�g���X�p���W�ɕϊ�����
Vector2 LevelManager::Field2Pos(Vector2 worldPos)
{
	Vector2 ret;

	int mapX = worldPos.x / BlockBase::BLOCK_SIZE_X;
	int mapY = worldPos.y / BlockBase::BLOCK_SIZE_Y;

	ret.x = mapX;
	ret.y = mapY;

	return ret;
}

//���[���h�p�ɍ��W�̕Ԋ�
Vector2 LevelManager::World2Pos(Vector2 fieldPos)
{
	Vector2 ret;

	int mapX = fieldPos.x * BlockBase::BLOCK_SIZE_X;
	int mapY = fieldPos.y * BlockBase::BLOCK_SIZE_Y;

	ret.x = mapX;
	ret.y = mapY;

	return ret;
}

void LevelManager::DebagDraw()
{
	////�~�m�̍��W
	//Vector2F mPos = block_->GetMinoPos();
	//
	//DrawFormatString(0
	//	, 0
	//	, 0x000000
	//	, "�~�m�̍��W = (%f, %f)"
	//	, mPos);
	//
	////�v���C���[�̍��W
	//Vector2F pPosF = player_->GetPos();
	//
	//DrawFormatString(0, 
	//	16,
	//	0x000000,
	//	"�v���C���[���W=(%f, %f)",
	//	pPosF.x,
	//	pPosF.y);
	//
	////�v���C���[�̃t�B�[���h���W
	//Vector2 pPos = pPosF.ToVector2();
	//pPos = { pPos.x - game_Draw_Center_.x,pPos.y };
	//Vector2 mapPos = Field2Pos(pPos);
	//
	//DrawFormatString(0,
	//	32,
	//	0x000000,
	//	"�v���C���[�}�b�v���W=(%d, %d)",
	//	mapPos.x,
	//	mapPos.y);
	//
	////�J�����̍��W
	//Vector2F cPos = camera_->GetPos();
	//
	//DrawFormatString(0, 48, 0x000000,
	//	"�J�����̍��W=(%.1f, %.1f)",
	//	cPos.x,
	//	cPos.y);
	//
	//DrawCircle
	//(cPos.x,
	//	cPos.y,
	//	50,
	//	0x00ffff,
	//	true);
	//
	////�~�m�̗������x
	//float fallSpeed = block_->GetFallSpeed();
	//
	//DrawFormatString(0, 64, 0x000000,
	//	"�������x=(%.1f)",
	//	fallSpeed);
}

void LevelManager::SetGameClear(bool value)
{
	isGameClear_ = value;
}

void LevelManager::SetGameOver(bool value)
{
	isGameOver_ = value;
}

void LevelManager::SetStopCnt(int cnt)
{
	StopBGM();
	SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::PLAYER, static_cast<int>(SoundManager::PLAYER::DEAD));
	hitStopCnt_ = cnt;
}

void LevelManager::CameraShake()
{
	// �U��
	if (hitStopCnt_ > 0)
	{
		// �`���𗠉�ʂɐݒ�
		SetDrawScreen(DX_SCREEN_BACK);

		// �V�F�C�N�����̌���
		int shake = hitStopCnt_ / HITSTOP_SHAKE_INTERVAL % SHAKE_SCALE;

		// �{���ϊ�
		shake *= SHAKE_SCALE;

		// �I�t�Z�b�g����
		shake -= SHAKE_OFFSET;

		// ���ۂɈړ������鋗���֕ϊ�
		shake *= SHAKE_DISTANCE;

		// �w�肵���I�t�Z�b�g�ʒu�Ɉꎞ�X�N���[����`��i��ʂ�h�炷�j
		DrawGraph(shake, shake, tmpScreen_, true);
	}
}

void LevelManager::NextBlockDraw(Vector2 pos)
{
	Vector2 blockPos = pos;

	block_->NextBlockDraw(blockPos, NEXT_BLOCK_RATE);
}

void LevelManager::ShiftGame()
{
	//�v���C���[���炵
	Vector2F pPos = { 0,BlockBase::BLOCK_SIZE_Y };
	player_->SetPos(pPos);

	//�J�������炵
	Vector2F cPos = camera_->GetPos();
	cPos.y += BlockBase::BLOCK_SIZE_Y;
	camera_->SetPos(cPos);
}

void LevelManager::IconDraw(Vector2 pos)
{
	Vector2 drawPos = pos;

	event_->IconDraw(drawPos);
}

void LevelManager::PlayBGM()
{
	gameScene_->PlayBGM();
}

void LevelManager::StopBGM()
{
	gameScene_->StopBGM();
}

int LevelManager::GetFieldBlockY(int y)
{
	return block_->GetFieldBestBlockY(y);
}

int LevelManager::GetBlockHeight()
{
	return block_->GetNowHeight();
}

int LevelManager::GetBlockCnt()
{
	return block_->GetBlockCount();
}

int LevelManager::GetCntLine()
{
	return block_->GetLineCount();
}

float LevelManager::GetFallSpeed()
{
	return block_->GetFallSpeed();
}

Vector2F LevelManager::GetCameraPos()
{
	return camera_->GetPos();
}

Vector2F LevelManager::GetPlayerPos()
{
	return player_->GetPos();
}

Vector2F LevelManager::GetMinoBlockPos(Vector2F pPos)
{
	Vector2F minoPos = block_->GetMinoPos();

	Vector2F mino = { (pPos.x - minoPos.x - game_Draw_Center_.x) / BlockBase::BLOCK_SIZE_X,
						(pPos.y - minoPos.y - game_Draw_Center_.y) / BlockBase::BLOCK_SIZE_Y, };
	Vector2F minoBlockPos = { mino.x * BlockBase::BLOCK_SIZE_X + minoPos.x,
								mino.y * BlockBase::BLOCK_SIZE_Y + minoPos.y };
	return minoBlockPos;
}

Moon* LevelManager::GetMoonInstans()
{
	return nullptr;
}

Event::EVENT LevelManager::GetEventState()
{
	return event_->GetEvent();
}

Vector2 LevelManager::GetFieldSize()
{
	return fieldSize_;
}

Vector2 LevelManager::GetGroundSize()
{
	return groundSize_;
}

Vector2 LevelManager::GetStageSize()
{
	return stageSize_;
}

Vector2F LevelManager::GetFirstPlayerPos()
{
	return firstPlayerPos_;
}

Vector2F LevelManager::GetFirstCameraPos()
{
	return firstCameraPos_;
}

Vector2 LevelManager::GetGoalPos()
{
	return goalPos_;
}

Vector2 LevelManager::GetGameCenter()
{
	return game_Draw_Center_;
}