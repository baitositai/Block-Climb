#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon1 : public Moon
{
public:

	Moon1();
	~Moon1();

	void Reset() override;
	void Update() override;
	void Draw() override;

};

