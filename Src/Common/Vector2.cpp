#include <tgmath.h>
#include "Vector2.h"
#include "Vector2F.h"

// コンストラクタ
Vector2::Vector2(void)
{
	x = 0;
	y = 0;
}

// コンストラクタ
Vector2::Vector2(int vX, int vY)
{
	x = vX;
	y = vY;
}

Vector2::~Vector2(void)
{
}

Vector2F Vector2::ToVector2F(void)
{
	Vector2F ret;

	ret.x = static_cast<float>(roundf(x));
	ret.y = static_cast<float>(roundf(y));

	return ret;
}
