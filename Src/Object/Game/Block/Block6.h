#pragma once
#include <vector>
#include "BlockBase.h"
#include "../Gimic/Blast.h"
#include "../Gimic/FireBall.h"

class Block6 :public BlockBase
{
public:

	//�N���A����
	static constexpr int CREAL_LINE = 20;

	//���̔��������܂ł̃N�[������
	static constexpr float COOL_TIME = 10.0f;

	//�X�V���C��
	static constexpr int UPDATE_LINE = 10;

	//�폜���C����
	static constexpr int DELETE_LINE = 3;

	//�R���X�g���N�^
	Block6();

	//�f�X�g���N�^
	~Block6();

	//���ƒ҂̍X�V����
	void HitUpdate(Vector2 pos) override;

	//���Z�b�g
	void Reset(void) override;

	//�X�e�[�W����
	void StageCreate(void) override;

	//���C���폜
	void LineDelete(void) override;

	//�����̍X�V
	void HeightUpdate();

	//�w�肵���l���獂���𒲂ׂ�
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

