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
    //画像読み込み
    LoadDivGraph((Application::PATH_IMAGE + "UI/blast.png").c_str()
        , BLAST_ANIM_NUM
        , BLAST_X
        , BLAST_Y
        , BLAST_SIZE_X
        , BLAST_SIZE_Y
        , &(imgBlasts_[0]));

    level_ = parent;

    //ブロックのインスタンスを取得
    block_ = block;

    //爆発位置を設定
    pos_ = pos;		

    //爆発サイズ
    size_ = { 0,0 };
    
    //爆発の有無
    state_ = STATE::WAIT;

    //爆発のアニメーション用カウンタ
    blastCntAnim_ = 0;

    //表示しているアニメーションの値
    blastIdxAnim_ = 0;

    //爆発のアニメーション速度
    blastSpeedAnim_ = ANIM_SPEED;

    //爆発の生成カウント
    createCnt_ = 0.0f;
   
    //クールタイム
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
        //カウント
        createCnt_++; 

        //クールタイムを過ぎてたら実行する
        if (coolTime_ <= createCnt_) 
        { 
            state_ = STATE::BLAST; 
            SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC,static_cast<int>(SoundManager::GIMIC::BLAST));
        }
        break;

    case STATE::BLAST:
        //アニメーションカウントの更新
        blastCntAnim_++;
        blastIdxAnim_ = blastCntAnim_ * blastSpeedAnim_;

        //爆発範囲の拡大
        size_.x += blastCntAnim_ * blastSpeedAnim_;
        size_.y += blastCntAnim_ * blastSpeedAnim_;

        radius_ += blastCntAnim_ * blastSpeedAnim_;

        //爆発サイズの上限
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

        //爆発アニメーションの終了判定
        if (blastIdxAnim_ >= BLAST_ANIM_NUM - BLAST_ANIM_OFFSET)
        {
            //判定をなくす
            size_ = { 0,0 };
            state_ = STATE::NONE;

            //ブロックを消去する
            block_->DeleteBlock(pos_.y, pos_.x);
            
            //ブロックをシフトさせる
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
            1.0f,	//拡大
            0.0f,	//回転
            imgBlasts_[blastIdxAnim_],
            true,	//透過
            false);	//向き  
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
