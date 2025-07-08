#pragma once



class Data
{
public:

	enum class LEVEL
	{
		LEVEL1,
		LEVEL2,
		LEVEL3,
		LEVEL4,
		LEVEL5,
		LEVEL6,
		MAX,
		MARASON,
		VS
	};
	
	//�J�����̃T�C�Y
	static constexpr int CAMERA_WIDTH = 150;
	static constexpr int CAMERA_HEIGHT = 150;

	//�f�t�H���g�f�[�^
	static constexpr int DEFAULT_DATA = 2;

	//�����o�[�֐�
	Data(void);
	~Data(void);

	//�C���X�^���X�̐���
	//�V���O���g����
	static void CreateInstance(void);
	static Data& GetInstance(void);

	void SetDeta(int pos);
	int GetDeta(void);

	//�X�e�[�W�f�[�^���Ǘ�����
	void ChangeLevelData(LEVEL Data);
	LEVEL GetStageData(void);

	//�}���\���̋L�^���Ǘ�����
	int GetMarasonData();
	void SetMarasonData(int value);

private:

	//�}���\���L�^
	int marasonData_;

	//�ϐ�
	int Data_;

	LEVEL type_;

	//�V���O���g����
	static Data* instance_;

	//�����o�[�֐�
	//---------------------------------------
	//�R�s�[�R���X�g���X�^
	Data(const Data& ins);

	void Destory(void);
};

