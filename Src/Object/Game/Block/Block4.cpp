#include "../../../Manager/SceneManager.h"
#include "Block4.h"


Block4::Block4()
{
}

Block4::~Block4()
{
}

void Block4::HitUpdate(Vector2 pos)
{
    minoPos_.y = pos.y * BLOCK_SIZE_Y;
    resetCnt_++;
    isFall_ = true;

    //ミノの初期化
    if (resetCnt_ > SceneManager::DEFAULT_FPS * FIX_TIME)
    {
        //ミノの固定化
        MinoFixed(pos.x, pos.y, minoType_);

        //ライン消し(ステージ4用)
        LineDelete();

        //置かれたブロックの高さの取得
        CheckHeight(pos.y);

        //ミノの初期化
        ResetMino();

        //ファイアーボールの生成
        CreateFireBall();
    }
}

void Block4::Reset(void)
{
    groundCsvDate_ = (Application::PATH_CSV + "Stage4.csv").c_str();

    //配列のサイズを定義
    stageField_.resize(stageHeight_, std::vector<int>(stageWidth_, 0)); // 空のフィールドを初期化
    stageRole_.resize(stageHeight_, std::vector<BLOCK_TYPE>(stageWidth_, BLOCK_TYPE::NONE));
}

void Block4::StageCreate(void)
{
    //ステージの初期化
    for (int i = 0; i < stageHeight_; ++i)
    {
        for (int j = 0; j < stageWidth_; j++)
        {
            stageRole_[i][j] = BLOCK_TYPE::NONE;
        }
    }

    //壁(プレイヤーの横の移動制限)
    for (int i = 0; i < stageHeight_; ++i)
    {
        stageRole_[i][0] = BLOCK_TYPE::WALL;
        stageRole_[i][stageWidth_ - 1] = BLOCK_TYPE::WALL;
    }

    //地面の役割付け
    for (int i = fieldHeight_; i < fieldHeight_ + groundHeight_; i++)
    {
        for (int j = 0; j < stageWidth_; j++)
        {
            if (stageField_[i][j] != -1)
            {
                stageRole_[i][j] = BLOCK_TYPE::GROUND;
            }

        }
    }
}

void Block4::CreateFireBall()
{
    int create = GenerationNumber();
    int speed = FireBallSpeed();

    for (int i = 0; i < create; i++)
    {
        FireBall* fire = GetValidFireBall();

        //爆発の生成
        fire->Create(level_, speed);
    }
}

int Block4::GenerationNumber()
{
    int cnt = FIREBALL_COUNTS[FIREBALL_RULE_SIZE - 1]; // 最小値のデフォルトを入れておく
    int height = nowHeight_;

    for (int i = 0; i < FIREBALL_RULE_SIZE; ++i)
    {
        if (height >= FIREBALL_HEIGHT_THRESHOLDS[i])
        {
            cnt = FIREBALL_COUNTS[i];
            break;
        }
    }

    return cnt;
}

float Block4::FireBallSpeed()
{
    float speed = FIREBALL_SPEEDS[FIREBALL_SPEED_RULE_SIZE- 1]; // 最小のデフォルト速度
    int height = nowHeight_;

    for (int i = 0; i < FIREBALL_SPEED_RULE_SIZE; ++i)
    {
        if (height >= FIREBALL_SPEED_HEIGHT_THRESHOLDS[i])
        {
            speed = FIREBALL_SPEEDS[i];
            break;
        }
    }

    return speed;
}

FireBall* Block4::GetValidFireBall()
{
    FireBall* fire = new FireBall();
    fire_.push_back(fire);
    return fire;
}