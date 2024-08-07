#pragma once
#include "SceneBase.h"
#include "../Object/Game/PlayerBase.h"

class TitleBackGround;
class TitleGround;
class TitlePlayer;
class Credit;
class FadeText;
class RabbitText;
class BlockBase;

class TitleScene : public SceneBase
{

public:static 
	
	//フォントサイズ
	constexpr int FONT_SIZE = 32;

	//画像サイズ
	static constexpr int LOGO_SIZE_X = 682;
	static constexpr int LOGO_SIZE_Y = 512;

	TitleScene(void);
	~TitleScene(void) override;

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void SetText();
	void SetIsText(bool value);

	//ウサギの描画
	void RabbitDraw();

	//ブロック生成
	BlockBase* GetValidBlock();

private:

	int font_;

	float step_;

	//テキスト表示用
	bool isText_;

	//テキスト座標
	Vector2 textPos_;

	//ロゴ画像の読み込み
	int imgLogo_;

	//インスタンス生成
	TitleBackGround* back_;
	TitleGround* ground_;
	TitlePlayer* player_[static_cast<int>(PlayerBase::PLAYER_TYPE::MAX)];
	FadeText* fadetext_;
	RabbitText* rabbit_;
	Credit* credit_;
	std::vector<BlockBase*> blocks_;

};
