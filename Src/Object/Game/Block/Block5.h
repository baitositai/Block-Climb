#pragma once
#include "BlockBase.h"

class Moon;

class Block5:public BlockBase
{

public:
	//�����`��
	static constexpr int CENTER_DRAW_X = 4;

	//�~�m�̏����ʒu
	static constexpr int MINO_DEFAULT_POS = -500;

	//�u���b�N�̃Z�b�g���
	enum class STATE
	{
		NONE,			//�Ȃ�
		NO_SET,
		SET				//�u���b�N��u���ꏊ
	};

	//�R���X�g���N�^
	Block5();

	//�f�X�g���N�^
	~Block5();

	//������
	void Init(LevelManager* parent) override;

	//�X�V
	void Update() override;
	
	//�Փˎ��̍X�V
	void HitUpdate(Vector2 pos) override;
	
	//���Z�b�g
	void Reset(void) override;
	
	//�X�e�[�W����
	void StageCreate(void) override;

	//�X�e�[�W��csv�f�[�^�̓ǂݍ���
	void LoadStageCsvData(void) override;

	//�z�u�G���A��csv�f�[�^�ǂݍ���
	void LoadPositionCsvData(void) override;

	//�z�u�G���A�̕`��
	void PutBlockZoneDraw() override;

	//�u���b�N�̔z�u
	void BlockSet(int MinoX,int MinoY,int MinoType_) override;
	
private:

	//�u���b�N�u���]�[���pCSV�f�[�^�ǂݍ���
	std::string putZoneCsvData_;

	//CSV�f�[�^�̊i�[�p�z��
	std::vector<std::vector<int>> setBlockField_;	

	//�u���b�N�u���]�[���̏�ԗp�z��
	std::vector<std::vector<STATE>> setBlockRole_;	

	//���̃C���X�^���X����
	Moon* moon_;

};