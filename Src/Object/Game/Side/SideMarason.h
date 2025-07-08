#pragma once
#include "SideBase.h"

class SideMarason:public SideBase
{
public:

	//X�����̊Ԋu
	static constexpr int INTERVAL_X = 5;

	//Y�����̊Ԋu
	static constexpr int INTERVAL_Y = 10;

	//�t�`�̑���
	static constexpr int BOX_BORDER = 3;

	//�����\���{�b�N�X��Y���W
	static constexpr int HEIGHT_BOX_POS_Y = 310;

	//�����\���{�b�N�X�̍���
	static constexpr int HEIGHT_BOX_SIZE_Y = 120;

	//�A�C�R���{�b�N�X��X�I�t�Z�b�g
	static constexpr int ICON_BOX_OFFSET_X = 64;

	//�A�C�R���{�b�N�X��Y���W
	static constexpr int ICON_BOX_POS_Y = 150;

	//�A�C�R���{�b�N�X�̃T�C�Y
	static constexpr int ICON_BOX_SIZE = 128;

	//�����{�b�N�X��X���W����
	static constexpr int HEIGHT_BOX_OFFSET_X_RATE = 8;

	//�����{�b�N�X�̉�������
	static constexpr int HEIGHT_BOX_WIDTH_OFFSET_RATE = 16;

	void Reset() override;
	void Update() override;
	void Draw(void) override;

	void HeightDraw();
	void IconDraw();

private:
};

