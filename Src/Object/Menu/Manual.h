#pragma once

class MenuScene;

class Manual
{

public:

	//コンストラクタ
	Manual(void);

	//デストラクタ
	~Manual(void);

	//マニュアル種類
	static constexpr int MANUAL_TYPE = 4;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="parent"></param>親クラス
	void Init(MenuScene* parent);

	//更新
	void Update(void);

	//描画
	void Draw(void);

	//解放
	void Release(void);

private:

	//スティック判定
	bool isStick_;

	//メニュー選択カウント
	int manuSle_;

	//画像
	int imgManual_[MANUAL_TYPE];

	//メニュー画面
	MenuScene* menu_;

};

