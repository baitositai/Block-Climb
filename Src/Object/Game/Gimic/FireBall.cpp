#include <DxLib.h>
#include "../../../Application.h"
#include "../../../Manager/SoundManager.h"
#include "../Level/LevelManager.h"
#include "../Block/BlockBase.h"
#include "FireBall.h"

FireBall::FireBall()
{
	//初期化
	level_ = nullptr;
	speed_ = 0.0f;
	cntAnim_ = 0.0f;
	animSpeed_ = 0.0f;
	idxAnim_ = 0;
	//初期座標
	pos_ = { 0,0 };
	//初期ステート
	state_ = STATE::NONE;
	//画像の初期化
	for (int i = 0; i < static_cast<int>(STATE::NONE); i++)
	{
		for (int j = 0; j < ANIM_NUM; j++)
		{
			imgFireBall_[i][j] = 0;
		}
	}
}

FireBall::~FireBall()
{
}

void FireBall::Create(LevelManager* parent, float speed)
{
    //インスタンス取得
    level_ = parent;

    //スピードの設定
    speed_ = speed;

    Load();

    Reset();

    SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::FIRE_BALL));
}

void FireBall::Update()
{
    STATE preState = state_;
    switch (state_)
    {
    case STATE::FIRE:
        //移動処理
        pos_.y += speed_;  
        //アニメーションカウントの更新
        cntAnim_++;
        idxAnim_ = static_cast<int>(cntAnim_ * animSpeed_) % ANIM_NUM;
        break;

    case STATE::BLAST:
        //アニメーションカウントの更新
        cntAnim_++;
        idxAnim_ = cntAnim_ * animSpeed_;
        if (idxAnim_ > ANIM_NUM)
        {
            state_ = STATE::NONE;
        }
        break;

    default:
        break;
    }
}

void FireBall::Draw()
{
    if (state_ == STATE::NONE)
    {
        return;
    }

    //カメラ座標
    Vector2 cameraPos = level_->GetCameraPos().ToVector2();

    //角度
    constexpr float ANGLE = 90.0f / 180 * DX_PI_F;

    DrawRotaGraph(
        pos_.x,
        pos_.y - cameraPos.y,
        1.0f, 
        ANGLE,
        imgFireBall_[static_cast<int>(state_)][idxAnim_],
        true,
        false);

}

void FireBall::Release()
{
    for (int i = 0; i < static_cast<int>(STATE::NONE); i++)
    {
        for (int j = 0; j < ANIM_NUM; j++)
        {
            DeleteGraph(imgFireBall_[i][j]);
        }
    }
}

void FireBall::Load()
{
    int anim = static_cast<int>(STATE::FIRE);
    LoadDivGraph((Application::PATH_IMAGE + "FireBall/FireBall.png").c_str()
        , ANIM_NUM
        , WIDTH
        , HEIGHT
        , SIZE_X
        , SIZE_Y
        , &(imgFireBall_[anim][0]));

    anim = static_cast<int>(STATE::BLAST);
    LoadDivGraph((Application::PATH_IMAGE + "FireBall/FireBallBlast.png").c_str()
        , ANIM_NUM
        , WIDTH
        , HEIGHT
        , SIZE_X
        , SIZE_Y
        , &(imgFireBall_[anim][0]));
}

void FireBall::Reset()
{
    //初期座標
    Vector2F cameraPos = level_->GetCameraPos();

    //ゲーム画面のサイズ
    Vector2 gameSize = { level_->GetStageSize().x * BlockBase::BLOCK_SIZE_X ,
                          level_->GetStageSize().y * BlockBase::BLOCK_SIZE_Y };

    //中央描画用座標
    float center = level_->GetGameCenter().x;

    pos_ = { center + BlockBase::BLOCK_SIZE_X + GetRand(BlockBase::BLOCK_SIZE_X * level_->GetFieldSize().x),
            cameraPos.y };

    //初期ステート
    state_ = STATE::FIRE;

    //アニメーション初期化
    cntAnim_ = 0;
    animSpeed_ = ANIM_SPEED;
    idxAnim_ = 0;
}

void FireBall::SetPos(Vector2F pos)
{
    pos_.x += pos.x;
    pos_.y += pos.y;
}

void FireBall::SetState(STATE state)
{
    state_ = state;
    cntAnim_ = 0;
}

Vector2F FireBall::GetPos()
{
    return pos_;
}

FireBall::STATE FireBall::GetState()
{
    return state_;
}
