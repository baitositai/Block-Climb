#include <fstream>
#include "Block2.h"
#include "../../../Manager/SceneManager.h"
#include "../Level/LevelManager.h"
#include "../Moon/Moon.h"


Block2::Block2()
{
    moon_ = nullptr;
}

Block2::~Block2()
{
}

void Block2::Init(LevelManager* parent)
{
    level_ = parent;

    //�����Ɋւ��鏉����
    fallSpeed_ = FALL_SPEED;

    isFall_ = false;

    //�u���b�N�T�C�Y
    size_ = { BLOCK_SIZE_X,BLOCK_SIZE_Y };

    //���Z�b�g�J�E���g�̏�����
    resetCnt_ = 0.0f;

    //����
    nowHeight_ = 0;

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
}

void Block2::Update()
{
    if (!moon_->IsMoon(Moon::MOON_TYPE::CREATE))
    {
        return;
    }
        
    //�~�m�𓮂�������    
    MoveMino();

    Vector2 mino = minoPos_.ToVector2();
    mino.x -= level_->GetGameCenter().x;
    Vector2 fieldMinoPos = level_->Field2Pos(mino);
    /*if (fieldMinoPos.y < 0) { fieldMinoPos.y *= -1; }*/

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

void Block2::HitUpdate(Vector2 pos)
{
    minoPos_.y = pos.y * BLOCK_SIZE_Y;
    resetCnt_++;
    isFall_ = true;

    //�~�m�̏�����
    if (resetCnt_ > SceneManager::DEFAULT_FPS * FIX_TIME)
    {
        //�~�m�̌Œ艻
        MinoFixed(pos.x, pos.y, minoType_);

        //�u���b�N�̃Z�b�g(�X�e�[�W2�p)
        BlockSet(pos.x, pos.y, minoType_);

        //���C������(�X�e�[�W4�p)
        LineDelete();

        //�u���ꂽ�u���b�N�̍����̎擾
        CheckHeight(pos.y);

        moon_->SetIsMoon(Moon::MOON_TYPE::CREATE, false);
    }
}

void Block2::Reset(void)
{
    setBlockCnt_ = 0;

    //�n�ʗpCsv�f�[�^
    groundCsvDate_ = (Application::PATH_CSV + "Stage2.csv").c_str();
    putZoneCsvData_ = (Application::PATH_CSV + "Stage2PutBlockZone.csv").c_str();

    //�z��̃T�C�Y���`
    stageField_.resize(stageHeight_, std::vector<int>(stageWidth_, 0));
    stageRole_.resize(stageHeight_, std::vector<BLOCK_TYPE>(stageWidth_, BLOCK_TYPE::NONE));
    setBlockField_.resize(stageHeight_, std::vector<int>(stageWidth_, 0));
    setBlockRole_.resize(stageHeight_, std::vector<STATE>(stageWidth_, STATE::NONE));

    //���̃C���X�^���X
    moon_ = level_->GetMoonInstans();

    minoPos_ = { MINO_DEFAULT_POS, MINO_DEFAULT_POS };

}

void Block2::StageCreate(void)
{ 
    //�X�e�[�W�̏�����
    for (int i = 0; i < stageHeight_; ++i)
    {
        for (int j = 0; j < stageWidth_; j++)
        {
            stageRole_[i][j] = BLOCK_TYPE::NONE;
        }
    }

    //��(�v���C���[�̉��̈ړ�����)
    for (int i = 0; i < stageHeight_; ++i)
    {
        stageRole_[i][0] = BLOCK_TYPE::WALL;
        stageRole_[i][stageWidth_ - 1] = BLOCK_TYPE::WALL;
    }

    //�n�ʂ̖����t��
    for (int i = stageHeight_ - groundHeight_; i < stageHeight_; i++)
    {
        for (int j = 0; j < groundWidth_; j++)
        {
            if (stageField_[i][j] != -1)
            {
                stageRole_[i][j] = BLOCK_TYPE::GROUND;
            }
        }
    }

    //--------------------------------------------------------------------

    //�Ƃ̌`�Ƀu���b�N��u���Ă��炤
    for (int i = 0; i < fieldHeight_; ++i)
    {
        for (int j = 0; j < fieldWidth_; ++j)
        {
            if (setBlockField_[i][j] == 1)
            {
                setBlockRole_[i][j] = STATE::NO_SET;
                setBlockCnt_++;
            }
        }
    }

}

void Block2::LoadStageCsvData(void)
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
            stageField_[stageHeight_ - groundHeight_ + y][x] = chipNo;
        }
        y++;
    }

}

void Block2::LoadPositionCsvData(void)
{
    //�t�@�C���̏���
    std::ifstream ifs = std::ifstream(putZoneCsvData_);
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
            setBlockField_[y][x] = chipNo;
        }
        y++;
    }
}

void Block2::PutBlockZoneDraw()
{
    Vector2F cameraPos = level_->GetCameraPos();
    Vector2 center = level_->GetGameCenter();

    for (int i = 0; i < fieldHeight_; ++i)
    {
        for (int j = 0; j < fieldWidth_; ++j)
        {
            if (setBlockRole_[i][j] == STATE::NO_SET)
            {
                DrawRotaGraph(center.x + (j + CENTER_DRAW_X) * BLOCK_SIZE_X,
                    i * BLOCK_SIZE_Y - cameraPos.y,
                    1.0f,	//�g��
                    0.0f,	//��]
                    imgBlocks_[MINO_TYPES],
                    true,	//����
                    false);	//����
            }
        }
    }
}

void Block2::BlockSet(int MinoX, int MinoY, int MinoType_)
{
    int minoX = MinoX - CENTER_DRAW_X;
    int minoY = MinoY;

    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            //�~�m�̃u���b�N�̂���ʒu���m�F
            if (minoShapes_[MinoType_][i][j] == 1)
            {
                //�X�e�[�W�͈͓����m�F
                if (minoX + j >= 0 && minoY + i >= 0 &&
                    minoX + j < stageWidth_ && minoY + i < stageHeight_)
                {
                    //���W�̈ʒu���u���b�N��u�����ꏊ�������̏ꏊ���m�F
                    if (setBlockRole_[minoY + i][minoX + j] == STATE::NO_SET &&
                        stageRole_[MinoY + i][MinoX + j] == BLOCK_TYPE::BLOCK)
                    {
                        //�u���b�N�̖�����ς���
                        setBlockRole_[minoY + i][minoX + j] = STATE::SET;

                        //�c��̐������炷
                        setBlockCnt_--;
                    }
                    if (setBlockRole_[minoY + i][minoX + j] == STATE::NONE &&
                        stageRole_[MinoY + i][MinoX + j] == BLOCK_TYPE::BLOCK)
                    {
                        level_->SetStopCnt(LevelManager::HIT_STOP_CNT);
                        level_->SetGameOver(true);
                    }
                }
            }
        }
    } 
    
    //�c��̐���0�ȉ��̏ꍇ
    if (setBlockCnt_ <= 0)
    {
        //�`�ȊO�̃u���b�N������
        for (int i = 0; i < fieldHeight_; ++i)
        {
            for (int j = 0; j < fieldWidth_; ++j)
            {
                if (setBlockRole_[i][j] == STATE::NONE &&
                    stageRole_[i][j + CENTER_DRAW_X] != BLOCK_TYPE::GROUND)
                {
                    stageRole_[i][j + CENTER_DRAW_X] = BLOCK_TYPE::NONE;
                }
            }
        } 
        
        //�Q�[���N���A�Ƃ���
        level_->SetGameClear(true);
    }
}
