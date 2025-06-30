#pragma once
#include <string>
#include "SceneBase.h"
#include "../Application.h"
#include "../Common/Data.h"
#include "../Common/Vector2.h"
#include "../Object/Menu/MenuPlayer.h"

class Scroll;
class Challenge;
class Manual;
class TagPlay;
class Credit;
class Text;
class MenuPlayer;
class BlockBase;

class MenuScene : public SceneBase
{
public:

	enum class STATE
	{
		MARASON,
		SELECT,
		TAG,
		CREDIT,
		MANYUAL,
		NONE
	};

	//�摜�T�C�Y
	static constexpr int BRICH_SIZE_X = 750;
	static constexpr int BRICH_SIZE_Y = 750;

	//�e�L�X�g���T�C�Y
	static constexpr int TEXT_BOX_SIZE_X = Application::SCREEN_SIZE_X;
	static constexpr int TEXT_BOX_SIZE_Y = 160;

	//�u���b�N�̐����J�E���g
	static constexpr float BLOCK_CREATE_CNT = 1.5f;

	//�e�L�X�g���A���t�@�l
	static constexpr int TEXT_BOX_ALPHA = 150;

	//�w�i�`�搔
	static constexpr int BACK_DRAW_NUM = 3;

	//�w�i�X�N���[���X�s�[�h
	static constexpr float BACK_SCROLL_SPEED = 0.3f;

	//���j���[��BGM����
	static constexpr int BGM_VOLUME = 70;

	MenuScene();
	~MenuScene() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void Load();
	void Reset();

	/// <summary>
	/// �Q�[���V�[���֑J��
	/// </summary>
	/// <param name="level"></param>�Q�[���̃��x��
	void ChangeGameScene(const Data::LEVEL level);	
	
	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="state"></param>���
	void SetState(const STATE state);	
	
	//�e�L�X�g�̏�����
	void TextReset();

	/// <summary>
	/// �|�C���g���W�̐ݒ�
	/// </summary>
	/// <param name="pos"></param>���W
	void SetPointPos(const Vector2 pos);

	/// <summary>
	/// �v���C���[�̏�Ԃ�ݒ�
	/// </summary>
	/// <param name="state"></param>�v���C���[�̈ړ����
	void SetPlayerState(const MenuPlayer::MOVE_STATE state);

	//�X�e�[�g��Ԃ�
	STATE GetMenuState();

	//�I�����Ă�X�e�[�g��Ԃ�
	STATE GetMenuSetState();

	//�`�������W�̑I�����Ă���X�e�[�g��Ԃ�
	Data::LEVEL GetChallengeState();

private:

	//�w�i�摜
	int imgBack_;

	//�|�C���g�摜
	int imgPoint_;

	//���j���[�I��p�J�E���g
	int menuCnt_;

	//�X�e�B�b�N�̔���
	bool isStick_;

	//�u���b�N�����J�E���g
	float blockCreateCnt_;

	//�|�C���g�p���W
	Vector2 pointPos_;
	
	//��ʃX�e�[�g
	STATE state_;

	//�I���X�e�[�g
	STATE sleState_;

	//�X�N���[��
	Scroll* scroll_;

	//�`�������W�ۑ�̑I��
	Challenge* challenge_;

	//�}�j���A��
	Manual* manual_;

	//�^�b�O�v���C
	TagPlay* tag_;

	//�N���W�b�g
	Credit* credit_;

	//�e�L�X�g
	Text* text_;

	//���j���[��ʗp�v���C���[
	MenuPlayer* player_;

	//�u���b�N
	std::vector<BlockBase*> blocks_;	
	
	//�w�i�摜�̃X�N���[������
	void InitBackImage();

	//���j���[��ʂł̏���
	void MenuUpdate();

	//�|�C���g�摜�̕`��
	void PointDraw();

	//�e�L�X�g�\���̔w�i�`��
	void TextBoxDraw();

	//�u���b�N����
	BlockBase* GetValidBlock();

	//�|�C���g�̍��W��Ԃ�
	Vector2 GetPointPos(const int index);

	//�u���b�N�Ɋւ��鏈��
	void BlockUpdate();
};

