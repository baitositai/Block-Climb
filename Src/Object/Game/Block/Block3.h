#pragma once
#include <vector>
#include "BlockBase.h"
#include "../Gimic/Blast.h"

class Block3 :public BlockBase
{
public:

	//�N���A����
	static constexpr int CREAL_LINE = 20;

	//���̔��������܂ł̃N�[������
	static constexpr float COOL_TIME = 10.0f;

	//�R���X�g���N�^
	Block3();

	//�f�X�g���N�^
	~Block3();

	//���Z�b�g
	void Reset(void) override;

	//�X�e�[�W����
	void StageCreate(void) override;

	//���C���폜
	void LineDelete(void) override;

	// �L���Ȓe���擾����
	Blast* GetValidBlast(void);

	//���C���𔚔�������
	void BlastLine(int y, int x, int cnt);

	//��������
	void AllDeleteLine() override;

	//���C�������炷
	void ShiftLine() override;

private:

	std::vector<std::vector<int>> fieldNeo_;
	std::vector<std::vector<BLOCK_TYPE>> roleNeo_;
	std::vector<int> decLineHeights_;
};

