#pragma once
#include <string>
#include "../../Common/Vector2.h"
#include "../../Common/Data.h"
#include "../../Scene/MenuScene.h"
#include "Challenge.h"

class Text
{
public:

	//�����ʒu
	static constexpr int MENU_FIRST_POS_X = Application::SCREEN_SIZE_X / 8;
	static constexpr int MENU_FIRST_POS_Y = Application::SCREEN_SIZE_Y / 5;

	static constexpr int EXP_FIRST_POS_X = Application::SCREEN_SIZE_X / 16;
	static constexpr int EXP_FIRST_POS_Y = Application::SCREEN_SIZE_Y - 80;

	//�ʏ�
	static constexpr int FONT_SIZE = 60;

	//�t�H���g����
	static constexpr int FONT_THICKNESS = 3;

	//�I��
	static constexpr int SELECT_FONT_SIZE = 75;

	//�����p
	static constexpr int EXPLANATION_FONT_SIZE = 32;

	//�����Ԋu
	static constexpr int FONT_INTERVAL = static_cast<int>(FONT_SIZE * 1.5f);

	//�{�[�_�[
	static constexpr int BORDER = 3;

	//���T�C�Y
	static constexpr int BOX_SIZE_X = 320;
	static constexpr int BOX_SIZE_Y = 120;

	//���ʒu
	static constexpr int BOX_POS_X = Application::SCREEN_SIZE_X / 2 + 150;
	static constexpr int BOX_POS_Y = 150;

	//�V�L�^�e�L�X�g�`��ʒu
	static constexpr int NEW_RECO_TEXT_POS_X = BOX_POS_X + 10;
	static constexpr int NEW_RECO_TEXT_POS_Y = BOX_POS_Y + EXPLANATION_FONT_SIZE;

	//�{�^��UI�A���t�@�l
	static constexpr int BUTTON_UI_ALPHA = 150;

	//�{�^��UI����
	static constexpr int BUTTON_UI_LENGTH = 18 ;

	//�{�^��UI�p�����W����
	static constexpr int BUTTON_UI_BOX_L_TOP_X = Application::SCREEN_SIZE_X;
	static constexpr int BUTTON_UI_BOX_L_TOP_Y = 0;

	//�{�^��UI�p�����W�E��
	static constexpr int BUTTON_UI_BOX_R_BOTTOM_X = Application::SCREEN_SIZE_X;
	static constexpr int BUTTON_UI_BOX_R_BOTTOM_Y = EXPLANATION_FONT_SIZE + 8;

	//�R���X�g���N�^
	Text();

	//�f�X�g���N�^
	~Text();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent"></param>�e�C���X�^���X
	void Init(MenuScene* parent);

	//�ϐ��̏�����
	void Reset();

	//���
	void Release();

	/// <summary>
	/// �e�L�X�g�̃X�N���[������
	/// </summary>
	/// <param name="pos"></param>�ʒu
	/// <param name="length"></param>����
	/// <returns></returns>
	Vector2 TextScroll(const Vector2 pos ,const int length);

	/// <summary>
	/// �w�肵���e�L�X�g�T�C�Y��Ԃ�
	/// </summary>
	/// <param name="index"></param>�e�L�X�g�ԍ�
	/// <returns></returns>
	int GetMenuTextSize(const int index);

	//�V�L�^�̕`��
	void NewRecodeDraw();

	//���j���[�e�L�X�g�`��
	void MenuText();

	//�`�������W�p�I���e�L�X�g�`��
	void ChallengeText();

	//�{�^��UI�`��
	void ButtonUIDraw();

private:

	//�{�^��UI�t�H���g
	int buttonUIFont_;

	//�ʏ�t�H���g
	int normalFont_;

	//�I��p�e�L�X�g
	int selectFont_;

	//�����p�e�L�X�g
	int explanationFont_;

	//�V�L�^�p�̃e�L�X�g
	std::string newRecodeText_;

	//�{�^��UI�e�L�X�g
	std::string buttonUIText_;

	//���j���[�e�L�X�g
	std::string menuText_[static_cast<int>(MenuScene::STATE::NONE)];

	//���j���[�����p�e�L�X�g
	std::string menuExpText_[static_cast<int>(MenuScene::STATE::NONE)];

	//�`�������W�����p�e�L�X�g
	std::string chlExpText_[static_cast<int>(Data::LEVEL::MAX)];

	//�`��p���W
	Vector2 pos_;

	//�X�N���[���p�ϐ�
	int cnt_;

	//�C���X�^���X
	MenuScene* menu_;	
	
	//�t�H���g�̐ݒ�
	void SetFont();

	//�e�L�X�g�̐ݒ�
	void TextData(); 

};

