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

    //ブロックの種類
    enum class BLOCK_TYPE
    {
        NONE,
        BLOCK,
        GROUND,
        WALL,
    };

    //ミノ種類
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

    //ブロック消去
    enum class DELETE_ORDER
    {
        CHECK,
        BLAST,
        SHIFT
    };

    //ブロック画像の分ける数
    static constexpr int GROUND_IMG_NUM_X = 22;
    static constexpr int GROUND_IMG_NUM_Y = 11;
    static constexpr int GROUND_IMG_NUM = GROUND_IMG_NUM_X * GROUND_IMG_NUM_Y;

    //地面チップの1サイズ
    static constexpr int GROUND_SIZE_X = 50;
    static constexpr int GROUND_SIZE_Y = 50;

    //ブロック画像の分ける数
    static constexpr int BLOCK_IMG_NUM_X = 8;
    static constexpr int BLOCK_IMG_NUM_Y = 1;
    static constexpr int BLOCK_IMG_NUM = BLOCK_IMG_NUM_X * BLOCK_IMG_NUM_Y;

    //ブロックサイズ
    static constexpr int BLOCK_SIZE_X = 50;
    static constexpr int BLOCK_SIZE_Y = 50;

    //落下スピード
    static constexpr float FALL_SPEED = 1.0f;
    static constexpr float FALL_SPEED_UP = 8.0f;

    //テトリミノ画面サイズ
    static constexpr int MINO_WIDTH = 4;
    static constexpr int MINO_HEIGHT = 4;

    //固定する時間
    static constexpr float FIX_TIME = 0.65f;

    //種類数
    static constexpr int MINO_TYPES = static_cast<int>(MINO_TYPE::MAX);

    //コンストラクタ
    BlockBase();

    //デストラクタ
    ~BlockBase();

    //初期化
    virtual void Init(LevelManager* parent);

    //更新
    virtual void Update();

    //衝突時の更新処理
    virtual void HitUpdate(Vector2 pos);

    //日衝突時の更新処理
    virtual void NoHitUpdate(Vector2 pos);

    //描画処理
    virtual void Draw();

    //解放
    virtual void Release();

    //画像の読み込み
    void Load();

    //変数の初期化
    virtual void Reset();

    //フィールド生成
    virtual void StageCreate();

    //ミノの固定化処理
    void MinoFixed(int MinoX, int MinoY, int MinoType);

    //ライン消しの処理
    virtual void LineDelete(void);

    //フィールドとの当たり判定
    bool IsHitField(int MinoX, int MinoY, int MinoType);

    //オブジェクトとブロックの当たり判定
    bool IsHitBlock(Vector2 Pos);
    
    //テトリミノのリセット
    void ResetMino();

    //パズルの操作処理
    void MoveMino();

    //回転処理
    void ArrayRotation(int type, AsoUtility::DIR value);
   
    //回転時の当たり判定
    bool RotationHit(int MinoX, int MinoY, int MinoType, AsoUtility::DIR value);

    //ブロックの役割を変える
    void DeleteBlock(int y, int x);

    //ブロックのシフト処理
    virtual void ShiftLine();

    //置かれたブロックの高さを取得
    virtual void CheckHeight(int y);

    //次の描画
    void NextBlockDraw(Vector2 pos, float expansion);

    //次のブロックの変更
    void ChangeNextBlock();

    //ブロックシャワー用生成関数
    virtual void Create();

    //全消し処理
    virtual void AllDeleteLine();

    void SetFallSpeed(float speed);

    //CSVデータの読み込み
    virtual void LoadStageCsvData();

    //地面の形成
    void CreateGround();

    //使用しているマップ情報を初期化
    void ClearUsedMap(void);	

    //チップナンバーを返す
    int GetChipNo(Vector2 mapPos);

    //形用のCSVデータを読み込む
    virtual void LoadPositionCsvData();

   //ブロックのセット
    virtual void BlockSet(int MinoX, int MinoY, int MinoType);

    //セットしてほしいブロックゾーンの描画
    virtual void PutBlockZoneDraw();

    //指定したミノの値を返す
    int GetMinoShapes(int type,int x,int y); 
    
    //現在の縦に置かれてるブロックの数を返す
    int GetFieldBestBlockY(int y);     

    //ミノの種類を返す
    int GetMinoType();

    //現在の高さを返す
    int GetNowHeight();

    //落下速度を返す
    float GetFallSpeed();

    //指定したフィールドの値を返す
    int GetField(Vector2 value);

    //配置するブロックの数を返す
    int GetBlockCount();

    //削除するラインの数を返す
    int GetLineCount();

    //フィールド内にブロックがあるか返す
    bool IsBlock();

    //削除判定を返す
    bool IsDelete();

    //ブロックのサイズを返す
    Vector2 GetSize();
    
    //指定したミノのブロックの位置を返す
    Vector2 GetMinoBlockPos(Vector2 Pos, int x, int y);

    //地面チップのサイズ
    //Vector2 GetGroundBlockPos(Vector2 value);

    //ミノの位置を返す
    Vector2F GetMinoPos();

    //爆発の配列を返す
    std::vector<Blast*> GetBlast(void);

    //火の玉の配列を返す
    std::vector<FireBall*> GetFireBall(void);

protected:

    //地面用CSVデータ読み込み
    std::string groundCsvDate_;

    //ステージフィールド
    std::vector<std::vector<int>> stageField_;

    //ブロックごとの役割
    std::vector<std::vector<BLOCK_TYPE>> stageRole_;

    //テトリミノの格納
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

    //フィールドサイズ
    int fieldWidth_;
    int fieldHeight_;

    //地面サイズ
    int groundWidth_;
    int groundHeight_;

    //ステージ全体のサイズ
    int stageWidth_;
    int stageHeight_;

    //ブロックの画像
    int imgBlocks_[BLOCK_IMG_NUM];

    //置くブロックの数
    int setBlockCnt_;

    //消したラインのカウント
    int cntLine_;

    //爆発(ポインタ)
    std::vector<Blast*> blasts_;

    //火の玉
    std::vector<FireBall*> fire_;

    //インスタンス
    LevelManager* level_;

    //現在の高さ
    int nowHeight_;

    int gameHeight_;

    //リセット時間カウント
    float resetCnt_;

    //落下時間のスピード
    float fallSpeed_;
    float normalFallSpeed_;

    //落下の許可
    bool isFall_;

    //テトリミノの種類
    int minoType_;

    //ネクストの種類
    int nextMino_;

    //ミノの座標
    Vector2F minoPos_;

    //ブロックサイズ
    Vector2 size_;

    //画像
    int imgGrounds_[GROUND_IMG_NUM];				

    //使用してるマップチップのサイズ
    Vector2 usedMapSize_;

    //削除するラインのY値
    int deleteLine_;

    //フィールド内のブロックの有無判定
    bool isBlock_;

    //削除判定
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

