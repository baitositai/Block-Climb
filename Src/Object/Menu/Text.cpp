#include <DxLib.h>
#include "../../Application.h"
#include "../../Common/Data.h"
#include "../../Scene/MenuScene.h"
#include "Text.h"

Text::Text()
{
	buttonUIFont_ = 0;
	cnt_ = 0;
	explanationFont_ = 0;
	menu_ = nullptr;
	normalFont_ = 0;
	selectFont_ = 0;
}

Text::~Text()
{
}

void Text::Init(MenuScene* parent)
{
	menu_ = parent;

	//フォントの設定
	SetFont();

	//テキストの設定
	TextData();

	Reset();
}

void Text::Reset()
{
	pos_ = { EXP_FIRST_POS_X,
			 EXP_FIRST_POS_Y };

	cnt_ = 0;
}

void Text::SetFont()
{
	buttonUIFont_ = CreateFontToHandle("ベストテンDOT", EXPLANATION_FONT_SIZE, FONT_THICKNESS);
	normalFont_ = CreateFontToHandle("ベストテンDOT", FONT_SIZE, FONT_THICKNESS);
	selectFont_ = CreateFontToHandle("ベストテンDOT", SELECT_FONT_SIZE, FONT_THICKNESS);
	explanationFont_ = CreateFontToHandle("ベストテンDOT", EXPLANATION_FONT_SIZE, FONT_THICKNESS);
}

void Text::TextData()
{
	//ボタンUIテキストの設定
	buttonUIText_ =
		"決定/B・SPACE. 選択/STICK・↑↓. 戻る/A・ENTER";

	//新記録のテキスト
	newRecodeText_ =
		"マラソンの最高記録";

	//メニューシーンテキストの設定
	menuText_[static_cast<int>(MenuScene::STATE::MARASON)] = "マラソン";
	menuText_[static_cast<int>(MenuScene::STATE::MANYUAL)] = "マニュアル";
	menuText_[static_cast<int>(MenuScene::STATE::SELECT)] = "チャレンジ";
	menuText_[static_cast<int>(MenuScene::STATE::TAG)] = "協力プレイ";
	menuText_[static_cast<int>(MenuScene::STATE::CREDIT)] = "クレジット動画";

	//メニューシーン説明用テキストの設定
	menuExpText_[static_cast<int>(MenuScene::STATE::MARASON)] =
		"ひたすらブロックを積み上げて上へと目指す1人用のモード。限界を超えてさらなる高みへ！！";
	menuExpText_[static_cast<int>(MenuScene::STATE::MANYUAL)] =
		"遊び方の確認や操作を説明するよ";
	menuExpText_[static_cast<int>(MenuScene::STATE::SELECT)] =
		"ステージごとにお題が課せられているチャレンジモード。君はいくつクリアできるかな？";
	menuExpText_[static_cast<int>(MenuScene::STATE::TAG)] =
		"開発中";
	menuExpText_[static_cast<int>(MenuScene::STATE::CREDIT)] =
		"このゲームのクレジット動画を再生するよ";

	//チャレンジシーン説明用テキストの設定
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL1)] =
		"ブロックを積み重ねて上へ登れ！うっかりブロックでプレイヤーをつぶさないように要注意だ！";
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL2)] =
		"家の型どおりにブロックを積み重ねよう！制限時間の3分以内に家を完成させよう！";
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL3)] =
		"ラインを作って消して本家ならではの遊び！爆発するから気を付けよう！";
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL4)] =
		"空から火の玉が落ちてくる！火の玉を避けながら上へ目指そう！";
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL5)] =
		"猫？の型どおりにブロックを積み重ねよう！このステージでは火の玉も落ちてくるから要注意だ！";
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL6)] =
		"ふざけるなと言いたくなるような少し理不尽難易度！クリア出来たら制作者を見つけて！ジュース奢るから";
}

void Text::ButtonUIDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, BUTTON_UI_ALPHA);
	int length = buttonUIText_.size() * BUTTON_UI_LENGTH;
	Vector2 leftTop{ BUTTON_UI_BOX_L_TOP_X - length,BUTTON_UI_BOX_L_TOP_Y };
	Vector2 rightBottom{ BUTTON_UI_BOX_R_BOTTOM_X,BUTTON_UI_BOX_R_BOTTOM_Y};

	DrawBox(leftTop.x, leftTop.y,
		rightBottom.x, rightBottom.y,
		0x000000,
		true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawStringToHandle(leftTop.x, leftTop.y, buttonUIText_.c_str(), 0xffffff, buttonUIFont_);
}

void Text::NewRecodeDraw()
{
	Vector2 boxPos = {BOX_POS_X,BOX_POS_Y};
	Vector2 boxSize = { BOX_SIZE_X, BOX_SIZE_Y };

	for (int i = 1; i >= 0; i--)
	{
		int color = 0x000000;
		if (i == 1) { color = 0xffffff; }

		DrawBox(boxPos.x - BORDER * i,
			boxPos.y - BORDER * i,
			boxPos.x + boxSize.x + BORDER * i,
			boxPos.y + boxSize.y + BORDER * i,
			color,
			true);
	}
	int recode = Data::GetInstance().GetMarasonData();
	DrawStringToHandle(boxPos.x, boxPos.y, newRecodeText_.c_str(), 0xff00ff, explanationFont_);
	DrawFormatStringToHandle(
		NEW_RECO_TEXT_POS_X, 
		NEW_RECO_TEXT_POS_Y, 
		0xffffff, selectFont_,
		"%d m", 
		recode);
}

void Text::Release()
{
	DeleteFontToHandle(explanationFont_);
	DeleteFontToHandle(selectFont_);
	DeleteFontToHandle(normalFont_);
	DeleteFontToHandle(buttonUIFont_);
}

void Text::MenuText()
{
	for (int i = 0; i < static_cast<int>(MenuScene::STATE::NONE); i++)
	{
		int fontIntevel = FONT_INTERVAL * i;
		int color = 0xffffff;
		int fontType = normalFont_;

		//座標の設定
		Vector2 pos = { MENU_FIRST_POS_X,
						MENU_FIRST_POS_Y + fontIntevel };

		//フォントの設定
		if (i == static_cast<int>(menu_->GetMenuSetState())) 
		{ 
			color = 0x00ffff;
			fontType = selectFont_;
		}
		//選択テキストの表示
		DrawStringToHandle(pos.x, pos.y, menuText_[i].c_str(), color, fontType);
		
		pos_ = { EXP_FIRST_POS_X,
				 EXP_FIRST_POS_Y};

		if (i == static_cast<int>(menu_->GetMenuSetState()))
		{
			int length = menuExpText_[i].size() * EXPLANATION_FONT_SIZE / 2;
			
			if (EXP_FIRST_POS_X + length >
				Application::SCREEN_SIZE_X)
			{
				pos_ = TextScroll(pos_, length);
			}
			//説明テキストの表示
			DrawStringToHandle(pos_.x, pos_.y, menuExpText_[i].c_str(), 0xffffff, explanationFont_);
		}
	}
}

void Text::ChallengeText()
{
	for (int i = 0; i < static_cast<int>(Data::LEVEL::MAX); i++)
	{
		pos_ = { EXP_FIRST_POS_X,
				 EXP_FIRST_POS_Y };

		int length = chlExpText_[i].size() * EXPLANATION_FONT_SIZE / 2;

		if (i == static_cast<int>(menu_->GetChallengeState()))
		{
			if (EXP_FIRST_POS_X + length >
				Application::SCREEN_SIZE_X)
			{
				pos_ = TextScroll(pos_, length);
			}
			DrawStringToHandle(pos_.x, pos_.y, chlExpText_[i].c_str(), 0xffffff, explanationFont_);
		}
	}
}

Vector2 Text::TextScroll(const Vector2 pos ,const int length)
{
	Vector2 scrollPos = pos;

	if (EXP_FIRST_POS_X + length >
		Application::SCREEN_SIZE_X)
	{
		cnt_++;
		scrollPos.x -= cnt_;

		if (-length > scrollPos.x)
		{
			cnt_ = 0;
		}
	}
	return scrollPos;
}

int Text::GetMenuTextSize(const int index)
{
	return menuText_[index].size();
}



