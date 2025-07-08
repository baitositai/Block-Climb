#pragma once
#include "../../Utility/AsoUtility.h"
#include "../../Manager/InputManager.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector2F.h"


class LevelManager;

class PlayerBase
{
public:
	//�񋓌^
	//----------------------------------------------
	//�v���C���[���
	enum class PLAYER_TYPE
	{
		DUDU,
		FROG,
		MAN,
		GUY,
		MAX
	};

	//�A�j���[�V�������
	enum class ANIM_STATE
	{
		IDLE,
		RUN,
		JUMP,
		FALL,
		HIT,
		DIE,
		MAX
	};

	//�Փˍ��W(���E)
	enum class COL_LR
	{
		C,
		L,
		R
	};

	//�Փˍ��W(�㉺)
	enum class COL_TD
	{
		C,
		T,
		D
	};

	//�Փˍ��W
	enum class COL_LRTD
	{
		C,		//���S
		L,		//��
		R,		//�E
		T,		//��
		D		//��
	};

	//�Փ˔���̊m�F
	enum class HIT
	{
		NONE,
		RIGHT,
		LEFT,
		UP,
		DOWN
	};

	//�摜�T�C�Y
	static constexpr int SIZE_X = 50;						
	static constexpr int SIZE_Y = 50;						

	//�����̉摜�T�C�Y
	static constexpr int IDLE_SIZE_X = 550;					
	static constexpr int IDLE_SIZE_Y = 50;					

	//����̉摜�T�C�Y
	static constexpr int RUN_SIZE_X = 600;					
	static constexpr int RUN_SIZE_Y = 50;	

	//�Փˎ��̉摜�T�C�Y
	static constexpr int HIT_SIZE_X = 350;
	static constexpr int HIT_SIZE_Y = 50;

	//�����̃A�j���[�V������
	static constexpr int IDLE_NUM_ANIM = 11;	

	//����̃A�j���[�V������
	static constexpr int RUN_NUM_ANIM = 12;	
	
	//�_���[�W�̃A�j���[�V������
	static constexpr int HIT_NUM_ANIM = 7;	

	//�v���C���[�̃X�s�[�h
	static constexpr float PLAYER_SPEED = 4.0f;

	//�v���C���[�̃A�j���[�V�������x
	static constexpr float ANIM_SPEED = 0.1f;

	//����(accelerator=�A�N�Z�����[�^�[)
	static constexpr float MOVE_ACC = 0.25f;	

	//����
	static constexpr float MOVE_DEC = 0.15f;			

	//�ړ����x�̍ő�l
	static constexpr float MAX_MOVE_SPEED = 3.5f;			

	//�ő�W�����v��
	static constexpr float MAX_JUMP_POW = 8.0;

	static constexpr float DEATH_JUMP_POW = 6.0f;		

	//�d��
	static constexpr float GRAVITY = 0.25;		

	//�W�����v�̃t���[����
	static constexpr float INPUT_JUMP_FRAME = 4.0f;		

	//�v���C���[�̏Փ˔͈͂����߂�
	static constexpr int PLAYER_HIT_RANGE_OFFSET_X = 8;
	static constexpr int PLAYER_HIT_RANGE_OFFSET_Y = 5;

	//�v���C���[�̑����I�t�Z�b�g
	static constexpr int PLAYER_COL_D_OFFSET = 4;

	//�R���X�g���N�^
	PlayerBase(void);			

	//�f�X�g���N�^
	~PlayerBase(void);						

	//�����������i�ŏ��̈��̂ݎ��s)
	virtual void Init(LevelManager* parent);
	
	//�X�V�����i���x���s�j			
	virtual void Update(void);	
	
	//�`�揈���i���x���s�j						
	virtual void Draw(void);	
	
	//������� (�I�������̂ݎ��s)						
	bool Release(void);									

	//�ϐ��̏�����
	virtual void Reset();

	//�摜�̓ǂݍ���
	void Load(PLAYER_TYPE type);

#pragma region �ړ��֘A
	void ProcessMove();					//�v���C���[�̑���	
	void Move();						//�ړ�(���ۂ̍��W�ړ�)
	void Accele(float speed);			//�����Ɋւ��鏈��
	void Decelerate(float speed);		//�����Ɋւ��鏈��
#pragma endregion

#pragma region �W�����v�֘A
	void AddGravity(void);				//�d�͂�������
	void ProcessJump(void);
	void Jump(void);					//�W�����v
	void SetJumpPow(float pow);			//�W�����v�͂̐ݒ�
#pragma endregion

#pragma region ���S�֘A
	void CheckDeath();
	void DeathAnimation();
#pragma endregion

#pragma region �Փ˔���	
	bool CollisionHead(void);			//���̏Փ˔���
	bool CollisionRight(void);			//�E�̏Փ˔���
	bool CollisionLeft(void);			//���̏Փ˔���
	int CollisionFoot(void);			//�����̏Փ˔���
#pragma endregion

#pragma region �l��Ԃ�
	Vector2F GetPos();							//���W��Ԃ�
	Vector2 GetColPos(COL_LR lr, COL_TD td);	//�v���C���[�̏㉺���E�̍��W��Ԃ�
	Vector2 GetSize();							//�v���C���[�T�C�Y��Ԃ�
	bool IsDeath();								//���S����
#pragma endregion
	
#pragma region �O������̐ݒ�
	void SetPos(Vector2F value);				//���W��ݒ�
	void SetState(ANIM_STATE state);			//��Ԃ̐ݒ�
	void SetIsDeath(bool value);				//���S����̐ݒ�
	void SetParam(float speed_, float jumpPow);	//�p�����[�^�[�̐ݒ�
#pragma endregion

protected:

#pragma region �X�e�[�^�X�֘A
	//�摜�̊i�[
	int Images_[static_cast<int>(ANIM_STATE::MAX)][RUN_NUM_ANIM];

	//�v���C���[�T�C�Y
	Vector2 size_;			

	//����
	bool dir_;		

	//�X�s�[�h
	float speed_;

	//�X�s�[�h
	float maxSpeed_;

	//�p�x
	float rot_;

	//���W
	Vector2F pos_;	

	//�o�b�N�A�b�v�p���W
	Vector2F prePos_;	
#pragma endregion

#pragma region �A�j���[�V�����֘A
	//�A�j���̏��	
	ANIM_STATE animState_;	

	//�A�j���J�E���^�[
	int cntAnim_;			

	//�A�j���̎�ނ̐��l
	int numAnim_;		

	//�A�j���[�V�����X�s�[�h
	float animSpeed_;									
#pragma endregion

private:

#pragma region �W�����v
	float cntJumpInput_;
	bool isJump_;
	float jumpPow_;
	float maxJumpPow_;
#pragma endregion

#pragma region �Փ˔���p
	//���S���W(pos_����̑��΍��W)
	Vector2 hitPos_;	

	//�͈�
	Vector2 hitBox_;	

	//�Փ˔���̊m�F
	HIT hit_;

#pragma endregion

	//����p�X�e�B�b�N�ϐ�
	Vector2 stick_;

	int deathCnt_;

	bool isDeath_;

	bool fallSound_;

	Vector2F deathPos_;

	//�������
	InputManager::JOYPAD_NO pad_;

	//�C���X�^���X
	LevelManager* level_;

};

