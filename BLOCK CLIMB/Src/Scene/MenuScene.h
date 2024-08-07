#pragma once
#include <string>
#include "SceneBase.h"
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

#pragma region 定数
	//画像サイズ
	static constexpr int BRICH_SIZE_X = 750;
	static constexpr int BRICH_SIZE_Y = 750;
#pragma endregion 

	MenuScene(void);
	~MenuScene(void) override;

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void Load(void);
	void Reset(void);

	//背景画像のスクロール処理
	void SetBackImage();

	//シーンチェンジ
	void ChangeGameScene(Data::LEVEL level);

	//ステートの変更
	void SetState(STATE state);

	//メニュー画面での処理
	void MenuUpdate();

	//ポイント画像の描画
	void PointDraw();

	//テキスト表示の背景描画
	void TextBoxDraw();

	//テキストのリセット
	void TextReset();

	//ポイント座標の設定
	void SetPointPos(Vector2 pos);

	//プレイヤーのステートを変更する
	void SetPlayerState(MenuPlayer::MOVE_STATE state);

	//ステートを返す
	STATE GetMenuState();
	
	//選択してるステートを返す
	STATE GetMenuSetState();

	//チャレンジの選択しているステートを返す
	Data::LEVEL GetChallengeState();

	//ブロック生成
	BlockBase* GetValidBlock();

private:

	//背景画像
	int imgBack_;

	//ポイント画像
	int imgPoint_;

	//メニュー選択用カウント
	int menuCnt_;

	//ブロック生成用カウント
	float step_;

	//スティックの判定
	bool isStick_;

	//ポイント用座標
	Vector2 pointPos_;
	
	//画面ステート
	STATE state_;

	//選択ステート
	STATE sleState_;

	//インスタンス
	Scroll* scroll_;
	Challenge* challenge_;
	Manual* manual_;
	TagPlay* tag_;
	Credit* credit_;
	Text* text_;
	MenuPlayer* player_;
	std::vector<BlockBase*> blocks_;
};

