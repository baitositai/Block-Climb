#pragma once
#include <vector>
#include "BlockBase.h"
#include "../Gimic/Blast.h"
#include "../Gimic/FireBall.h"

class BlockMarason :public BlockBase
{
public:

	//�N���A����
	static constexpr int CREAL_LINE = 20;

	//���̔��������܂ł̃N�[������
	static constexpr float COOL_TIME = 10.0f;

	//�X�V���C��
	static constexpr int UPDATE_LINE = 10;

	//���C�������̍ő�l
	static constexpr int LINE_DELETE_MAX = 3;

	//�R���X�g���N�^
	BlockMarason();

	//�f�X�g���N�^
	~BlockMarason();

	//�ՓˍX�V����
	void HitUpdate(Vector2 pos) override;

	//���Z�b�g
	void Reset(void) override;

	//�X�e�[�W���쐬
	void StageCreate(void) override;

	//���C���폜
	void LineDelete(void) override;

	//�����̍X�V
	void HeightUpdate();

	//�w�肵���l���猻�݂̍����𒲂ׂ�
	void CheckHeight(int y) override;

	// �L���Ȕ������擾����
	Blast* GetValidBlast(void);

	//���C���𔚔�������
	void BlastLine(int y, int x, int i);

private:

	int count_;
	std::vector<std::vector<int>> fieldNeo_;
	std::vector < std::vector<BLOCK_TYPE>> roleNeo_;
	std::vector<int> decLineHeights_;
};

