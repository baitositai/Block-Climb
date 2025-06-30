#pragma once
#include <string>
#include "SceneBase.h"
#include "../Application.h"
#include "../Common/Data.h"
#include "../Common/Vector2.h"
#include "../Object/Menu/MenuPlayer.h"

class Scroll;
class Challenge;
class Manual;
class TagPlay;
class Credit;
class Text;
class MenuPlayer;
class BlockBase;

class MenuScene : public SceneBase
{
public:

	enum class STATE
	{
		MARASON,
		SELECT,
		TAG,
		CREDIT,
		MANYUAL,
		NONE
	};

	//画像サイズ
	static constexpr int BRICH_SIZE_X = 750;
	static constexpr int BRICH_SIZE_Y = 750;

	//テキスト箱サイズ
	static constexpr int TEXT_BOX_SIZE_X = Application::SCREEN_SIZE_X;
	static constexpr int TEXT_BOX_SIZE_Y = 160;

	//ブロックの生成カウント
	static constexpr float BLOCK_CREATE_CNT = 1.5f;

	//テキスト箱アルファ値
	static constexpr int TEXT_BOX_ALPHA = 150;

	//背景描画数
	static constexpr int BACK_DRAW_NUM = 3;

	//背景スクロールスピード
	static constexpr float BACK_SCROLL_SPEED = 0.3f;

	//メニューのBGM音量
	static constexpr int BGM_VOLUME = 70;

	MenuScene();
	~MenuScene() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Load();
	void Reset();

	/// <summary>
	/// ゲームシーンへ遷移
	/// </summary>
	/// <param name="level"></param>ゲームのレベル
	void ChangeGameScene(const Data::LEVEL level);	
	
	/// <summary>
	/// 状態変更
	/// </summary>
	/// <param name="state"></param>状態
	void SetState(const STATE state);	
	
	//テキストの初期化
	void TextReset();

	/// <summary>
	/// ポイント座標の設定
	/// </summary>
	/// <param name="pos"></param>座標
	void SetPointPos(const Vector2 pos);

	/// <summary>
	/// プレイヤーの状態を設定
	/// </summary>
	/// <param name="state"></param>プレイヤーの移動状態
	void SetPlayerState(const MenuPlayer::MOVE_STATE state);

	//ステートを返す
	STATE GetMenuState();

	//選択してるステートを返す
	STATE GetMenuSetState();

	//チャレンジの選択しているステートを返す
	Data::LEVEL GetChallengeState();

private:

	//背景画像
	int imgBack_;

	//ポイント画像
	int imgPoint_;

	//メニュー選択用カウント
	int menuCnt_;

	//スティックの判定
	bool isStick_;

	//ブロック生成カウント
	float blockCreateCnt_;

	//ポイント用座標
	Vector2 pointPos_;
	
	//画面ステート
	STATE state_;

	//選択ステート
	STATE sleState_;

	//スクロール
	Scroll* scroll_;

	//チャレンジ課題の選択
	Challenge* challenge_;

	//マニュアル
	Manual* manual_;

	//タッグプレイ
	TagPlay* tag_;

	//クレジット
	Credit* credit_;

	//テキスト
	Text* text_;

	//メニュー画面用プレイヤー
	MenuPlayer* player_;

	//ブロック
	std::vector<BlockBase*> blocks_;	
	
	//背景画像のスクロール処理
	void InitBackImage();

	//メニュー画面での処理
	void MenuUpdate();

	//ポイント画像の描画
	void PointDraw();

	//テキスト表示の背景描画
	void TextBoxDraw();

	//ブロック生成
	BlockBase* GetValidBlock();

	//ポイントの座標を返す
	Vector2 GetPointPos(const int index);

	//ブロックに関する処理
	void BlockUpdate();
};

