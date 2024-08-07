#include <DxLib.h>
#include <cmath>
#include "Collision.h"
#include "AsoUtility.h"

//中心座標の短径の衝突判定
bool Collision::IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2)
{
	Vector2 diff;
		diff.x = centerPos1.x - centerPos2.x;
		diff.y = centerPos1.y - centerPos2.y;
	if (fabsf(diff.x) > size1.x / 2 + size2.x / 2 ||
		fabsf(diff.y) > size1.y / 2 + size2.y / 2)
	{
		//入ってない
		return false;
	}

	else
	{
		//入ってる
		return true;
	}
}

//円同士の衝突判定
bool Collision::IsCollisionCircle(Vector2 centerPos1, int size1, Vector2 centerPos2, int size2)
{
	Vector2 pos;

	pos.x = centerPos1.x - centerPos2.x;
	pos.y = centerPos1.y - centerPos2.y;

	return 	(std::hypot(pos.x, pos.y) <= size1 + size2);
	;
}

//円と矩形の判定
bool Collision::IsCollisionBoxCircle(Vector2 pos1, Vector2 size1, Vector2 pos2, float radius2)
{
	Vector2 righttop = pos1;
	righttop.x += size1.x / 2;
	righttop.y -= size1.y / 2;
	righttop = AsoUtility::V2Sub(pos2, righttop);
	int rightTop = std::hypot(righttop.x, righttop.y);

	Vector2 rightdown = pos1;
	rightdown.x += size1.x / 2;
	rightdown.y += size1.y / 2;
	rightdown = AsoUtility::V2Sub(pos2, rightdown);
	int rightDown = std::hypot(rightdown.x, rightdown.y);

	Vector2 lefttop = pos1;
	lefttop.x -= size1.x / 2;
	lefttop.y -= size1.y / 2;
	lefttop = AsoUtility::V2Sub(pos2, lefttop);
	int leftTop = std::hypot(lefttop.x, lefttop.y);

	Vector2 leftdown = pos1;
	leftdown.x -= size1.x / 2;
	leftdown.y += size1.y / 2;
	leftdown = AsoUtility::V2Sub(pos2, leftdown);
	int leftDown = std::hypot(leftdown.x, leftdown.y);

	//-----------------------------------------------------------

	//衝突していたら色を変える
	auto diffX = (pos1.x - pos2.x) ;/////終点から始点を引く///////
	auto diffY = (pos1.y - pos2.y) ;/////終点から始点を引く///////

	if (rightTop   <= radius2 ||
		rightDown <= radius2 ||
		leftTop   <= radius2 ||
		leftDown  <= radius2 ||

		(fabsf(diffX) < radius2 
	  && fabsf(diffY) < radius2 + size1.y / 2) ||
		(fabsf(diffX) < radius2 + size1.x /2
	  && fabsf(diffY) < size1.y / 2 ))
	{
		return true;
	}


	//衝突している
	return false;
}