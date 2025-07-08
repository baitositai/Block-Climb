#pragma once
#include <string>
#include "../../../Common/Vector2.h"
#include "../../../Common/Vector2F.h"
#include "../../../Utility/AsoUtility.h"
#include "../Event/Event.h"

class GameScene;
class BlockBase;
class PlayerBase;
class BackGround;
class Camera;
class Moon;
class SideBase;
class Moon;
class Event;

class LevelManager
{
public:

	//�q�b�g�X�g�b�v�p�̃J�E���g
	static constexpr int HIT_STOP_CNT = 60;

	//����u���b�N�g�嗦
	static constexpr float NEXT_BLOCK_RATE = 0.7f;

	// �萔�Ń}�W�b�N�i���o�[��u������
	static constexpr int HITSTOP_SHAKE_INTERVAL = 5;   // �h��̐؂�ւ��Ԋu�i�t���[���j
	static constexpr int SHAKE_SCALE = 2;              // �V�F�C�N�̋��x�i�ŏI�ʒu�̔{���j
	static constexpr int SHAKE_OFFSET = 1;             // ���S����̃I�t�Z�b�g����
	static constexpr int SHAKE_DISTANCE = 5;           // ���ۂɉ�ʂ𓮂�������

	static constexpr int EFFECT_LOCAL_POS_X = 30;					//�G�t�F�N�g�̑��ΈʒuX
	static constexpr int EFFECT_LOCAL_POS_Y = 30;					//�G�t�F�N�g�̑��ΈʒuY

	static constexpr float BUFF_PERCENT = 1.5f;						//�o�t�̊���
	static constexpr float DEBUFF_PERCENT = 0.75f;					//�f�o�t�̊���
	static constexpr int BLOCK_FALL_SPEED_UP = 3;					//�u���b�N�̗������x

	LevelManager(void);
	~LevelManager(void);

	virtual void Init(GameScene* parent);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

	//�ǉ��̓ǂݍ���
	virtual void AddInit();

	//�X�e�[�W���x���̏����ݒ�
	virtual void SetParam();

	//���Z�b�g�@�\
	virtual void Reset();

	//�S�[���Ƃ̏Փ˔���
	virtual void GoalHit();

	//�N���A����
	void GameClearCheck();

	//�Q�[���I�[�o�[����
	void GameOverCheck();

	//�u���b�N�֌W�̓����蔻��
	bool IsHitBlocks(Vector2 Pos, Vector2 Size);

	//�t�B�[���h�Ƃ̓����蔻��
	bool IsHitField(Vector2 Ppos);

	//�������Ă�~�m�Ƃ̓����蔻��
	bool IsHitMino(Vector2 Ppos, Vector2 Psize);

	//�v���C���[���Փ˔�����N�����Ă邩�̊m�F
	bool IsPlayerCheck(AsoUtility::DIR value, Vector2 Mino, int MinoType);

	//�v���C���[���J�����͈͂��m�F
	void IsCameraRange();

	//�v���C���[�����炷����
	void PlayerShift(AsoUtility::DIR value);

	//�t�B�[���h�p�ɍ��W�̕ϊ�
	Vector2 Field2Pos(Vector2 worldPos);

	//���[���h�p�ɍ��W�̕Ԋ�
	Vector2 World2Pos(Vector2 fieldPos);

	//�f�o�b�O�Ɋւ���`��
	void DebagDraw();

	//�Q�[���N���A�֕ς���
	void SetGameClear(bool value);

	//�Q�[���I�[�o�[�֕ς���
	void SetGameOver(bool value);

	//�q�b�g�X�g�b�v�̃J�E���g��ݒ�
	void SetStopCnt(int cnt);

	//�J�����V�F�C�N
	void CameraShake();

	//���̃u���b�N�̕`��
	void NextBlockDraw(Vector2 pos);

	//���W�����炷����
	virtual void ShiftGame();

	//�C�x���g�A�C�R���`��
	void IconDraw(Vector2 pos);

	//bgm�̍Đ�
	void PlayBGM();

	//bgm�̒�~
	void StopBGM();

	/// <summary>
	/// �u���b�N�̏c�ɒu����Ă鐔��Ԃ�
	/// </summary>
	/// <param name="y"></param>�u���b�N�c�̐��ŐV�̒l
	/// <returns></returns>
	int GetFieldBlockY(int y);

	/// <summary>
	/// ���݂̍�����Ԃ�
	/// </summary>
	/// <returns></returns>�ςݏグ������
	int GetBlockHeight();

	/// <summary>
	/// �ۑ�p�u���b�N�̒u������Ԃ�
	/// </summary>
	/// <returns></returns>�ۑ�p�u���b�N�̒u����
	int GetBlockCnt();

	/// <summary>
	/// ���������C���̐�
	/// </summary>
	/// <returns></returns>���������C���̐�
	int GetCntLine();

	/// <summary>
	/// �������x��Ԃ�
	/// </summary>
	/// <returns></returns>�������x
	float GetFallSpeed();

	/// <summary>
	/// �J�������W��Ԃ�
	/// </summary>
	/// <returns></returns>�J�������W
	Vector2F GetCameraPos();

	/// <summary>
	/// �v���C���[���W��Ԃ�
	/// </summary>
	/// <returns></returns>�v���C���[���W
	Vector2F GetPlayerPos();

	/// <summary>
	/// �v���C���[�ƃ~�m�̈ʒu����~�m�̍��W��Ԃ�
	/// </summary>
	/// <param name="pPos"></param>�v���C���[���W
	/// <returns></returns>�~�m�̍��W
	Vector2F GetMinoBlockPos(Vector2F pPos);

	/// <summary>
	/// ���̃N���X��Ԃ�
	/// </summary>
	/// <returns></returns>��
	virtual Moon* GetMoonInstans();

	/// <summary>
	/// �C�x���g��Ԃ�Ԃ�
	/// </summary>
	/// <returns></returns>�C�x���g�̏��
	Event::EVENT GetEventState();

	/// <summary>
	/// �t�B�[���h�T�C�Y��Ԃ�
	/// </summary>
	/// <returns></returns>�t�B�[���h�T�C�Y
	Vector2 GetFieldSize();

	/// <summary>
	/// �n�ʂ̃T�C�Y��Ԃ�
	/// </summary>
	/// <returns></returns>�n�ʃT�C�Y
	Vector2 GetGroundSize();

	/// <summary>
	/// �X�e�[�W�S�̂̃T�C�Y�Ԃ�
	/// </summary>
	/// <returns></returns>�X�e�[�W�S�̂̃T�C�Y
	Vector2 GetStageSize();

	/// <summary>
	/// �v���C���[�̏����ʒu��Ԃ�
	/// </summary>
	/// <returns></returns>�v���C���[�̏����ʒu
	Vector2F GetFirstPlayerPos();

	/// <summary>
	/// �J�����̏����ʒu��Ԃ�
	/// </summary>
	/// <returns></returns>�J�����̏����ʒu
	Vector2F GetFirstCameraPos();

	/// <summary>
	/// �S�[���̈ʒu��Ԃ�
	/// </summary>
	/// <returns></returns>�S�[���̈ʒu��Ԃ�
	Vector2 GetGoalPos();

	/// <summary>
	/// ���S�ʒu�ɍ��킹��p�̒l��Ԃ�
	/// </summary>
	/// <returns></returns>���S�ʒu�ɍ��킹��p�̒l
	Vector2 GetGameCenter();

protected:

	//�Q�[���N���A����
	bool isGameClear_;

	//�Q�[���I�[�o�[����
	bool isGameOver_;

	//�q�b�g�X�g�b�v�J�E���g
	int hitStopCnt_;

	//�t�B�[���h�T�C�Y
	Vector2 fieldSize_;

	//�n�ʃT�C�Y
	Vector2 groundSize_;

	//�X�e�[�W�T�C�Y
	Vector2 stageSize_;

	//�v���C���[�̏������W
	Vector2F firstPlayerPos_;

	//�J�����̏������W
	Vector2F firstCameraPos_;

	//�S�[�����W
	Vector2 goalPos_;
	
	//�Q�[������ʒ��S�ŕ`��ł���悤�ɂ���p�̍��W
	Vector2 game_Draw_Center_;

	//�Q�[���V�[��
	GameScene* gameScene_;

	//�u���b�N
	BlockBase* block_;

	//�v���C���[
	PlayerBase* player_;

	//�w�i
	BackGround* backGround_;

	//�J����
	Camera* camera_;

	//��
	Moon* moon_;

	//�T�C�h���
	SideBase* side_;

	//�C�x���g
	Event* event_;

	//�ꎞ�I�ȃX�N���[��
	int tmpScreen_;
	
};

