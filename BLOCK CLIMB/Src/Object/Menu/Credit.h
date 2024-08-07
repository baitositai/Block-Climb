#pragma once

class MenuScene;

class Credit
{
public:

	Credit();
	~Credit();

	void Init(MenuScene* parent);
	void Update();
	void Draw();
	void Release();

private:

	int movie_;
	
	bool isPlay_;

	MenuScene* menu_;

};

