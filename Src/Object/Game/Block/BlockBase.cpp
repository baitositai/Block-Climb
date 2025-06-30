#include <DxLib.h>
#include<vector>
#include <iostream>
#include <string>
#include <fstream>
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/InputManager.h"
#include "../../../Manager/SoundManager.h"
#include "../Level/LevelManager.h"
#include "BlockBase.h"
#include "../Gimic/Blast.h"
#include "../Gimic/FireBall.h"


BlockBase::BlockBase()
{
    fallSpeed_ = 0.0f;
    fieldHeight_ = 0;
    fieldWidth_ = 0;
    level_ = nullptr;
    gameHeight_ = 0;
    groundHeight_ = 0;
    groundWidth_ = 0;
    minoType_ = 0;
    resetCnt_ = 0;
    stageHeight_ = 0;
    stageWidth_ = 0;
	nowHeight_ = 0;
	setBlockCnt_ = 0;
	cntLine_ = 0;
	isBlock_ = false;
	isFall_ = false;
	isStick_ = false;
	nextMino_ = 0;
	pad_ = InputManager::JOYPAD_NO::PAD1;
    size_ = { };
	normalFallSpeed_ = 0.0f;
	deleteLine_ = 0;
	isDelete_ = false;

    for (int i = 0; i < BLOCK_IMG_NUM; i++)
    {
        imgBlocks_[i] = 0;
    } 
    
    for (int i = 0; i < GROUND_IMG_NUM; i++)
    {
        imgGrounds_[i] = 0;
    }
}

BlockBase::~BlockBase()
{
}

void BlockBase::Init(LevelManager* parent)
{
    level_ = parent;

    //�����̏��
    pad_ = InputManager::JOYPAD_NO::PAD1;

    //�����Ɋւ��鏉����
    normalFallSpeed_ = FALL_SPEED;
    fallSpeed_ = FALL_SPEED;

    isFall_ = false;

    isBlock_;

    //�X�e�B�b�N�̔���
    isStick_ = false;

    //�u���b�N�T�C�Y
    size_ = { BLOCK_SIZE_X,BLOCK_SIZE_Y };

    //���Z�b�g�J�E���g�̏�����
    resetCnt_ = 0.0f;
  
    //�����~�m�̐ݒ�
    nextMino_ = rand() % static_cast<int>(MINO_TYPE::MAX);

    //�t�B�[���h�̃T�C�Y���擾
    fieldWidth_ = level_->GetFieldSize().x;
    fieldHeight_ = level_->GetFieldSize().y;

    //�n�ʂ̃T�C�Y���擾
    groundWidth_ = level_->GetGroundSize().x;
    groundHeight_ = level_->GetGroundSize().y;

    //�X�e�[�W�S�̂̃T�C�Y���擾
    stageWidth_ = level_->GetStageSize().x;
    stageHeight_ = level_->GetStageSize().y;

    //����
    nowHeight_ = 0;
    gameHeight_ = fieldHeight_;

    //�摜�̓ǂݍ���
    Load();

    //�ϐ��̏�����
    Reset();
    
    //CSV�f�[�^�̓ǂݍ���
    LoadStageCsvData();

    //CSV�f�[�^�̓ǂݍ���(�X�e�[�W2�p)
    LoadPositionCsvData();

    //�t�B�[���h����
    StageCreate();
    
    //�~�m�̏������Z�b�g
    ResetMino();
}

void BlockBase::Update()
{
    //�~�m�𓮂�������
    MoveMino();

    Vector2 mino = minoPos_.ToVector2();
    mino.x -= level_->GetGameCenter().x;
    Vector2 fieldMinoPos = level_->Field2Pos(mino);
    if (fieldMinoPos.y < 0) { fieldMinoPos.y *= -1; }

    //�u���b�N���m�ŏd�Ȃ�����
    if (IsHitField(fieldMinoPos.x, fieldMinoPos.y, minoType_))
    {
        level_->SetStopCnt(LevelManager::HIT_STOP_CNT);
        level_->SetGameOver(true);
    }

    //�~�m�����ɒ�������
    if (IsHitField(fieldMinoPos.x, fieldMinoPos.y + 1, minoType_))
    {
        HitUpdate(fieldMinoPos);
    }

    else
    {
        NoHitUpdate(fieldMinoPos);
    }
}

void BlockBase::HitUpdate(Vector2 pos)
{
    minoPos_.y = pos.y * BLOCK_SIZE_Y;
    resetCnt_++;
    isFall_ = true;

    //�~�m�̏�����
    if (resetCnt_ > SceneManager::DEFAULT_FPS * FIX_TIME)
    {
        isBlock_ = true;

        //�~�m�̌Œ艻
        MinoFixed(pos.x, pos.y, minoType_);

        //�u���b�N�̃Z�b�g(�X�e�[�W2�p)
        BlockSet(pos.x, pos.y, minoType_);

        //���C������(�X�e�[�W4�p)
        LineDelete();

        //�u���ꂽ�u���b�N�̍����̎擾
        CheckHeight(pos.y);

        //�~�m�̏�����
        ResetMino();

        SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::SET));
    }
}

void BlockBase::NoHitUpdate(Vector2 pos)
{
    isFall_ = false;
    //�v���C���[�Ƃ̓����蔻����m�F
    if (level_->IsPlayerCheck(AsoUtility::DIR::DOWN, pos, minoType_))
    {
        //�������Ă����ꍇ�A�v���C���[�̍��W�����炷
        level_->PlayerShift(AsoUtility::DIR::DOWN);
    }
    //�~�m�𗎂Ƃ�����
    minoPos_.y += fallSpeed_;
}

void BlockBase::Draw()
{ 
    Vector2F cameraPos = level_->GetCameraPos();
    Vector2 center = level_->GetGameCenter();

    PutBlockZoneDraw();

    for (int i = 0; i < stageHeight_; ++i)
    {
        for (int j = 0; j < stageWidth_; ++j)
        {
            //�n�ʂ̕`��
            if (stageRole_[i][j] == BLOCK_TYPE::GROUND)
            {
                DrawRotaGraph(center.x + j * GROUND_SIZE_X,
                    i * GROUND_SIZE_Y - cameraPos.y,
                    1.0f,	//�g��
                    0.0f,	//��]
                    imgGrounds_[stageField_[i][j]],
                    true,	//�������
                    false);	//����
            } 
            
            //�Œ�u���b�N�̕`��
            if (stageRole_[i][j] == BLOCK_TYPE::BLOCK)
            {
                //�t�B�[���h�ƌŒ肵���u���b�N�̕`��
                DrawRotaGraph(center.x + j * BLOCK_SIZE_X,
                    i * BLOCK_SIZE_Y - cameraPos.y,
                    1.0f,	//�g��
                    0.0f,	//��]
                    imgBlocks_[stageField_[i][j]],
                    true,	//�������
                    false);	//����
            } 
        }
    }

    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            if (1 == minoShapes_[minoType_][i][j])
            {
                //�~�m�̕`��
                DrawRotaGraph(minoPos_.x + j * BLOCK_SIZE_X,
                    minoPos_.y + i * BLOCK_SIZE_Y - cameraPos.y,
                    1.0f,	//�g��
                    0.0f,	//��]
                    imgBlocks_[minoType_],
                    true,	//�������
                    false);	//����
            }
        }
    }
}

void BlockBase::Release()
{
    for (int i = 0; i < GROUND_IMG_NUM; i++)
    {
        DeleteGraph(imgGrounds_[i]);
    }
    for (int i = 0; i < BLOCK_IMG_NUM; i++)
    {
        DeleteGraph(imgBlocks_[i]);
    }
}

void BlockBase::Load()
{
    //�u���b�N�摜�ǂݍ���
    int ret;
    ret = LoadDivGraph((Application::PATH_BLOCK + "Blocks.png").c_str()
        , BLOCK_IMG_NUM
        , BLOCK_IMG_NUM_X
        , BLOCK_IMG_NUM_Y
        , BLOCK_SIZE_X
        , BLOCK_SIZE_Y
        , &(imgBlocks_[0]));

    //�n�ʉ摜�̓ǂݍ���
    ret = LoadDivGraph((Application::PATH_IMAGE + "Terrain/Terrain.png").c_str()
        , GROUND_IMG_NUM
        , GROUND_IMG_NUM_X
        , GROUND_IMG_NUM_Y
        , GROUND_SIZE_X
        , GROUND_SIZE_Y
        , &(imgGrounds_[0]));

}

//�ϐ��̏�����
void BlockBase::Reset()
{ 
}

//�e�g���X�t�B�[���h�̌`��
void BlockBase::StageCreate()
{   
}

//�~�m�̌Œ艻
void BlockBase::MinoFixed(int MinoX, int MinoY, int MinoType)
{
    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            if (1 == minoShapes_[minoType_][i][j])
            {
                //�u���b�N���Œ�
                stageField_[MinoY + i][MinoX + j] = MinoType;

                //��ނ�ς���
                stageRole_[MinoY + i][MinoX + j] = BLOCK_TYPE::BLOCK;

            }
        }
    }
}

//���C������
void BlockBase::LineDelete()
{
}

//�����蔻��
bool BlockBase::IsHitField(int MinoX, int MinoY, int MinoType)
{
    int minoX = MinoX;
    int minoY = MinoY;

    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            if (minoShapes_[MinoType][i][j] == 1)
            {
                if (stageRole_[minoY + i][minoX + j] != BLOCK_TYPE::NONE)
                {
                    return true;
                }
            }
        }
    }

	return false;
}

//�I�u�W�F�N�g�ƃu���b�N�̏Փ˔���
bool BlockBase::IsHitBlock(Vector2 Pos)
{
    //�u���b�N�Ƃ̏Փ˔���
    if (Pos.x >= 0 && Pos.y >= 0 &&
        Pos.x < stageWidth_ && Pos.y < stageHeight_)
    {
        if (stageRole_[Pos.y][Pos.x] != BLOCK_TYPE::NONE)
        {
            return true;
        }
    }

    return false;
}

//��]�O�̓����蔻��m�F
bool BlockBase::RotationHit(int MinoX, int MinoY, int MinoType, AsoUtility::DIR value)
{
    switch (value)
    {
    case AsoUtility::DIR::RIGHT:

        for (int i = 0; i < MINO_HEIGHT; ++i)
        {
            for (int j = 0; j < MINO_WIDTH; ++j)
            {
                if (minoShapes_[MinoType][(MINO_HEIGHT - 1) - j][i] == 1)
                {
                    if (stageRole_[MinoY + i][MinoX + j] != BLOCK_TYPE::NONE)
                    {
                        return true;
                    }
                }
            }
        }

        break;

    case AsoUtility::DIR::LEFT:

        for (int i = 0; i < MINO_HEIGHT; ++i)
        {
            for (int j = 0; j < MINO_WIDTH; ++j)
            {
                if (minoShapes_[MinoType][j][MINO_HEIGHT - 1 - i]==1)
                {
                    if (stageRole_[MinoY + i][MinoX + j] != BLOCK_TYPE::NONE)
                    {
                        return true;
                    }
                }
            }
        }

        break;

    default:
        break;
    }

    return false;

}

void BlockBase::DeleteBlock(int y, int x)
{
    //���W�̕ϊ�
    Vector2 mapPos = {(x - level_->GetGameCenter().x) / BLOCK_SIZE_X,
                      (y - level_->GetGameCenter().y) / BLOCK_SIZE_Y};
    
    //�u���b�N�̏���
    stageRole_[mapPos.y][mapPos.x] = BLOCK_TYPE::NONE;
}

void BlockBase::ShiftLine()
{
}

void BlockBase::CheckHeight(int y)
{    
    int height = y;
    for (int i = 0; i < MINO_HEIGHT; i++)
    {
        //�s���ƂɃu���b�N�����邩�̊m�F
        bool flag = true;
        for (int j = 0; j < MINO_WIDTH; j++)
        {
            //����ꍇ
            if (minoShapes_[minoType_][i][j] == 1)
            {
                //�����̎��s��������
                flag = false;
                break;
            }
        }
        if (flag == false)
        {
            //for�����甲����
            break;
        }
        else
        {
            //������1���炷
            height++;
        }
    }

    //�������������v�Z
    height = fieldHeight_ - height;

    //�������X�V���ꂽ�ꍇ
    if (nowHeight_ < height)
    {
        //���݂̍������X�V
        nowHeight_ = height;
    }
}

void BlockBase::NextBlockDraw(Vector2 pos ,float expansion)
{
    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            if (1 == drawMinoShapes_[nextMino_][i][j])
            {
                DrawRotaGraph(pos.x - BLOCK_SIZE_X + j * BLOCK_SIZE_X * expansion,
                    pos.y + i * BLOCK_SIZE_Y * expansion,
                    expansion,	//�g��
                    0.0f,	//��]
                    imgBlocks_[nextMino_],
                    true,	//�������
                    false);	//����
            }
        }
    }
}

void BlockBase::ChangeNextBlock()
{
    nextMino_ += 1;
    if (nextMino_ >= static_cast<int>(MINO_TYPE::MAX)) { nextMino_ = 0; }
}

void BlockBase::Create()
{
}

void BlockBase::AllDeleteLine()
{
}

void BlockBase::SetFallSpeed(float speed)
{
    fallSpeed_ = speed;
    normalFallSpeed_ = speed;
}

//�~�m�̃��Z�b�g
void BlockBase::ResetMino()
{
    //�~�m�̎��
    minoType_ = nextMino_;

    //�����_���Ń~�m�̎�ނ����߂�
    int num = rand() % static_cast<int>(MINO_TYPE::MAX);

    //�~�m�̏������W
    Vector2F cameraPos = level_->GetCameraPos();
    float width = fieldWidth_;
    minoPos_ = { level_->GetGameCenter().x + width / 2 * BLOCK_SIZE_X ,
                cameraPos.y };

    //���̃~�m�̊i�[
    nextMino_ = num;

    isFall_ = false;

    resetCnt_ = 0.0f;
}

//�~�m�̑��쏈��
void BlockBase::MoveMino()
{
    auto& ins = InputManager::GetInstance();
    auto& snd = SoundManager::GetInstance();
    int stickX = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
    int stickY = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;

    //���ɂ��낷
    if ((ins.IsNew(KEY_INPUT_S) || 
        stickY > 0 )&&
        isFall_ == false)
    {
        fallSpeed_ = FALL_SPEED_UP;
    }
    else if(isFall_ == false)
    {
        fallSpeed_ = normalFallSpeed_;
        
    }
    else
    {
        fallSpeed_ = 0.0f;
    }

    Vector2 mino = minoPos_.ToVector2();
    mino.x -= level_->GetGameCenter().x;
    Vector2 fieldMinoPos = level_->Field2Pos(mino);

    //���ɓ�����
    if (ins.IsTrgDown(KEY_INPUT_A) ||
        (stickX < 0 && !isStick_))
    {
        isStick_ = true;
        if (!IsHitField(fieldMinoPos.x - 1, fieldMinoPos.y, minoType_))
        {
            if (level_->IsPlayerCheck(AsoUtility::DIR::LEFT, fieldMinoPos, minoType_))
            {
                level_->PlayerShift(AsoUtility::DIR::LEFT);
            } 
            snd.PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::MOVE));
            minoPos_.x -= BLOCK_SIZE_X;
        }
    }

    //�E�ɓ�����
    if (ins.IsTrgDown(KEY_INPUT_D) ||
        (stickX > 0 && !isStick_))
    {
        isStick_ = true;
        if (!IsHitField(fieldMinoPos.x + 1, fieldMinoPos.y, minoType_))
        {
            if (level_->IsPlayerCheck(AsoUtility::DIR::RIGHT, fieldMinoPos, minoType_))
            {
                level_->PlayerShift(AsoUtility::DIR::RIGHT);
                
            }
            snd.PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::MOVE));
            minoPos_.x += BLOCK_SIZE_X;
        }
    }
   
    //�E��]
    if (ins.IsTrgDown(KEY_INPUT_E) ||
        ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::R_TRIGGER))
    {
        if (!RotationHit(fieldMinoPos.x, fieldMinoPos.y, minoType_, AsoUtility::DIR::RIGHT))
        {
            ArrayRotation(minoType_, AsoUtility::DIR::RIGHT);
            snd.PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::ROTATION));
        }
    }

    //����]
    if (ins.IsTrgDown(KEY_INPUT_Q) ||
        ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::L_TRIGGER))
    {
        if (!RotationHit(fieldMinoPos.x, fieldMinoPos.y, minoType_, AsoUtility::DIR::LEFT))
        {
            ArrayRotation(minoType_, AsoUtility::DIR::LEFT);
            snd.PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::ROTATION));
        }
    }

    //�X�e�B�b�N�̔����߂�
    if (stickX == 0)
    {
        isStick_ = false;
    }
}

//��]����
void BlockBase::ArrayRotation(int type, AsoUtility::DIR value)
{
    //��]�������̂�������p
    char array[MINO_HEIGHT][MINO_WIDTH] = { 0 };
    
    switch (value)
    {
    case AsoUtility::DIR::RIGHT:

        for (int i = 0; i < MINO_HEIGHT; ++i)
        {
            for (int j = 0; j < MINO_WIDTH; ++j)
            {
                array[i][j] = minoShapes_[type][(MINO_HEIGHT - 1) - j][i];
            }
        }

        break;
    case AsoUtility::DIR::LEFT:

        for (int i = 0; i < MINO_HEIGHT; ++i)
        {
            for (int j = 0; j < MINO_WIDTH; ++j)
            {
                array[i][j] = minoShapes_[type][j][MINO_HEIGHT - 1 - i];
            }
        }

        break;
    default:
        break;
    }

    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            minoShapes_[type][i][j] = array[i][j];
        }
    }
}

//�O���t�@�C������X�e�[�W��CSV�f�[�^��ǂݍ���
void BlockBase::LoadStageCsvData(void)
{
    //�t�@�C���̏���
    std::ifstream ifs = std::ifstream(groundCsvDate_);
    if (!ifs)
    {
        OutputDebugString("�X�e�[�W��ifstream�������s\n");
        return;
    }

    //�񎟌��z��̏ꏊ���w��p
    int x = 0;
    int y = 0;

    std::string line;					//1�s�̃f�[�^���i�[����̈�
    while (getline(ifs, line))
    {
        //Split�֐��̖߂�l�󂯎��p�ϐ�
        std::vector<std::string> strSplit; // 1�s��1�����̓��I�z��ɕ���
        strSplit = AsoUtility::Split(line, ',');

        int chipNo;

        //���������f�[�^���}�b�v�z��Ɋi�[����
        for (int x = 0; x < strSplit.size(); x++)
        {
            chipNo = stoi(strSplit[x]);
            stageField_[fieldHeight_ + y][x] = chipNo;
        }
        y++;
    }
}

//�`�b�v�ԍ���Ԃ�
int BlockBase::GetChipNo(Vector2 mapPos)
{
    return stageField_[mapPos.y][mapPos.x];
}

void BlockBase::LoadPositionCsvData()
{
}

void BlockBase::BlockSet(int MinoX, int MinoY, int MinoType_)
{
}

void BlockBase::PutBlockZoneDraw()
{
}

//�n�ʂ̌`��
void BlockBase::CreateGround()
{
    //�����ŗ��p����}�b�v�z�������������
    ClearUsedMap();
}

//�g�p�}�b�v�̏�����
void BlockBase::ClearUsedMap(void)
{
    for (int y = fieldHeight_; y < fieldHeight_ + groundHeight_; y++)
    {
        for (int x = 0; x < groundWidth_; x++)
        {
            stageField_[y][x] = -1;
        }
    }
}

int BlockBase::GetMinoShapes(int type, int x, int y)
{
    return minoShapes_[type][y][x];
}

//�t�B�[���h�̒l��Ԃ�
int BlockBase::GetField(Vector2 value)
{
    return stageField_[value.y][value.x];
}

//�~�m�̒l��Ԃ�
Vector2F BlockBase::GetMinoPos()
{
    return minoPos_;
}

std::vector<Blast*> BlockBase::GetBlast(void)
{
    return blasts_;
}

std::vector<FireBall*> BlockBase::GetFireBall()
{
    return fire_;
}

Vector2 BlockBase::GetSize()
{
    return size_;
}

Vector2 BlockBase::GetMinoBlockPos(Vector2 Pos,int x, int y)
{
   Vector2 pos = { Pos.x + BLOCK_SIZE_X * x,
                    Pos.y + BLOCK_SIZE_Y * y };
   return pos;
}

int  BlockBase::GetFieldBestBlockY(int y)
{
    int maxY = y;

    for (int i = y - 1; i > 0; i--)
    {
        for (int j = 1; j < fieldWidth_ - 1; j++)
        {
            if (stageRole_[i][j] == BLOCK_TYPE::BLOCK)
            {
                maxY = i;
                break;
            }
        }
        if(stageRole_[i][fieldWidth_ - 1] != BLOCK_TYPE::BLOCK)
        {
            break;
        }
    }

     return maxY;
}

//�~�m�̎�ނ�Ԃ�
int BlockBase::GetMinoType()
{
    return minoType_;
}

int BlockBase::GetNowHeight()
{
    return nowHeight_;
}

float BlockBase::GetFallSpeed()
{
    return fallSpeed_;
}

int BlockBase::GetBlockCount()
{
    return setBlockCnt_;
}

int BlockBase::GetLineCount()
{
    return cntLine_;
}

bool BlockBase::IsBlock()
{
    return isBlock_;
}

bool BlockBase::IsDelete()
{
    return isDelete_;
}