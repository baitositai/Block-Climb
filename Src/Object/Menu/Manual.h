#pragma once

class MenuScene;

class Manual
{

public:

	//�R���X�g���N�^
	Manual(void);

	//�f�X�g���N�^
	~Manual(void);

	//�}�j���A�����
	static constexpr int MANUAL_TYPE = 4;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent"></param>�e�N���X
	void Init(MenuScene* parent);

	//�X�V
	void Update(void);

	//�`��
	void Draw(void);

	//���
	void Release(void);

private:

	//�X�e�B�b�N����
	bool isStick_;

	//���j���[�I���J�E���g
	int manuSle_;

	//�摜
	int imgManual_[MANUAL_TYPE];

	//���j���[���
	MenuScene* menu_;

};

