#pragma once
#include <string>
#include "../Common/Vector2.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "SceneBase.h"

class LevelManager;
class GameStart;
class GameOver;
class GameClear;
class Pause;
class Fader;

class GameScene : public SceneBase
{
public:

	//BGM����
	static constexpr int BGM_VOLUME = 70;

	//�Q�[���I�����̃Q�[��UI�̕\������
	static constexpr float FINISH_TO_WAIT_TIME = 2.0f;

	//BGM��ސ�
	static constexpr int RAND_BGMS = 4;

	//�Q�[�����
	enum class STATE
	{
		START,
		GAME,
		OVER,
		CLEAR,
		PAUSE
	};

	//�R���X�g���N�^
	GameScene();

	//�f�X�g���N�^
	~GameScene() override;

	//������
	virtual void Init() override;

	//�X�V
	virtual void Update() override;

	//�`��
	virtual void Draw() override;

	//���
	virtual void Release() override;

	//���g���C����
	void Retry();

	/// <summary>
	/// �I�������̋��̐ݒ�
	/// </summary>
	/// <param name="value"></param>�I���̋���
	void SetIsSelect(const bool value);

	/// <summary>
	/// �Q�[����Ԃ̕ύX
	/// </summary>
	/// <param name="state"></param>�Q�[�����
	void ChangeState(const STATE state);

	//�V�L�^�����ׂ�
	void CheckNewRecode();

	//BGM�Đ�
	void PlayBGM();

	//BGM��~
	void StopBGM();

	//�X�e�[�g��Ԃ�
	STATE GetState();

	//������Ԃ�
	int GetHeight();

protected:

	//�I�������̋���
	bool isSelect_;

	//�I�������̏o���J�E���g
	float cnt_;

	//�X�e�[�g�̃`�F���W��
	bool isStateChanging_;

	//�Q�[���X�e�[�g
	STATE state_;

	//�Đ�����BGM 
	SoundManager::BGM bgm_;

	//�t�F�[�_�[
	Fader* fader_;

	//���x���Ǘ��N���X
	LevelManager* level_;

	//�Q�[���X�^�[�g
	GameStart* start_;

	//�Q�[���I�[�o�[
	GameOver* over_;

	//�Q�[���N���A
	GameClear* clear_;

	//�V�[���I��
	Pause* select_;	
	
	//���Z�b�g
	void Reset();

	//�X�e�[�W���x���̓ǂݍ���
	void LevelLoad();
	
	//�t�F�[�h����
	void Fade();

	//BGM�̎�ނ������_���Ō��肷��
	SoundManager::BGM GetRandGameBgm();

};

