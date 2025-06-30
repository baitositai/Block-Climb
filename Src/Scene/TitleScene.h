#pragma once
#include <string>
#include "../Application.h"
#include "../Object/Game/PlayerBase.h"
#include "../Object/Game/RabbitText/RabbitText.h"
#include "SceneBase.h"

class BackGround;
class TitleGround;
class TitlePlayer;
class FadeText;
class RabbitText;
class BlockBase;

class TitleScene : public SceneBase
{

public: 
	
	//�t�H���g�T�C�Y
	static constexpr int FONT_SIZE = 32;

	//�摜�T�C�Y
	static constexpr int LOGO_SIZE_X = 682;
	static constexpr int LOGO_SIZE_Y = 512;

	//BGM�̉���
	static constexpr int BGM_VOLUME = 70;

	//�u���b�N�̐����J�E���g
	static constexpr float BLOCK_CREATE_CNT = 1.5f;

	//�h�炷���g��
	static constexpr float AMPLITUDE = 0.3f;

	//�h�炷�U��
	static constexpr float FREQUENCY = 5.0f;

	//�e�L�X�g�J���[
	static constexpr int TEXT_COLOR = 0xffffff;

	//�e�L�X�g�t�H���g�T�C�Y
	static constexpr int TEXT_FONT_SIZE = 32;

	//�e�L�X�g�t�H���g����
	static constexpr int TEXT_FONT_THICK = 6;

	//�^�C�g�����S���W
	static constexpr int LOGO_POS_X = Application::SCREEN_SIZE_X / 2 - LOGO_SIZE_X / 2;
	static constexpr int LOGO_POS_Y = Application::SCREEN_SIZE_Y / 2 - 335;

	//���r�b�g���W
	static constexpr int RAB_POS_X = 30;
	static constexpr int RAB_POS_Y = Application::SCREEN_SIZE_Y - RabbitText::RABBIT_SIZE_Y;

	//���r�b�g�����o���ʒu
	static constexpr int RAB_SPEECH_POS_X = 40 + RabbitText::RABBIT_SIZE_X;
	static constexpr int RAB_SPEECH_POS_Y = Application::SCREEN_SIZE_Y - RabbitText::SPEECH_SIZE_Y + 5;

	//���r�b�g�e�L�X�g�ʒu
	static constexpr int RAB_TEXT_POS_X = 70 + RabbitText::RABBIT_SIZE_X;
	static constexpr int RAB_TEXT_POS_Y = Application::SCREEN_SIZE_Y - RabbitText::RABBIT_SIZE_Y + 80;	

	//���b�Z�[�W�e�L�X�g�ʒu
	static constexpr int MES_POS_Y = Application::SCREEN_SIZE_Y / 5 * 4;
											
	TitleScene(void);
	~TitleScene(void) override;

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	/// <summary>
	/// �e�L�X�g�\���m�F
	/// </summary>
	/// <param name="value"></param>�\�����邩�ۂ�
	void SetIsText(bool value);

	//�E�T�M�̕`��
	void RabbitDraw();

	//�u���b�N�𐶐����Ԃ�
	BlockBase* GetValidBlock();

	//�^�C�g�����b�Z�[�W�̈ʒu��Ԃ�
	static Vector2 GetTitlePosMes(const std::string & mes);

private:

	//�t�H���g
	int font_;

	//�u���b�N�����p�J�E���g
	float blockCreateCnt_;

	//�e�L�X�g�\���p
	bool isText_;

	//�e�L�X�g���W
	Vector2 textPos_;

	//���S�摜�̓ǂݍ���
	int imgLogo_;

	//�^�C�g���w�i
	BackGround* back_;

	//�n��
	TitleGround* ground_;

	//�v���C�L�����N�^�[����
	TitlePlayer* player_[static_cast<int>(PlayerBase::PLAYER_TYPE::MAX)];

	//�t�F�[�h�e�L�X�g
	FadeText* fadeText_;

	//�E�T�M
	RabbitText* rabbit_;

	//�u���b�N
	std::vector<BlockBase*> blocks_;
	
	//�e�L�X�g�����ݒ�
	void InitText();

	//�e�L�X�g�p�X�V����
	void TextUpdate();

	//�u���b�N�p�X�V����
	void BlockUpdate();

};
