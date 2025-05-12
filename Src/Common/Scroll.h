#pragma once
#include<vector>
#include"Vector2.h"
#include"Vector2F.h"

class Scroll
{
public:
	Scroll();
	~Scroll();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="image"></param>画像
	/// <param name="imageSize"></param>画像サイズ
	/// <param name="drawNum"></param>描画数
	/// <param name="scrollSpeed"></param>スクロール速度
	void Init(int image, Vector2 imageSize, int drawNum, float scrollSpeed);
	void Update();	//更新
	void Draw();	//描画
	void Release();	//解放

	//横スクロール用座標設定
	void SetWidthScrollPos();
	
private:
	
	//描画用画像
	int imgBack_;

	//画像サイズ
	Vector2 size_;

	//描画位置用座標
	std::vector<Vector2F> pos_;

	//スクロールスピード
	float speed_;
	
};

