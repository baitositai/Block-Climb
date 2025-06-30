#pragma once

class MenuScene;

class TagPlay
{
public:

	//�R���X�g���N�^
	TagPlay(void);

	//�f�X�g���N�^
	~TagPlay(void);

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent"></param>�e�C���X�^���X
	void Init(MenuScene* parent);

	//�X�V
	void Update(void);

	//�`��
	void Draw(void);

	//���
	void Release(void);

private:

	//���j���[�V�[��
	MenuScene* menu_;
	
	//�ϐ��̏�����
	void Reset();

	//�ǂݍ���
	void Load();
};

