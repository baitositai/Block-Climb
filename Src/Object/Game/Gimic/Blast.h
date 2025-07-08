#pragma once
#include <vector>
#include "../../../Common/Vector2.h"

class LevelManager;
class BlockBase;

class Blast
{
public:
	//�������
	enum class STATE
	{
		NONE,
		WAIT,
		BLAST
	};

	//�摜������
	static constexpr int BLAST_X = 16;
	static constexpr int BLAST_Y = 1;

	//�����̃A�j���[�V������
	static constexpr int BLAST_ANIM_NUM = BLAST_X * BLAST_Y;

	//�摜�T�C�Y
	static constexpr int BLAST_SIZE_X = 1024 / BLAST_X;
	static constexpr int BLAST_SIZE_Y = 87 / BLAST_Y;

	//�Փ˔���T�C�Y
	static constexpr int HIT_SIZE = 48;

	//�����A�j���[�V�����X�s�[�h
	static constexpr float ANIM_SPEED = 0.3f;

	//�����A�j���[�V�����C���f�b�N�X�I�t�Z�b�g
	static constexpr int BLAST_ANIM_OFFSET = 4;

	Blast(void);								//�R���X�g���N�^
	~Blast(void);								//�f�X�g���N�^

	//void Init(LevelManager* parent);			//�����������i�ŏ��̈��̂ݎ��s)
	void Create(LevelManager* parent, BlockBase* block, Vector2 pos, float coolTime);		// �e�̐���(�\���J�n���W�A�e�̐i�s����)
	void Update(void);							//�X�V�����i���x���s�j
	void Draw(void);							//�`�揈���i���x���s�j
	void Release(void);							//������� (�I�������̂ݎ��s)

	//���W
	void SetPos(Vector2 pos);

	//�������W��Ԃ�
	Vector2 GetPos();

	//�����T�C�Y��Ԃ�
	Vector2 GetSize();

	//������������Ԃ�
	int GetCreateCnt();

	float GetRadius();

	//�����̏�Ԃ�Ԃ�
	STATE GetState();

private:

	//�摜�̊i�[
	int imgBlasts_[BLAST_ANIM_NUM];

	//�����̏��
	STATE state_;

	//�����̑傫��
	Vector2 size_;
	float radius_;

	//�����ʒu
	Vector2 pos_;

	//�����̃A�j���[�V�����p�J�E���^
	int blastCntAnim_;

	//�\�����Ă���A�j���[�V�����l
	int blastIdxAnim_;

	//�����̃A�j���[�V�������x
	float blastSpeedAnim_;

	//���j�̐�����
	float createCnt_;	

	//�N�[������
	float coolTime_;

	//�C���X�^���X
	LevelManager* level_;
	BlockBase* block_;
};

