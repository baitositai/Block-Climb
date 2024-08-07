#pragma once
#include<vector>
#include"Vector2.h"
#include"Vector2F.h"

class Scroll
{
public:
	Scroll();
	~Scroll();

	void Init(int image, Vector2 imageSize, int drawNum, float scrollSpeed);
	void Update();
	void Draw();
	void Release();

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

