#pragma once
#include <string>
#include "../../Common/Data.h"
#include "../../Common/Vector2.h"

class MenuScene;

class Challenge
{
public:

	//ステージ選択配列
	static constexpr int STAGE_X = 3;
	static constexpr int STAGE_Y = 2;

	//揺らす周波数
	static constexpr float AMPLITUDE = 0.5f;

	//揺らす振幅
	static constexpr float FREQUENCY = 10.0f;

	//課題画像拡大率
	static constexpr float SLE_IMG_RATE = 1.2f;

	//上段課題UIの座標位置
	static constexpr int SLE_UIS_UP_X = Application::SCREEN_SIZE_X / 4;
	static constexpr int SLE_UIS_UP_Y = Application::SCREEN_SIZE_X / 8 + 20;

	//下段課題UIの座標位置
	static constexpr int SLE_UIS_DOWN_X = Application::SCREEN_SIZE_X / 4;
	static constexpr int SLE_UIS_DOWN_Y = Application::SCREEN_SIZE_X / 8 * 3;

	//ポイントローカル座標
	static constexpr int POINT_LOCAL_POS = 75;

	//コンストラクタ
	Challenge();

	//デストラクタ
	~Challenge();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="parent"></param>親インスタンスを受け取る
	void Init(MenuScene* parent);

	//更新
	void Update();

	//描画
	void Draw();

	//解放
	void Release();

	/// <summary>
	/// 選択したレベルを返す
	/// </summary>
	/// <returns></returns>課題レベル
	Data::LEVEL GetChallengeData();

private:

	//画像関係
	int imgSle_[static_cast<int>(Data::LEVEL::MAX)];
	int imgPoint_;

	//テキスト
	std::string expText_[static_cast<int>(Data::LEVEL::MAX)];

	//選択しているステージ
	Vector2 sleCnt_;

	//選択してるステージのデータ格納
	Data::LEVEL sleData_;

	//ポイント用座標
	Vector2 pointPos_;

	//インスタンス
	MenuScene* menu_;

	//スクロール
	int scrollCnt_;

	//スティック判定
	bool isStick_;	
	
	//読み込み
	void Load();

};

