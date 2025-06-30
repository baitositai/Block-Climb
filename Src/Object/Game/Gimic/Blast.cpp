#include <DxLib.h> 
#include "../../../Common/Vector2.h"
#include "../../../Application.h"
#include "../../../Manager/SoundManager.h"
#include "../Level/LevelManager.h"
#include "../Block/BlockBase.h"
#include "Blast.h"

Blast::Blast(void)
{
    for (int i = 0; i < BLAST_ANIM_NUM; i++)
    {
        imgBlasts_[i] = 0;
    }
	level_ = nullptr;
	block_ = nullptr;
	pos_ = { 0,0 };
	size_ = { 0,0 };
	state_ = STATE::NONE;
	blastCntAnim_ = 0;
	blastIdxAnim_ = 0;
	blastSpeedAnim_ = 0.0f;
	createCnt_ = 0.0f;
}

Blast::~Blast(void)
{
}

void Blast::Create(LevelManager* parent, BlockBase* block,Vector2 pos, float coolTime)
{      
    //�摜�ǂݍ���
    LoadDivGraph((Application::PATH_IMAGE + "UI/blast.png").c_str()
        , BLAST_ANIM_NUM
        , BLAST_X
        , BLAST_Y
        , BLAST_SIZE_X
        , BLAST_SIZE_Y
        , &(imgBlasts_[0]));

    level_ = parent;

    //�u���b�N�̃C���X�^���X���擾
    block_ = block;

    //�����ʒu��ݒ�
    pos_ = pos;		

    //�����T�C�Y
    size_ = { 0,0 };
    
    //�����̗L��
    state_ = STATE::WAIT;

    //�����̃A�j���[�V�����p�J�E���^
    blastCntAnim_ = 0;

    //�\�����Ă���A�j���[�V�����̒l
    blastIdxAnim_ = 0;

    //�����̃A�j���[�V�������x
    blastSpeedAnim_ = ANIM_SPEED;

    //�����̐����J�E���g
    createCnt_ = 0.0f;
   
    //�N�[���^�C��
    coolTime_ = coolTime;

    radius_ = 0;

}

void Blast::Update(void)
{
    switch (state_)
    {
    case STATE::NONE:
        break;

    case STATE::WAIT:
        //�J�E���g
        createCnt_++; 

        //�N�[���^�C�����߂��Ă�����s����
        if (coolTime_ <= createCnt_) 
        { 
            state_ = STATE::BLAST; 
            SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC,static_cast<int>(SoundManager::GIMIC::BLAST));
        }
        break;

    case STATE::BLAST:
        //�A�j���[�V�����J�E���g�̍X�V
        blastCntAnim_++;
        blastIdxAnim_ = blastCntAnim_ * blastSpeedAnim_;

        //�����͈͂̊g��
        size_.x += blastCntAnim_ * blastSpeedAnim_;
        size_.y += blastCntAnim_ * blastSpeedAnim_;

        radius_ += blastCntAnim_ * blastSpeedAnim_;

        //�����T�C�Y�̏��
        if (size_.x > BLAST_SIZE_X)
        {
            size_.x = BLAST_SIZE_X;
        }
        if (size_.y > BLAST_SIZE_Y)
        {
            size_.y = BLAST_SIZE_Y;
        }
        if (radius_ > HIT_SIZE / 2)
        {
            radius_ = HIT_SIZE / 2;
        }

        //�����A�j���[�V�����̏I������
        if (blastIdxAnim_ >= BLAST_ANIM_NUM - BLAST_ANIM_OFFSET)
        {
            //������Ȃ���
            size_ = { 0,0 };
            state_ = STATE::NONE;

            //�u���b�N����������
            block_->DeleteBlock(pos_.y, pos_.x);
            
            //�u���b�N���V�t�g������
            block_->ShiftLine();
        }
        break;

    default:
        break;
    }
}

void Blast::Draw(void)
{
    Vector2F cameraPos = level_->GetCameraPos();

    if (state_ == STATE::BLAST)
    {
        DrawRotaGraph(pos_.x,
            pos_.y - cameraPos.y,
            1.0f,	//�g��
            0.0f,	//��]
            imgBlasts_[blastIdxAnim_],
            true,	//����
            false);	//����  
    }
}

void Blast::Release(void)
{
    for (int i = 0; i < BLAST_ANIM_NUM; i++)
    {
        DeleteGraph(imgBlasts_[i]);
    }
}

void Blast::SetPos(Vector2 pos)
{
    pos_.x += pos.x;
    pos_.y += pos.y;
}

Vector2 Blast::GetPos()
{
    return pos_;
}

Vector2 Blast::GetSize()
{
    return size_;
}

float Blast::GetRadius()
{
    return radius_;
}

int Blast::GetCreateCnt()
{
    return createCnt_;
}

Blast::STATE Blast::GetState()
{
    return state_;
}
