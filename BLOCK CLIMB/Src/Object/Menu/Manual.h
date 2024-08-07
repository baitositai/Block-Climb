#pragma once

class MenuScene;

class Manual
{

public:

	Manual(void);
	~Manual(void);

	static constexpr int MANUAL_TYPE = 4;

	void Init(MenuScene* parent);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	bool isStick_;
	int manuSle_;
	int imgManual_[MANUAL_TYPE];
	MenuScene* menu_;

};

