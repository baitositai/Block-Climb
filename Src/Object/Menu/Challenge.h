#pragma once
#include <string>
#include "../../Common/Data.h"
#include "../../Common/Vector2.h"

class MenuScene;

class Challenge
{
public:

	//�X�e�[�W�I��z��
	static constexpr int STAGE_X = 3;
	static constexpr int STAGE_Y = 2;

	//�h�炷���g��
	static constexpr float AMPLITUDE = 0.5f;

	//�h�炷�U��
	static constexpr float FREQUENCY = 10.0f;

	//�ۑ�摜�g�嗦
	static constexpr float SLE_IMG_RATE = 1.2f;

	//��i�ۑ�UI�̍��W�ʒu
	static constexpr int SLE_UIS_UP_X = Application::SCREEN_SIZE_X / 4;
	static constexpr int SLE_UIS_UP_Y = Application::SCREEN_SIZE_X / 8 + 20;

	//���i�ۑ�UI�̍��W�ʒu
	static constexpr int SLE_UIS_DOWN_X = Application::SCREEN_SIZE_X / 4;
	static constexpr int SLE_UIS_DOWN_Y = Application::SCREEN_SIZE_X / 8 * 3;

	//�|�C���g���[�J�����W
	static constexpr int POINT_LOCAL_POS = 75;

	//�R���X�g���N�^
	Challenge();

	//�f�X�g���N�^
	~Challenge();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent"></param>�e�C���X�^���X���󂯎��
	void Init(MenuScene* parent);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���
	void Release();

	/// <summary>
	/// �I���������x����Ԃ�
	/// </summary>
	/// <returns></returns>�ۑ背�x��
	Data::LEVEL GetChallengeData();

private:

	//�摜�֌W
	int imgSle_[static_cast<int>(Data::LEVEL::MAX)];
	int imgPoint_;

	//�e�L�X�g
	std::string expText_[static_cast<int>(Data::LEVEL::MAX)];

	//�I�����Ă���X�e�[�W
	Vector2 sleCnt_;

	//�I�����Ă�X�e�[�W�̃f�[�^�i�[
	Data::LEVEL sleData_;

	//�|�C���g�p���W
	Vector2 pointPos_;

	//�C���X�^���X
	MenuScene* menu_;

	//�X�N���[��
	int scrollCnt_;

	//�X�e�B�b�N����
	bool isStick_;	
	
	//�ǂݍ���
	void Load();

};

