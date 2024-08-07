#pragma once

class MenuScene;

class TagPlay
{
public:

	TagPlay(void);
	~TagPlay(void);

	void Init(MenuScene* parent);
	void Update(void);
	void Draw(void);
	void Release(void);
	void Reset();
	void Load();

private:

	MenuScene* menu_;
};

