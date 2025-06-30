#include "Block3.h"
#include "../Level/LevelManager.h"

Block3::Block3()
{
    fieldNeo_.clear();
    roleNeo_.clear();
    decLineHeights_.clear();
}

Block3::~Block3()
{
}

void Block3::Reset(void)
{
    //CSVデータの読み込み
    groundCsvDate_ = (Application::PATH_CSV + "Stage3.csv").c_str();

    //配列のサイズを定義
    stageField_.resize(stageHeight_, std::vector<int>(stageWidth_, 0));
    stageRole_.resize(stageHeight_, std::vector<BLOCK_TYPE>(stageWidth_, BLOCK_TYPE::NONE));

    //カウントの初期化
    cntLine_ = 0;
}

void Block3::StageCreate(void)
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

void Block3::LineDelete(void)
{
    for (int i = 0; i < fieldHeight_; ++i)
    {
        //ライン消しの実行を許可しとく
        bool isLineFilled = true;
        for (int j = 1; j < fieldWidth_ - 1; ++j)
        {
            //ブロックがなかった時
            if (stageRole_[i][j] != BLOCK_TYPE::BLOCK)
            {
                //実行の許可を下げる
                isLineFilled = false;
            }
        }

        //ライン消しの実行
        if (isLineFilled)
        {
            //消すラインの高さを保持
            decLineHeights_.push_back(i);

            //配列のサイズを定義
            fieldNeo_.resize(i, std::vector<int>(stageWidth_, 0));
            roleNeo_.resize(i, std::vector<BLOCK_TYPE>(stageWidth_, BLOCK_TYPE::NONE));
            int cnt = -1;
            for (int j = i - 1; j > 0; j--)
            {
                for (int k = 1; k < stageWidth_ - 1; k++)
                {
                    //爆発処理(消したラインのみ実行)
                    if (j == i - 1)
                    {
                        cnt++;
                        BlastLine(j, k, cnt);
                    }
                }
            }
        }
    }
    //シフトできるか確認
    ShiftLine();

    //クリア確認
    if (cntLine_ >= CREAL_LINE) { level_->SetGameClear(true); }
}

Blast* Block3::GetValidBlast(void)
{
    Blast* blast = new Blast();
    blasts_.push_back(blast);
    return blast;
}

void Block3::BlastLine(int y, int x, int i)
{
    Blast* blast = GetValidBlast();

    //爆発位置用にブロックの座標を取得
    Vector2 blockPos = { x * BLOCK_SIZE_X + level_->GetGameCenter().x,
                        (y + 1) * BLOCK_SIZE_Y + level_->GetGameCenter().y };

    //生成用クールタイム
    float coolTime = (i * COOL_TIME);

    //爆発の生成
    blast->Create(level_, this, blockPos, coolTime);
}

//全消し
void Block3::AllDeleteLine()
{
    int startLine = 0;
  
    for (int i = 0; i < fieldHeight_; ++i)
    {
        for (int i = 0; i < fieldHeight_; ++i)
        {
            bool isFlag = false;
            for (int j = 1; j < fieldWidth_ - 1; ++j)
            {
                //ブロックがある時
                if (stageRole_[i][j] == BLOCK_TYPE::BLOCK)
                {
                    isFlag = true;
                    startLine = i - 1;
                    break;
                }
            }
            if (isFlag) { break; }
        }

        int cnt = -1;
        for (int j = startLine; j < fieldHeight_ - 1; j++)
        {
            for (int k = 1; k < stageWidth_ - 1; k++)
            {
                cnt++;
                BlastLine(j, k, cnt);
            }
        }
        break;
    }
    isBlock_ = false;
}

void Block3::ShiftLine()
{
    //ブロックをずらせるか確認
    int size = decLineHeights_.size();
    for (int i = 0; i < size; i++)
    {
        //ライン消しをする高さ
        int height = decLineHeights_[i];

        //ラインシフトの実行を許可しとく
        bool isLineFilled = true;
        for (int j = 1; j < fieldWidth_ - 1; j++)
        {
            //ブロックがある場合
            if (stageRole_[height][j] != BLOCK_TYPE::NONE)
            {
                //実行の許可を下げる
                isLineFilled = false;
                break;
            }
        }
        if (isLineFilled)
        {
            for (int j = height - 1; j > 0; j--)
            {
                for (int k = 1; k < stageWidth_ - 1; k++)
                {
                    //元の値を記憶
                    fieldNeo_[j][k] = stageField_[j][k];
                    roleNeo_[j][k] = stageRole_[j][k];

                    //消したラインから値を上書きしていく
                    stageField_[j + 1][k] = fieldNeo_[j][k];
                    stageRole_[j + 1][k] = roleNeo_[j][k];
                }
                //消したラインのカウント
                if (j == height - 1 &&
                    isBlock_)
                {
                    cntLine_++;
                }
            }
        }
    }
}

