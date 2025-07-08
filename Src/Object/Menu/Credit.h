#pragma once

class MenuScene;

class Credit
{
public:

	//���批��
	static constexpr int MOVIE_VOLUME = 70;

	//�R���X�g���N�^
	Credit();

	//�f�X�g���N�^
	~Credit();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="parent"></param>�e�C���X�^���X
	void Init(MenuScene* parent);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//���
	void Release();

private:

	//����
	int movie_;
	
	//�Đ�����
	bool isPlay_;

	//���j���[���
	MenuScene* menu_;

};

