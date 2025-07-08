#pragma once

class MenuScene;

class Credit
{
public:

	//動画音量
	static constexpr int MOVIE_VOLUME = 70;

	//コンストラクタ
	Credit();

	//デストラクタ
	~Credit();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="parent"></param>親インスタンス
	void Init(MenuScene* parent);

	//更新
	void Update();

	//描画
	void Draw();

	//解放
	void Release();

private:

	//動画
	int movie_;
	
	//再生判定
	bool isPlay_;

	//メニュー画面
	MenuScene* menu_;

};

