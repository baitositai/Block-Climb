#pragma once
#include <string>

class GameScene;

class Pause
{
public:

	//�|�[�Y�̉�ʍ���
	enum class CHANGE
	{
		RETRY,
		MENU,
		TITLE,
		MAX
	};	
	
	//�t�H���g�T�C�Y
	static constexpr int FONT_SIZE = 48;
	static constexpr int SELECT_FONT_SIZE = 54;

	//�t�H���g����
	static constexpr int FONT_THICK = 3;

	//�摜�T�C�Y
	static constexpr int BOARD_SIZE_X = 297;
	static constexpr int BOARD_SIZE_Y = 345;

	//�g��X�s�[�h
	static constexpr float EXPANSION_SPEED = 0.1f;

	//�ő�T�C�Y
	static constexpr float BOARD_SIZE_MAX = 1.0f;

	//�j���[���R�[�h�`��ʒu
	static constexpr int NEW_RECODE_POS_X = Application::SCREEN_SIZE_X / 4;
	static constexpr int NEW_RECODE_POS_Y = Application::SCREEN_SIZE_Y / 5;

	//�j���[���R�[�h�p�C���^�[�o��
	static constexpr int NEW_RECODE_INTERVAL = 1;

	//�h�炷���g��
	static constexpr float AMPLITUDE = 0.3f;

	//�h�炷�U��
	static constexpr float FREQUENCY = 5.0f;

	//�|�[�YUI�ʒu
	static constexpr int PAUSE_UI_POS_X = Application::SCREEN_SIZE_X / 2;
	static constexpr int PAUSE_UI_POS_Y = Application::SCREEN_SIZE_Y / 2- 200;

	//�e�L�X�g�̕`��Ԋu
	static constexpr int TEXT_INTERVAL = static_cast<int>(FONT_SIZE * 1.7f);

	//�e�L�X�g�`��ʒu
	static constexpr int TEXT_POS_Y = 250;

	//�R���X�g���N�^
	Pause();

	//�f�X�g���N�^
	~Pause();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent"></param>�e�C���X�^���X
	void Init(GameScene* parent);

	//�ϐ��̏�����
	void Reset();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���
	void Release();

	//�摜�̕`��
	void NewRecodeDraw();

	/// <summary>
	/// �V�L�^UI�`��̋���
	/// </summary>
	/// <param name="value"></param>����
	void SetIsNewRecode(const bool value);

	//�V�L�^UI�`�拖�̊m�F
	bool IsNewRecode();

private:

	bool isStick_;

	//�|�[�YUI�摜
	int imgPause_;

	//�T�C�Y��
	float size_;

	//�摜
	int imgBoard_;

	//�I��p�J�E���g
	int cnt_;

	//�e�L�X�g
	std::string text_[static_cast<int>(CHANGE::MAX)];

	//�t�H���g
	int font_;

	//�Z���N�g�t�H���g
	int sleFont_;

	//�摜�ǂݍ���
	int imgNewRecode_;

	//�V�L�^�̕`�拖��
	bool isNewRecode_;

	//�I�����Ă�X�e�[�g
	CHANGE state_;

	//�C���X�^���X
	GameScene* game_;	
	
	//�e�L�X�g�̐ݒ�
	void SetText();

	//�t�H���g�̐ݒ�
	void SetFont();

	//�I������
	void Select();

	//�̊g��
	void BoardExpansion();

	//�؂�ւ�����
	void Change();
};

