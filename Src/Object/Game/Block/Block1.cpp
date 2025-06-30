#include "Block1.h"

Block1::Block1()
{
}

Block1::~Block1()
{
}

void Block1::Reset(void)
{
    groundCsvDate_ = (Application::PATH_CSV + "Stage1.csv").c_str();

    //配列のサイズを定義
    stageField_.resize(stageHeight_, std::vector<int>(stageWidth_, 0));
    stageRole_.resize(stageHeight_, std::vector<BLOCK_TYPE>(stageWidth_, BLOCK_TYPE::NONE));
}

void Block1::StageCreate(void)
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
