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

    //落下に関する初期化
    fallSpeed_ = FALL_SPEED;

    isFall_ = false;

    //ブロックサイズ
    size_ = { BLOCK_SIZE_X,BLOCK_SIZE_Y };

    //リセットカウントの初期化
    resetCnt_ = 0.0f;

    //高さ
    nowHeight_ = 0;

    //初期ミノの設定
    nextMino_ = rand() % static_cast<int>(MINO_TYPE::MAX);

    //フィールドのサイズを取得
    fieldWidth_ = level_->GetFieldSize().x;
    fieldHeight_ = level_->GetFieldSize().y;

    //地面のサイズを取得
    groundWidth_ = level_->GetGroundSize().x;
    groundHeight_ = level_->GetGroundSize().y;

    //ステージ全体のサイズを取得
    stageWidth_ = level_->GetStageSize().x;
    stageHeight_ = level_->GetStageSize().y;

    //画像の読み込み
    Load();

    //変数の初期化
    Reset();

    //CSVデータの読み込み
    LoadStageCsvData();

    //CSVデータの読み込み(ステージ2用)
    LoadPositionCsvData();

    //フィールド生成
    StageCreate();
}

void Block2::Update()
{
    if (!moon_->IsMoon(Moon::MOON_TYPE::CREATE))
    {
        return;
    }
        
    //ミノを動かす処理    
    MoveMino();

    Vector2 mino = minoPos_.ToVector2();
    mino.x -= level_->GetGameCenter().x;
    Vector2 fieldMinoPos = level_->Field2Pos(mino);
    /*if (fieldMinoPos.y < 0) { fieldMinoPos.y *= -1; }*/

    //ブロック同士で重なった時
    if (IsHitField(fieldMinoPos.x, fieldMinoPos.y, minoType_))
    {
        level_->SetStopCnt(LevelManager::HIT_STOP_CNT);
        level_->SetGameOver(true);
    }

    //ミノが下に着いた時
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

    //ミノの初期化
    if (resetCnt_ > SceneManager::DEFAULT_FPS * FIX_TIME)
    {
        //ミノの固定化
        MinoFixed(pos.x, pos.y, minoType_);

        //ブロックのセット(ステージ2用)
        BlockSet(pos.x, pos.y, minoType_);

        //ライン消し(ステージ4用)
        LineDelete();

        //置かれたブロックの高さの取得
        CheckHeight(pos.y);

        moon_->SetIsMoon(Moon::MOON_TYPE::CREATE, false);
    }
}

void Block2::Reset(void)
{
    setBlockCnt_ = 0;

    //地面用Csvデータ
    groundCsvDate_ = (Application::PATH_CSV + "Stage2.csv").c_str();
    putZoneCsvData_ = (Application::PATH_CSV + "Stage2PutBlockZone.csv").c_str();

    //配列のサイズを定義
    stageField_.resize(stageHeight_, std::vector<int>(stageWidth_, 0));
    stageRole_.resize(stageHeight_, std::vector<BLOCK_TYPE>(stageWidth_, BLOCK_TYPE::NONE));
    setBlockField_.resize(stageHeight_, std::vector<int>(stageWidth_, 0));
    setBlockRole_.resize(stageHeight_, std::vector<STATE>(stageWidth_, STATE::NONE));

    //月のインスタンス
    moon_ = level_->GetMoonInstans();

    minoPos_ = { MINO_DEFAULT_POS, MINO_DEFAULT_POS };

}

void Block2::StageCreate(void)
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

    //家の形にブロックを置いてもらう
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
    //ファイルの準備
    std::ifstream ifs = std::ifstream(groundCsvDate_);
    if (!ifs)
    {
        OutputDebugString("ステージのifstream準備失敗\n");
        return;
    }

    //二次元配列の場所を指定用
    int x = 0;
    int y = 0;

    std::string line;					//1行のデータを格納する領域
    while (getline(ifs, line))
    {
        //Split関数の戻り値受け取り用変数
        std::vector<std::string> strSplit; // 1行を1文字の動的配列に分割
        strSplit = AsoUtility::Split(line, ',');

        int chipNo;

        //分割したデータをマップ配列に格納する
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
    //ファイルの準備
    std::ifstream ifs = std::ifstream(putZoneCsvData_);
    if (!ifs)
    {
        OutputDebugString("ステージのifstream準備失敗\n");
        return;
    }

    //二次元配列の場所を指定用
    int x = 0;
    int y = 0;

    std::string line;					//1行のデータを格納する領域
    while (getline(ifs, line))
    {
        //Split関数の戻り値受け取り用変数
        std::vector<std::string> strSplit; // 1行を1文字の動的配列に分割
        strSplit = AsoUtility::Split(line, ',');

        int chipNo;

        //分割したデータをマップ配列に格納する
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
                    1.0f,	//拡大
                    0.0f,	//回転
                    imgBlocks_[MINO_TYPES],
                    true,	//透過
                    false);	//向き
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
            //ミノのブロックのある位置を確認
            if (minoShapes_[MinoType_][i][j] == 1)
            {
                //ステージ範囲内か確認
                if (minoX + j >= 0 && minoY + i >= 0 &&
                    minoX + j < stageWidth_ && minoY + i < stageHeight_)
                {
                    //座標の位置がブロックを置いた場所かつ条件の場所か確認
                    if (setBlockRole_[minoY + i][minoX + j] == STATE::NO_SET &&
                        stageRole_[MinoY + i][MinoX + j] == BLOCK_TYPE::BLOCK)
                    {
                        //ブロックの役割を変える
                        setBlockRole_[minoY + i][minoX + j] = STATE::SET;

                        //残りの数を減らす
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
    
    //残りの数が0以下の場合
    if (setBlockCnt_ <= 0)
    {
        //形以外のブロックを消す
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
        
        //ゲームクリアとする
        level_->SetGameClear(true);
    }
}
