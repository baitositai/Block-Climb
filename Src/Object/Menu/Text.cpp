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

	//�t�H���g�̐ݒ�
	SetFont();

	//�e�L�X�g�̐ݒ�
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
	buttonUIFont_ = CreateFontToHandle("�x�X�g�e��DOT", EXPLANATION_FONT_SIZE, FONT_THICKNESS);
	normalFont_ = CreateFontToHandle("�x�X�g�e��DOT", FONT_SIZE, FONT_THICKNESS);
	selectFont_ = CreateFontToHandle("�x�X�g�e��DOT", SELECT_FONT_SIZE, FONT_THICKNESS);
	explanationFont_ = CreateFontToHandle("�x�X�g�e��DOT", EXPLANATION_FONT_SIZE, FONT_THICKNESS);
}

void Text::TextData()
{
	//�{�^��UI�e�L�X�g�̐ݒ�
	buttonUIText_ =
		"����/B�ESPACE. �I��/STICK�E����. �߂�/A�EENTER";

	//�V�L�^�̃e�L�X�g
	newRecodeText_ =
		"�}���\���̍ō��L�^";

	//���j���[�V�[���e�L�X�g�̐ݒ�
	menuText_[static_cast<int>(MenuScene::STATE::MARASON)] = "�}���\��";
	menuText_[static_cast<int>(MenuScene::STATE::MANYUAL)] = "�}�j���A��";
	menuText_[static_cast<int>(MenuScene::STATE::SELECT)] = "�`�������W";
	menuText_[static_cast<int>(MenuScene::STATE::TAG)] = "���̓v���C";
	menuText_[static_cast<int>(MenuScene::STATE::CREDIT)] = "�N���W�b�g����";

	//���j���[�V�[�������p�e�L�X�g�̐ݒ�
	menuExpText_[static_cast<int>(MenuScene::STATE::MARASON)] =
		"�Ђ�����u���b�N��ςݏグ�ď�ւƖڎw��1�l�p�̃��[�h�B���E�𒴂��Ă���Ȃ鍂�݂ցI�I";
	menuExpText_[static_cast<int>(MenuScene::STATE::MANYUAL)] =
		"�V�ѕ��̊m�F�⑀�����������";
	menuExpText_[static_cast<int>(MenuScene::STATE::SELECT)] =
		"�X�e�[�W���Ƃɂ��肪�ۂ����Ă���`�������W���[�h�B�N�͂����N���A�ł��邩�ȁH";
	menuExpText_[static_cast<int>(MenuScene::STATE::TAG)] =
		"�J����";
	menuExpText_[static_cast<int>(MenuScene::STATE::CREDIT)] =
		"���̃Q�[���̃N���W�b�g������Đ������";

	//�`�������W�V�[�������p�e�L�X�g�̐ݒ�
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL1)] =
		"�u���b�N��ςݏd�˂ď�֓o��I��������u���b�N�Ńv���C���[���Ԃ��Ȃ��悤�ɗv���ӂ��I";
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL2)] =
		"�Ƃ̌^�ǂ���Ƀu���b�N��ςݏd�˂悤�I�������Ԃ�3���ȓ��ɉƂ����������悤�I";
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL3)] =
		"���C��������ď����Ė{�ƂȂ�ł̗͂V�сI�������邩��C��t���悤�I";
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL4)] =
		"�󂩂�΂̋ʂ������Ă���I�΂̋ʂ�����Ȃ����֖ڎw�����I";
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL5)] =
		"�L�H�̌^�ǂ���Ƀu���b�N��ςݏd�˂悤�I���̃X�e�[�W�ł͉΂̋ʂ������Ă��邩��v���ӂ��I";
	chlExpText_[static_cast<int>(Data::LEVEL::LEVEL6)] =
		"�ӂ�����Ȃƌ��������Ȃ�悤�ȏ������s�s��Փx�I�N���A�o�����琧��҂������āI�W���[�X���邩��";
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

		//���W�̐ݒ�
		Vector2 pos = { MENU_FIRST_POS_X,
						MENU_FIRST_POS_Y + fontIntevel };

		//�t�H���g�̐ݒ�
		if (i == static_cast<int>(menu_->GetMenuSetState())) 
		{ 
			color = 0x00ffff;
			fontType = selectFont_;
		}
		//�I���e�L�X�g�̕\��
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
			//�����e�L�X�g�̕\��
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



