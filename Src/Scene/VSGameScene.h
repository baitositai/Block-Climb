#pragma once
#include "GameScene.h"

class VSGameScene :public GameScene
{
public:

	VSGameScene(void);
	~VSGameScene(void) override;

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;
	void Reset(void);
};

