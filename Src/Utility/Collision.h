#pragma once
#include "../Common/Vector2.h"

class Collision
{
public:
	//���S���W�̒Z�`�̏Փ˔���
	static bool IsCollisionRectCenter(const Vector2 centerPos1, const Vector2 size1, const Vector2 centerPos2, const Vector2 size2);

	//�~���m�̏Փ˔���
	static bool IsCollisionCircle(const Vector2 centerPos1, const int size1, const Vector2 centerPos2, const int size2);

	//�~�Ƌ�`�̏Փ˔���
	static bool IsCollisionBoxCircle(Vector2 pos1, Vector2 size1, Vector2 pos2, float radius2);

};

