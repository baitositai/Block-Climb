#include <DxLib.h>
#include<vector>
#include <iostream>
#include <string>
#include <fstream>
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/InputManager.h"
#include "../../../Manager/SoundManager.h"
#include "../Level/LevelManager.h"
#include "BlockBase.h"
#include "../Gimic/Blast.h"
#include "../Gimic/FireBall.h"


BlockBase::BlockBase()
{
    fallSpeed_ = 0.0f;
    fieldHeight_ = 0;
    fieldWidth_ = 0;
    level_ = nullptr;
    gameHeight_ = 0;
    groundHeight_ = 0;
    groundWidth_ = 0;
    minoType_ = 0;
    resetCnt_ = 0;
    stageHeight_ = 0;
    stageWidth_ = 0;
	nowHeight_ = 0;
	setBlockCnt_ = 0;
	cntLine_ = 0;
	isBlock_ = false;
	isFall_ = false;
	isStick_ = false;
	nextMino_ = 0;
	pad_ = InputManager::JOYPAD_NO::PAD1;
    size_ = { };
	normalFallSpeed_ = 0.0f;
	deleteLine_ = 0;
	isDelete_ = false;

    for (int i = 0; i < BLOCK_IMG_NUM; i++)
    {
        imgBlocks_[i] = 0;
    } 
    
    for (int i = 0; i < GROUND_IMG_NUM; i++)
    {
        imgGrounds_[i] = 0;
    }
}

BlockBase::~BlockBase()
{
}

void BlockBase::Init(LevelManager* parent)
{
    level_ = parent;

    //操作主の情報
    pad_ = InputManager::JOYPAD_NO::PAD1;

    //落下に関する初期化
    normalFallSpeed_ = FALL_SPEED;
    fallSpeed_ = FALL_SPEED;

    isFall_ = false;

    isBlock_;

    //スティックの判定
    isStick_ = false;

    //ブロックサイズ
    size_ = { BLOCK_SIZE_X,BLOCK_SIZE_Y };

    //リセットカウントの初期化
    resetCnt_ = 0.0f;
  
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

    //高さ
    nowHeight_ = 0;
    gameHeight_ = fieldHeight_;

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
    
    //ミノの初期リセット
    ResetMino();
}

void BlockBase::Update()
{
    //ミノを動かす処理
    MoveMino();

    Vector2 mino = minoPos_.ToVector2();
    mino.x -= level_->GetGameCenter().x;
    Vector2 fieldMinoPos = level_->Field2Pos(mino);
    if (fieldMinoPos.y < 0) { fieldMinoPos.y *= -1; }

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

void BlockBase::HitUpdate(Vector2 pos)
{
    minoPos_.y = pos.y * BLOCK_SIZE_Y;
    resetCnt_++;
    isFall_ = true;

    //ミノの初期化
    if (resetCnt_ > SceneManager::DEFAULT_FPS * FIX_TIME)
    {
        isBlock_ = true;

        //ミノの固定化
        MinoFixed(pos.x, pos.y, minoType_);

        //ブロックのセット(ステージ2用)
        BlockSet(pos.x, pos.y, minoType_);

        //ライン消し(ステージ4用)
        LineDelete();

        //置かれたブロックの高さの取得
        CheckHeight(pos.y);

        //ミノの初期化
        ResetMino();

        SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::SET));
    }
}

void BlockBase::NoHitUpdate(Vector2 pos)
{
    isFall_ = false;
    //プレイヤーとの当たり判定を確認
    if (level_->IsPlayerCheck(AsoUtility::DIR::DOWN, pos, minoType_))
    {
        //当たっていた場合、プレイヤーの座標をずらす
        level_->PlayerShift(AsoUtility::DIR::DOWN);
    }
    //ミノを落とす処理
    minoPos_.y += fallSpeed_;
}

void BlockBase::Draw()
{ 
    Vector2F cameraPos = level_->GetCameraPos();
    Vector2 center = level_->GetGameCenter();

    PutBlockZoneDraw();

    for (int i = 0; i < stageHeight_; ++i)
    {
        for (int j = 0; j < stageWidth_; ++j)
        {
            //地面の描画
            if (stageRole_[i][j] == BLOCK_TYPE::GROUND)
            {
                DrawRotaGraph(center.x + j * GROUND_SIZE_X,
                    i * GROUND_SIZE_Y - cameraPos.y,
                    1.0f,	//拡大
                    0.0f,	//回転
                    imgGrounds_[stageField_[i][j]],
                    true,	//分からん
                    false);	//向き
            } 
            
            //固定ブロックの描画
            if (stageRole_[i][j] == BLOCK_TYPE::BLOCK)
            {
                //フィールドと固定したブロックの描画
                DrawRotaGraph(center.x + j * BLOCK_SIZE_X,
                    i * BLOCK_SIZE_Y - cameraPos.y,
                    1.0f,	//拡大
                    0.0f,	//回転
                    imgBlocks_[stageField_[i][j]],
                    true,	//分からん
                    false);	//向き
            } 
        }
    }

    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            if (1 == minoShapes_[minoType_][i][j])
            {
                //ミノの描画
                DrawRotaGraph(minoPos_.x + j * BLOCK_SIZE_X,
                    minoPos_.y + i * BLOCK_SIZE_Y - cameraPos.y,
                    1.0f,	//拡大
                    0.0f,	//回転
                    imgBlocks_[minoType_],
                    true,	//分からん
                    false);	//向き
            }
        }
    }
}

void BlockBase::Release()
{
    for (int i = 0; i < GROUND_IMG_NUM; i++)
    {
        DeleteGraph(imgGrounds_[i]);
    }
    for (int i = 0; i < BLOCK_IMG_NUM; i++)
    {
        DeleteGraph(imgBlocks_[i]);
    }
}

void BlockBase::Load()
{
    //ブロック画像読み込み
    int ret;
    ret = LoadDivGraph((Application::PATH_BLOCK + "Blocks.png").c_str()
        , BLOCK_IMG_NUM
        , BLOCK_IMG_NUM_X
        , BLOCK_IMG_NUM_Y
        , BLOCK_SIZE_X
        , BLOCK_SIZE_Y
        , &(imgBlocks_[0]));

    //地面画像の読み込み
    ret = LoadDivGraph((Application::PATH_IMAGE + "Terrain/Terrain.png").c_str()
        , GROUND_IMG_NUM
        , GROUND_IMG_NUM_X
        , GROUND_IMG_NUM_Y
        , GROUND_SIZE_X
        , GROUND_SIZE_Y
        , &(imgGrounds_[0]));

}

//変数の初期化
void BlockBase::Reset()
{ 
}

//テトリスフィールドの形成
void BlockBase::StageCreate()
{   
}

//ミノの固定化
void BlockBase::MinoFixed(int MinoX, int MinoY, int MinoType)
{
    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            if (1 == minoShapes_[minoType_][i][j])
            {
                //ブロックを固定
                stageField_[MinoY + i][MinoX + j] = MinoType;

                //種類を変える
                stageRole_[MinoY + i][MinoX + j] = BLOCK_TYPE::BLOCK;

            }
        }
    }
}

//ライン消去
void BlockBase::LineDelete()
{
}

//当たり判定
bool BlockBase::IsHitField(int MinoX, int MinoY, int MinoType)
{
    int minoX = MinoX;
    int minoY = MinoY;

    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            if (minoShapes_[MinoType][i][j] == 1)
            {
                if (stageRole_[minoY + i][minoX + j] != BLOCK_TYPE::NONE)
                {
                    return true;
                }
            }
        }
    }

	return false;
}

//オブジェクトとブロックの衝突判定
bool BlockBase::IsHitBlock(Vector2 Pos)
{
    //ブロックとの衝突判定
    if (Pos.x >= 0 && Pos.y >= 0 &&
        Pos.x < stageWidth_ && Pos.y < stageHeight_)
    {
        if (stageRole_[Pos.y][Pos.x] != BLOCK_TYPE::NONE)
        {
            return true;
        }
    }

    return false;
}

//回転前の当たり判定確認
bool BlockBase::RotationHit(int MinoX, int MinoY, int MinoType, AsoUtility::DIR value)
{
    switch (value)
    {
    case AsoUtility::DIR::RIGHT:

        for (int i = 0; i < MINO_HEIGHT; ++i)
        {
            for (int j = 0; j < MINO_WIDTH; ++j)
            {
                if (minoShapes_[MinoType][(MINO_HEIGHT - 1) - j][i] == 1)
                {
                    if (stageRole_[MinoY + i][MinoX + j] != BLOCK_TYPE::NONE)
                    {
                        return true;
                    }
                }
            }
        }

        break;

    case AsoUtility::DIR::LEFT:

        for (int i = 0; i < MINO_HEIGHT; ++i)
        {
            for (int j = 0; j < MINO_WIDTH; ++j)
            {
                if (minoShapes_[MinoType][j][MINO_HEIGHT - 1 - i]==1)
                {
                    if (stageRole_[MinoY + i][MinoX + j] != BLOCK_TYPE::NONE)
                    {
                        return true;
                    }
                }
            }
        }

        break;

    default:
        break;
    }

    return false;

}

void BlockBase::DeleteBlock(int y, int x)
{
    //座標の変換
    Vector2 mapPos = {(x - level_->GetGameCenter().x) / BLOCK_SIZE_X,
                      (y - level_->GetGameCenter().y) / BLOCK_SIZE_Y};
    
    //ブロックの消去
    stageRole_[mapPos.y][mapPos.x] = BLOCK_TYPE::NONE;
}

void BlockBase::ShiftLine()
{
}

void BlockBase::CheckHeight(int y)
{    
    int height = y;
    for (int i = 0; i < MINO_HEIGHT; i++)
    {
        //行ごとにブロックがあるかの確認
        bool flag = true;
        for (int j = 0; j < MINO_WIDTH; j++)
        {
            //ある場合
            if (minoShapes_[minoType_][i][j] == 1)
            {
                //処理の実行を許可する
                flag = false;
                break;
            }
        }
        if (flag == false)
        {
            //for分から抜ける
            break;
        }
        else
        {
            //高さを1減らす
            height++;
        }
    }

    //正しい高さを計算
    height = fieldHeight_ - height;

    //高さが更新された場合
    if (nowHeight_ < height)
    {
        //現在の高さも更新
        nowHeight_ = height;
    }
}

void BlockBase::NextBlockDraw(Vector2 pos ,float expansion)
{
    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            if (1 == drawMinoShapes_[nextMino_][i][j])
            {
                DrawRotaGraph(pos.x - BLOCK_SIZE_X + j * BLOCK_SIZE_X * expansion,
                    pos.y + i * BLOCK_SIZE_Y * expansion,
                    expansion,	//拡大
                    0.0f,	//回転
                    imgBlocks_[nextMino_],
                    true,	//分からん
                    false);	//向き
            }
        }
    }
}

void BlockBase::ChangeNextBlock()
{
    nextMino_ += 1;
    if (nextMino_ >= static_cast<int>(MINO_TYPE::MAX)) { nextMino_ = 0; }
}

void BlockBase::Create()
{
}

void BlockBase::AllDeleteLine()
{
}

void BlockBase::SetFallSpeed(float speed)
{
    fallSpeed_ = speed;
    normalFallSpeed_ = speed;
}

//ミノのリセット
void BlockBase::ResetMino()
{
    //ミノの種類
    minoType_ = nextMino_;

    //ランダムでミノの種類を決める
    int num = rand() % static_cast<int>(MINO_TYPE::MAX);

    //ミノの初期座標
    Vector2F cameraPos = level_->GetCameraPos();
    float width = fieldWidth_;
    minoPos_ = { level_->GetGameCenter().x + width / 2 * BLOCK_SIZE_X ,
                cameraPos.y };

    //次のミノの格納
    nextMino_ = num;

    isFall_ = false;

    resetCnt_ = 0.0f;
}

//ミノの操作処理
void BlockBase::MoveMino()
{
    auto& ins = InputManager::GetInstance();
    auto& snd = SoundManager::GetInstance();
    int stickX = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
    int stickY = ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;

    //下におろす
    if ((ins.IsNew(KEY_INPUT_S) || 
        stickY > 0 )&&
        isFall_ == false)
    {
        fallSpeed_ = FALL_SPEED_UP;
    }
    else if(isFall_ == false)
    {
        fallSpeed_ = normalFallSpeed_;
        
    }
    else
    {
        fallSpeed_ = 0.0f;
    }

    Vector2 mino = minoPos_.ToVector2();
    mino.x -= level_->GetGameCenter().x;
    Vector2 fieldMinoPos = level_->Field2Pos(mino);

    //左に動かす
    if (ins.IsTrgDown(KEY_INPUT_A) ||
        (stickX < 0 && !isStick_))
    {
        isStick_ = true;
        if (!IsHitField(fieldMinoPos.x - 1, fieldMinoPos.y, minoType_))
        {
            if (level_->IsPlayerCheck(AsoUtility::DIR::LEFT, fieldMinoPos, minoType_))
            {
                level_->PlayerShift(AsoUtility::DIR::LEFT);
            } 
            snd.PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::MOVE));
            minoPos_.x -= BLOCK_SIZE_X;
        }
    }

    //右に動かす
    if (ins.IsTrgDown(KEY_INPUT_D) ||
        (stickX > 0 && !isStick_))
    {
        isStick_ = true;
        if (!IsHitField(fieldMinoPos.x + 1, fieldMinoPos.y, minoType_))
        {
            if (level_->IsPlayerCheck(AsoUtility::DIR::RIGHT, fieldMinoPos, minoType_))
            {
                level_->PlayerShift(AsoUtility::DIR::RIGHT);
                
            }
            snd.PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::MOVE));
            minoPos_.x += BLOCK_SIZE_X;
        }
    }
   
    //右回転
    if (ins.IsTrgDown(KEY_INPUT_E) ||
        ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::R_TRIGGER))
    {
        if (!RotationHit(fieldMinoPos.x, fieldMinoPos.y, minoType_, AsoUtility::DIR::RIGHT))
        {
            ArrayRotation(minoType_, AsoUtility::DIR::RIGHT);
            snd.PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::ROTATION));
        }
    }

    //左回転
    if (ins.IsTrgDown(KEY_INPUT_Q) ||
        ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::L_TRIGGER))
    {
        if (!RotationHit(fieldMinoPos.x, fieldMinoPos.y, minoType_, AsoUtility::DIR::LEFT))
        {
            ArrayRotation(minoType_, AsoUtility::DIR::LEFT);
            snd.PlayEffectSound(SoundManager::EFFECT_TYPE::BLOCK, static_cast<int>(SoundManager::BLOCK::ROTATION));
        }
    }

    //スティックの判定を戻す
    if (stickX == 0)
    {
        isStick_ = false;
    }
}

//回転処理
void BlockBase::ArrayRotation(int type, AsoUtility::DIR value)
{
    //回転したものを代入する用
    char array[MINO_HEIGHT][MINO_WIDTH] = { 0 };
    
    switch (value)
    {
    case AsoUtility::DIR::RIGHT:

        for (int i = 0; i < MINO_HEIGHT; ++i)
        {
            for (int j = 0; j < MINO_WIDTH; ++j)
            {
                array[i][j] = minoShapes_[type][(MINO_HEIGHT - 1) - j][i];
            }
        }

        break;
    case AsoUtility::DIR::LEFT:

        for (int i = 0; i < MINO_HEIGHT; ++i)
        {
            for (int j = 0; j < MINO_WIDTH; ++j)
            {
                array[i][j] = minoShapes_[type][j][MINO_HEIGHT - 1 - i];
            }
        }

        break;
    default:
        break;
    }

    for (int i = 0; i < MINO_HEIGHT; ++i)
    {
        for (int j = 0; j < MINO_WIDTH; ++j)
        {
            minoShapes_[type][i][j] = array[i][j];
        }
    }
}

//外部ファイルからステージのCSVデータを読み込む
void BlockBase::LoadStageCsvData(void)
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
            stageField_[fieldHeight_ + y][x] = chipNo;
        }
        y++;
    }
}

//チップ番号を返す
int BlockBase::GetChipNo(Vector2 mapPos)
{
    return stageField_[mapPos.y][mapPos.x];
}

void BlockBase::LoadPositionCsvData()
{
}

void BlockBase::BlockSet(int MinoX, int MinoY, int MinoType_)
{
}

void BlockBase::PutBlockZoneDraw()
{
}

//地面の形成
void BlockBase::CreateGround()
{
    //処理で利用するマップ配列を初期化する
    ClearUsedMap();
}

//使用マップの初期化
void BlockBase::ClearUsedMap(void)
{
    for (int y = fieldHeight_; y < fieldHeight_ + groundHeight_; y++)
    {
        for (int x = 0; x < groundWidth_; x++)
        {
            stageField_[y][x] = -1;
        }
    }
}

int BlockBase::GetMinoShapes(int type, int x, int y)
{
    return minoShapes_[type][y][x];
}

//フィールドの値を返す
int BlockBase::GetField(Vector2 value)
{
    return stageField_[value.y][value.x];
}

//ミノの値を返す
Vector2F BlockBase::GetMinoPos()
{
    return minoPos_;
}

std::vector<Blast*> BlockBase::GetBlast(void)
{
    return blasts_;
}

std::vector<FireBall*> BlockBase::GetFireBall()
{
    return fire_;
}

Vector2 BlockBase::GetSize()
{
    return size_;
}

Vector2 BlockBase::GetMinoBlockPos(Vector2 Pos,int x, int y)
{
   Vector2 pos = { Pos.x + BLOCK_SIZE_X * x,
                    Pos.y + BLOCK_SIZE_Y * y };
   return pos;
}

int  BlockBase::GetFieldBestBlockY(int y)
{
    int maxY = y;

    for (int i = y - 1; i > 0; i--)
    {
        for (int j = 1; j < fieldWidth_ - 1; j++)
        {
            if (stageRole_[i][j] == BLOCK_TYPE::BLOCK)
            {
                maxY = i;
                break;
            }
        }
        if(stageRole_[i][fieldWidth_ - 1] != BLOCK_TYPE::BLOCK)
        {
            break;
        }
    }

     return maxY;
}

//ミノの種類を返す
int BlockBase::GetMinoType()
{
    return minoType_;
}

int BlockBase::GetNowHeight()
{
    return nowHeight_;
}

float BlockBase::GetFallSpeed()
{
    return fallSpeed_;
}

int BlockBase::GetBlockCount()
{
    return setBlockCnt_;
}

int BlockBase::GetLineCount()
{
    return cntLine_;
}

bool BlockBase::IsBlock()
{
    return isBlock_;
}

bool BlockBase::IsDelete()
{
    return isDelete_;
}