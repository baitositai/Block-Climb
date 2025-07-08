#pragma once
#include "../Common/Vector2.h"

class Collision
{
public:
	//’†SÀ•W‚Ì’ZŒ`‚ÌÕ“Ë”»’è
	static bool IsCollisionRectCenter(const Vector2 centerPos1, const Vector2 size1, const Vector2 centerPos2, const Vector2 size2);

	//‰~“¯m‚ÌÕ“Ë”»’è
	static bool IsCollisionCircle(const Vector2 centerPos1, const int size1, const Vector2 centerPos2, const int size2);

	//‰~‚Æ‹éŒ`‚ÌÕ“Ë”»’è
	static bool IsCollisionBoxCircle(Vector2 pos1, Vector2 size1, Vector2 pos2, float radius2);

};

