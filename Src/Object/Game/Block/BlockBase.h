#pragma once
#include <vector>
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"
#include "../../../Manager/InputManager.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Application.h"

class LevelManager;
class Blast;
class FireBall;

class BlockBase
{
public:

    //�u���b�N�̎��
    enum class BLOCK_TYPE
    {
        NONE,
        BLOCK,
        GROUND,
        WALL,
    };

    //�~�m���
    enum class MINO_TYPE
    {
        I,
        O,
        S,
        Z,
        J,
        L,
        T,
        MAX //(Field)
    };

    //�u���b�N����
    enum class DELETE_ORDER
    {
        CHECK,
        BLAST,
        SHIFT
    };

    //�u���b�N�摜�̕����鐔
    static constexpr int GROUND_IMG_NUM_X = 22;
    static constexpr int GROUND_IMG_NUM_Y = 11;
    static constexpr int GROUND_IMG_NUM = GROUND_IMG_NUM_X * GROUND_IMG_NUM_Y;

    //�n�ʃ`�b�v��1�T�C�Y
    static constexpr int GROUND_SIZE_X = 50;
    static constexpr int GROUND_SIZE_Y = 50;

    //�u���b�N�摜�̕����鐔
    static constexpr int BLOCK_IMG_NUM_X = 8;
    static constexpr int BLOCK_IMG_NUM_Y = 1;
    static constexpr int BLOCK_IMG_NUM = BLOCK_IMG_NUM_X * BLOCK_IMG_NUM_Y;

    //�u���b�N�T�C�Y
    static constexpr int BLOCK_SIZE_X = 50;
    static constexpr int BLOCK_SIZE_Y = 50;

    //�����X�s�[�h
    static constexpr float FALL_SPEED = 1.0f;
    static constexpr float FALL_SPEED_UP = 8.0f;

    //�e�g���~�m��ʃT�C�Y
    static constexpr int MINO_WIDTH = 4;
    static constexpr int MINO_HEIGHT = 4;

    //�Œ肷�鎞��
    static constexpr float FIX_TIME = 0.65f;

    //��ސ�
    static constexpr int MINO_TYPES = static_cast<int>(MINO_TYPE::MAX);

    //�R���X�g���N�^
    BlockBase();

    //�f�X�g���N�^
    ~BlockBase();

    //������
    virtual void Init(LevelManager* parent);

    //�X�V
    virtual void Update();

    //�Փˎ��̍X�V����
    virtual void HitUpdate(Vector2 pos);

    //���Փˎ��̍X�V����
    virtual void NoHitUpdate(Vector2 pos);

    //�`�揈��
    virtual void Draw();

    //���
    virtual void Release();

    //�摜�̓ǂݍ���
    void Load();

    //�ϐ��̏�����
    virtual void Reset();

    //�t�B�[���h����
    virtual void StageCreate();

    //�~�m�̌Œ艻����
    void MinoFixed(int MinoX, int MinoY, int MinoType);

    //���C�������̏���
    virtual void LineDelete(void);

    //�t�B�[���h�Ƃ̓����蔻��
    bool IsHitField(int MinoX, int MinoY, int MinoType);

    //�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
    bool IsHitBlock(Vector2 Pos);
    
    //�e�g���~�m�̃��Z�b�g
    void ResetMino();

    //�p�Y���̑��쏈��
    void MoveMino();

    //��]����
    void ArrayRotation(int type, AsoUtility::DIR value);
   
    //��]���̓����蔻��
    bool RotationHit(int MinoX, int MinoY, int MinoType, AsoUtility::DIR value);

    //�u���b�N�̖�����ς���
    void DeleteBlock(int y, int x);

    //�u���b�N�̃V�t�g����
    virtual void ShiftLine();

    //�u���ꂽ�u���b�N�̍������擾
    virtual void CheckHeight(int y);

    //���̕`��
    void NextBlockDraw(Vector2 pos, float expansion);

    //���̃u���b�N�̕ύX
    void ChangeNextBlock();

    //�u���b�N�V�����[�p�����֐�
    virtual void Create();

    //�S��������
    virtual void AllDeleteLine();

    void SetFallSpeed(float speed);

    //CSV�f�[�^�̓ǂݍ���
    virtual void LoadStageCsvData();

    //�n�ʂ̌`��
    void CreateGround();

    //�g�p���Ă���}�b�v����������
    void ClearUsedMap(void);	

    //�`�b�v�i���o�[��Ԃ�
    int GetChipNo(Vector2 mapPos);

    //�`�p��CSV�f�[�^��ǂݍ���
    virtual void LoadPositionCsvData();

   //�u���b�N�̃Z�b�g
    virtual void BlockSet(int MinoX, int MinoY, int MinoType);

    //�Z�b�g���Ăق����u���b�N�]�[���̕`��
    virtual void PutBlockZoneDraw();

    //�w�肵���~�m�̒l��Ԃ�
    int GetMinoShapes(int type,int x,int y); 
    
    //���݂̏c�ɒu����Ă�u���b�N�̐���Ԃ�
    int GetFieldBestBlockY(int y);     

    //�~�m�̎�ނ�Ԃ�
    int GetMinoType();

    //���݂̍�����Ԃ�
    int GetNowHeight();

    //�������x��Ԃ�
    float GetFallSpeed();

    //�w�肵���t�B�[���h�̒l��Ԃ�
    int GetField(Vector2 value);

    //�z�u����u���b�N�̐���Ԃ�
    int GetBlockCount();

    //�폜���郉�C���̐���Ԃ�
    int GetLineCount();

    //�t�B�[���h���Ƀu���b�N�����邩�Ԃ�
    bool IsBlock();

    //�폜�����Ԃ�
    bool IsDelete();

    //�u���b�N�̃T�C�Y��Ԃ�
    Vector2 GetSize();
    
    //�w�肵���~�m�̃u���b�N�̈ʒu��Ԃ�
    Vector2 GetMinoBlockPos(Vector2 Pos, int x, int y);

    //�n�ʃ`�b�v�̃T�C�Y
    //Vector2 GetGroundBlockPos(Vector2 value);

    //�~�m�̈ʒu��Ԃ�
    Vector2F GetMinoPos();

    //�����̔z���Ԃ�
    std::vector<Blast*> GetBlast(void);

    //�΂̋ʂ̔z���Ԃ�
    std::vector<FireBall*> GetFireBall(void);

protected:

    //�n�ʗpCSV�f�[�^�ǂݍ���
    std::string groundCsvDate_;

    //�X�e�[�W�t�B�[���h
    std::vector<std::vector<int>> stageField_;

    //�u���b�N���Ƃ̖���
    std::vector<std::vector<BLOCK_TYPE>> stageRole_;

    //�e�g���~�m�̊i�[
    int minoShapes_[static_cast<int>(MINO_TYPE::MAX)]
        [MINO_HEIGHT]
        [MINO_WIDTH] =
    {
        // MINO_TYPE_I
        {
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0
        },

        // MINO_TYPE_O
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },

        // MINO_TYPE_S
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            1, 1, 0, 0,
            0, 0, 0, 0
        },

        // MINO_TYPE_Z
        {
            0, 0, 0, 0,
            1, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },

        // MINO_TYPE_J
        {
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },


        // MINO_TYPE_L
        {
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },

        // MINO_TYPE_T
        {
            0, 0, 0, 0,
            1, 1, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 0
        },
    };

    //�t�B�[���h�T�C�Y
    int fieldWidth_;
    int fieldHeight_;

    //�n�ʃT�C�Y
    int groundWidth_;
    int groundHeight_;

    //�X�e�[�W�S�̂̃T�C�Y
    int stageWidth_;
    int stageHeight_;

    //�u���b�N�̉摜
    int imgBlocks_[BLOCK_IMG_NUM];

    //�u���u���b�N�̐�
    int setBlockCnt_;

    //���������C���̃J�E���g
    int cntLine_;

    //����(�|�C���^)
    std::vector<Blast*> blasts_;

    //�΂̋�
    std::vector<FireBall*> fire_;

    //�C���X�^���X
    LevelManager* level_;

    //���݂̍���
    int nowHeight_;

    int gameHeight_;

    //���Z�b�g���ԃJ�E���g
    float resetCnt_;

    //�������Ԃ̃X�s�[�h
    float fallSpeed_;
    float normalFallSpeed_;

    //�����̋���
    bool isFall_;

    //�e�g���~�m�̎��
    int minoType_;

    //�l�N�X�g�̎��
    int nextMino_;

    //�~�m�̍��W
    Vector2F minoPos_;

    //�u���b�N�T�C�Y
    Vector2 size_;

    //�摜
    int imgGrounds_[GROUND_IMG_NUM];				

    //�g�p���Ă�}�b�v�`�b�v�̃T�C�Y
    Vector2 usedMapSize_;

    //�폜���郉�C����Y�l
    int deleteLine_;

    //�t�B�[���h���̃u���b�N�̗L������
    bool isBlock_;

    //�폜����
    bool isDelete_;

private:

    InputManager::JOYPAD_NO pad_;
   
    bool isStick_;

    int drawMinoShapes_[static_cast<int>(MINO_TYPE::MAX)]
        [MINO_HEIGHT]
        [MINO_WIDTH] =
    {
        // MINO_TYPE_I
        {
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0
        },

        // MINO_TYPE_O
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },

        // MINO_TYPE_S
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            1, 1, 0, 0,
            0, 0, 0, 0
        },

        // MINO_TYPE_Z
        {
            0, 0, 0, 0,
            1, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },

        // MINO_TYPE_J
        {
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },


        // MINO_TYPE_L
        {
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },

        // MINO_TYPE_T
        {
            0, 0, 0, 0,
            1, 1, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 0
        },
    };
};

