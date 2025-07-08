#pragma once

class MenuScene;

class TagPlay
{
public:

	//コンストラクタ
	TagPlay(void);

	//デストラクタ
	~TagPlay(void);

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="parent"></param>親インスタンス
	void Init(MenuScene* parent);

	//更新
	void Update(void);

	//描画
	void Draw(void);

	//解放
	void Release(void);

private:

	//メニューシーン
	MenuScene* menu_;
	
	//変数の初期化
	void Reset();

	//読み込み
	void Load();
};

