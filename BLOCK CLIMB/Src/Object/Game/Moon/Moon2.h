#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon2 : public Moon
{
public:

	Moon2();
	~Moon2();

	void Reset() override;
	void Update() override;
	void Draw() override;

};


