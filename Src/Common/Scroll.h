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
	/// <param name="image">画像</param>
	/// <param name="imageSize">画像サイズ</param>
	/// <param name="drawNum">描画数</param>
	/// <param name="scrollSpeed">スクロール速度</param>
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

