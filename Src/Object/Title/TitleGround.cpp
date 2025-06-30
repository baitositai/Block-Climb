#include <DxLib.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "TitleGround.h"

TitleGround::TitleGround()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            grounds_[i][j] = 0;
        }
    }

    for (int i = 0; i < GROUND_IMG_NUM; i++)
    {
        imgGrounds_[i] = 0;
    }
}

TitleGround::~TitleGround()
{
}

void TitleGround::Init()
{
    //�n�ʉ摜�̓ǂݍ���
    int ret;
    ret = LoadDivGraph((Application::PATH_IMAGE + "Terrain/Terrain.png").c_str()
        , GROUND_IMG_NUM
        , GROUND_IMG_NUM_X
        , GROUND_IMG_NUM_Y
        , GROUND_SIZE_X
        , GROUND_SIZE_Y
        , &(imgGrounds_[0]));

    groundCsvDate_ = (Application::PATH_CSV + "Title.csv").c_str();

    LoadStageCsvData();

}

void TitleGround::Draw()
{
    Vector2 pos =  { 0,
                      Application::SCREEN_SIZE_Y - GROUND_SIZE_Y * HEIGHT + 5};

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            DrawGraph(pos.x + i * GROUND_SIZE_X,
                pos.y + j * GROUND_SIZE_Y,
                imgGrounds_[grounds_[j][i]],
                true);
        }
    }
}

void TitleGround::Release()
{
    for (int i = 0; i < GROUND_IMG_NUM; i++)
    {
        DeleteGraph(imgGrounds_[i]);
    }
}

//�O���t�@�C������X�e�[�W��CSV�f�[�^��ǂݍ���
void TitleGround::LoadStageCsvData(void)
{
    //�t�@�C���̏���
    std::ifstream ifs = std::ifstream(groundCsvDate_);
    if (!ifs)
    {
        OutputDebugString("�X�e�[�W��ifstream�������s\n");
        return;
    }

    //�񎟌��z��̏ꏊ���w��p
    int x = 0;
    int y = 0;

    std::string line;					//1�s�̃f�[�^���i�[����̈�
    while (getline(ifs, line))
    {
        //Split�֐��̖߂�l�󂯎��p�ϐ�
        std::vector<std::string> strSplit; // 1�s��1�����̓��I�z��ɕ���
        strSplit = AsoUtility::Split(line, ',');

        int chipNo;

        //���������f�[�^���}�b�v�z��Ɋi�[����
        for (int x = 0; x < strSplit.size(); x++)
        {
            chipNo = stoi(strSplit[x]);
            grounds_[y][x] = chipNo;
        }
        y++;
    }

}