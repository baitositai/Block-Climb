#include "BlockMarason.h"
#include "../Level/LevelManager.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"

BlockMarason::BlockMarason()
{
    count_ = 0;
    fieldNeo_.clear();
    roleNeo_.clear();
    decLineHeights_.clear();
}

BlockMarason::~BlockMarason()
{
}

void BlockMarason::HitUpdate(Vector2 pos)
{
    minoPos_.y = pos.y * BLOCK_SIZE_Y;
    resetCnt_++;
    isFall_ = true;

    //ミノの初期化
    if (resetCnt_ > SceneManager::DEFAULT_FPS * FIX_TIME)
    {
        //置かれたブロックの高さの取得
        CheckHeight(pos.y);

        //ミノの固定化
        MinoFixed(pos.x, pos.y, minoType_);

        //ミノの初期化
        ResetMino();

        //ブロック設置音
        SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::SET));

        //高さの更新処理
        HeightUpdate();
    }
}

void BlockMarason::Reset(void)
{
    //CSVデータの読み込み
    groundCsvDate_ = (Application::PATH_CSV + "Stage1.csv").c_str();

    //配列のサイズを定義
    stageField_.resize(stageHeight_, std::vector<int>(stageWidth_, 0));
    stageRole_.resize(stageHeight_, std::vector<BLOCK_TYPE>(stageWidth_, BLOCK_TYPE::NONE));

    //カウントの初期化
    cntLine_ = 0;
    count_ = 0;
}

void BlockMarason::StageCreate(void)
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
            if (stageField_[i][j] != -1) { stageRole_[i][j] = BLOCK_TYPE::GROUND; }
        }
    }
}

void BlockMarason::LineDelete(void)
{
    int startLine = 0;

    for (int i = 0; i < fieldHeight_; ++i)
    {
        //ライン消し
        bool isLineFilled = false;
        for (int j = 1; j < fieldWidth_ - 1; ++j)
        {
            //ブロックがある時
            if (stageRole_[i][j] == BLOCK_TYPE::BLOCK)
            {
                //そのラインから消去する
                isLineFilled = true;
                startLine = i - 1;
                break;
            }
        }

        //ライン消しの実行
        if (isLineFilled)
        {
            int cnt = -1;
            int line = 1 + (rand() % LINE_DELETE_MAX);
            gameHeight_ += line;
            for (int j = startLine; j < startLine + line; j++)
            {
                for (int k = 1; k < stageWidth_ - 1; k++)
                {
                    cnt++;
                    BlastLine(j, k, cnt);
                }
            }
            break;
        }
    }    
}

void BlockMarason::HeightUpdate()
{
    if (gameHeight_ <= UPDATE_LINE)
    {
        for (int i = 0; i < count_; i++)
        {
            // 最後の要素を削除
            stageField_.pop_back();
            stageRole_.pop_back();

            // 新しい要素を先頭に追加
            stageField_.insert(stageField_.begin(), std::vector<int>(stageWidth_, 0));
            stageRole_.insert(stageRole_.begin(), std::vector<BLOCK_TYPE>(stageWidth_, BLOCK_TYPE::NONE));

            stageRole_[0][0] = BLOCK_TYPE::WALL;
            stageRole_[0][stageWidth_ - 1] = BLOCK_TYPE::WALL;

            //座標をずらす
            level_->ShiftGame();

            gameHeight_ += 1;

        }
    }
}

void BlockMarason::CheckHeight(int y)
{
    int height1 = y;
    for (int i = 0; i < MINO_HEIGHT; i++)
    {
        bool flag = true;
        for (int j = 1; j < fieldWidth_ - 1; j++)
        {
            if (stageRole_[height1][j] != BLOCK_TYPE::NONE)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            height1++;
        }
    }

    int height2 = y;
    for (int i = 0; i < MINO_HEIGHT; i++)
    {
        bool flag = true;
        for (int j = 0; j < MINO_WIDTH; j++)
        {
            
            if (minoShapes_[minoType_][i][j] == 1)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            height2++;
        }
        else
        {
            break;
        }
    }

    count_ = height1 - height2;

    if (count_ > 0)
    {
        nowHeight_ += count_;
        gameHeight_ -= count_;
    }
    else
    {
        count_ = 0;
    }
}

Blast* BlockMarason::GetValidBlast(void)
{
    Blast* blast = new Blast();
    blasts_.push_back(blast);
    return blast;
}

void BlockMarason::BlastLine(int y, int x, int i)
{
    Blast* blast = GetValidBlast();

    //爆発位置用にブロックの座標を取得
    Vector2 blockPos = { x * BLOCK_SIZE_X + level_->GetGameCenter().x,
                        (y + 1) * BLOCK_SIZE_Y + level_->GetGameCenter().y };

    //生成用クールタイム
    float coolTime = (i * COOL_TIME);

    //爆発の生成
    blast->Create(level_ ,this, blockPos, coolTime);
}