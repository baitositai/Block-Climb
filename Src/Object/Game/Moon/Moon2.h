#pragma once
#include "../../../Common/Vector2.h"
#include "../Level/LevelManager.h"
#include "Moon.h"

class Moon2 : public Moon
{
public:

	//�Ԃ����̒�ʒu
	static constexpr int RED_MOON_DEFAULT_POS_X = 75;
	static constexpr int RED_MOON_DEFAULT_POS_Y = 250;

	//���΂̒�ʒu
	static constexpr int BLUE_MOON_DEFAULT_POS_X = static_cast<float>(Application::SCREEN_SIZE_X - 75);
	static constexpr int BLUE_MOON_DEFAULT_POS_Y = 250;

	//�������錎�̐�
	static constexpr int UPD_MOONS = 2;

	//�R���X�g���N�^
	Moon2();

	//�f�X�g���N�^
	~Moon2();

	//���Z�b�g
	void Reset() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

};


