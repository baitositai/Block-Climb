#include "../../../Application.h"
#include "../../../Manager/SceneManager.h"
#include "../../../Manager/SoundManager.h"
#include "../../../Utility/Collision.h"
#include "Level6.h"
#include "../PlayerBase.h"
#include "../Block/BlockBase.h"
#include "../Block/Block6.h"
#include "../BackGround.h"
#include "../Camera/MarasonCamera.h"
#include "../Moon/Moon6.h"
#include "../Gimic/Blast.h"
#include "../Gimic/FireBall.h"
#include "../Side/SideBase.h"
#include "../Side/Side6.h"

Level6::Level6(void)
{
	eventLine_ = 0;
	fireCnt_ = 0;
	fireCreateCnt_ = 0;
	isBlast_ = false;	
	isSpeedDown_ = false;
	paramCnt_ = 0;
}

Level6::~Level6(void)
{
}

void Level6::Init(GameScene* parent)
{
	SetParam();

	gameScene_ = parent;

	camera_ = new MarasonCamera();
	camera_->Init(this);

	player_ = new PlayerBase();
	player_->Init(this);

	backGround_ = new BackGround();
	backGround_->Init();	

	//�u���b�N�̓ǂݍ���
	block_ = new Block6();
	block_->Init(this);

	//�T�C�h�̓ǂݍ���
	side_ = new Side6();
	side_->Init(this);

	//�S�[���̓ǂݍ���
	moon_ = new Moon6();
	moon_->Init(this);

	event_ = new Event();
	event_->Init(this);

	// �ꎞ�I�ȕ`��̈�
	tmpScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	//����������
	Reset();

	//�΂̋ʂ̏�����
	for (auto fire : fire_)
	{
		fire->SetState(FireBall::STATE::NONE);
	}
}

void Level6::Update(void)
{
	//�q�b�g�X�g�b�v����
	if (hitStopCnt_ > 0)
	{
		hitStopCnt_--;
		return;
	}	

	//�Q�[���I�[�o�[�`�F�b�N
	GameOverCheck();

	//�Q�[���N���A�`�F�b�N
	GameClearCheck();

	//�u���b�N����(�������͍s��Ȃ�)
	if (!isBlast_) { block_->Update(); }
	
	//�v���C���[�̍X�V����
	player_->Update();

	//�w�i����
	backGround_->Update();

	//�J��������
	camera_->Update();

	//�T�C�h��ʏ���
	side_->Update();

	//���̏���
	moon_->Update();
	HitMoon();

	//��������
	BlastUpdate();

	//�΂̋ʏ���
	FireBallUpdate();

	//�v���C���[�ւ̃f�o�t
	if (GetBlockHeight() >= DEBUFF_LINE && !isSpeedDown_) 
	{
		player_->SetParam(PlayerBase::MAX_MOVE_SPEED * DEBUFF_PERCENT, PlayerBase::MAX_JUMP_POW * DEBUFF_PERCENT);
		SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::EVENT, static_cast<int>(SoundManager::EVENT::SPEEDDOWN));
		event_->SetEvent(Event::EVENT::SPEED_DOWN);
		Vector2 efectPos = AsoUtility::V2Sub(player_->GetPos().ToVector2(), Vector2{ EFFECT_LOCAL_POS_X,EFFECT_LOCAL_POS_Y });
		event_->SetEfectPos(efectPos);

		isSpeedDown_ = true;
	}
}

void Level6::Draw(void)
{
	// �U��
	if (hitStopCnt_ > 0)
	{
		// �`���̃X�N���[����ݒ� �q�b�g�X�g�b�v���́A
		SetDrawScreen(tmpScreen_);
		ClearDrawScreen();				//�`��̈�̃N���A
	}

	//�w�i�`��
	backGround_->Draw();

	//�u���b�N�`��
	block_->Draw();

	//���̕`��
	moon_->Draw();

	//�v���C���[�`��
	player_->Draw();

	event_->EfectDraw();

	//�J�����̕`��
	camera_->Draw();

	for (auto fire : fire_)
	{
		fire->Draw();
	}
	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		blast->Draw();
	}

	CameraShake();

	side_->Draw();
	DebagDraw();
}

void Level6::Release(void)
{	
	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		blast->Release();
	}
	for (auto fire : fire_)
	{
		fire->Release();
	}
	event_->Release();
	delete event_;

	side_->Release();
	delete side_;
	
	block_->Release();
	delete block_;
	
	moon_->Release();
	delete moon_;
	
	backGround_->Release();
	delete backGround_;
	
	player_->Release();
	delete player_;
	
	camera_->Release();
	delete camera_;
}

void Level6::SetParam()
{
	// �t�B�[���h�T�C�Y��ݒ�
	fieldSize_ = { FIELD_WIDTH, FIELD_HEIGHT };

	// �n�ʃT�C�Y��ݒ�
	groundSize_ = { FIELD_WIDTH, GROUND_HEIGHT };

	// �X�e�[�W�T�C�Y��ݒ�
	stageSize_ = {
		fieldSize_.x,
		fieldSize_.y + groundSize_.y
	};

	float fieldY = static_cast<float>(fieldSize_.y);  // �t�B�[���h�̏c�T�C�Y�� float �ɕϊ����Ďg�p

	// �v���C���[�̏������W��ݒ�
	firstPlayerPos_ = {
		Application::SCREEN_SIZE_X / 2,
		BlockBase::BLOCK_SIZE_Y * (fieldY - PLAYER_OFFSET_BLOCK_Y) - PLAYER_PIXEL_ADJUST_Y
	};

	// �J�����̏������W��ݒ�
	firstCameraPos_ = {
		0,
		-Application::SCREEN_SIZE_Y + BlockBase::BLOCK_SIZE_Y * (fieldY + CAMERA_OFFSET_BLOCK_Y)
	};

	// �S�[���̍��W��ݒ�
	goalPos_ = {
		Application::SCREEN_SIZE_X / 2 + GOAL_OFFSET_X,
		GOAL_POS_Y
	};

	// �`�撆�S�̍��W���v�Z���Đݒ�
	game_Draw_Center_ = {
		Application::SCREEN_SIZE_X / 2
			- fieldSize_.x * BlockBase::BLOCK_SIZE_X / 2
			+ BlockBase::BLOCK_SIZE_X / 2,
		0
	};
}

void Level6::Reset()
{
	LevelManager::Reset();
	fireCnt_ = 0;
	fireCreateCnt_ = DEFAULT_CREATE_FIRE_CNT;
	isSpeedDown_ = false;	
	eventLine_ = ADD_LINE;
	isBlast_ = false;
}

void Level6::ShiftGame()
{
	LevelManager::ShiftGame();

	//�V�t�g�p���W
	Vector2F pos = { 0,BlockBase::BLOCK_SIZE_Y };

	//�����炵
	for (auto fire : fire_)
	{
		fire->SetPos(pos);
	}

	//�����W���炵
	moon_->SetPos(Moon::MOON_TYPE::DEAD, pos);
	moon_->SetPos(Moon::MOON_TYPE::GOAL, pos);
	moon_->SetFirstPos(Moon::MOON_TYPE::GOAL, pos);

}

void Level6::HitMoon()
{
	//�v���C���[���̎擾
	Vector2 pPos = player_->GetPos().ToVector2();
	Vector2 pSize = player_->GetSize();			//�v���C���[��x���W�̔����𔼌a�Ƃ���
	int pRadius = pSize.x / 2;

	//���̎擾
	Vector2 mPos = moon_->GetPos(Moon::MOON_TYPE::DEAD).ToVector2();

	if (!isBlast_ &&
		Collision::IsCollisionCircle(pPos, pRadius, mPos, Moon::RADIUS) &&
		moon_->IsMoon(Moon::MOON_TYPE::DEAD) == false)
	{
		StopBGM();
		moon_->SetDarkMove(Moon::DARK_MOVE::FADE_BIG);
		block_->LineDelete();
	}

	//�v���C���[���̎擾

	//�S�[�����̎擾
	mPos = moon_->GetPos(Moon::MOON_TYPE::GOAL).ToVector2();
	if (Collision::IsCollisionCircle(pPos, pRadius, mPos, Moon::RADIUS))
	{
		StopBGM();
		SetStopCnt(HIT_STOP_CNT);
		isGameClear_ = true;
	}
}

void Level6::FireBallUpdate()
{
	CreateFireBall();

	//�΂̋ʂ̏���
	for (auto fire : fire_)
	{
		//����������
		fire->Update();

		//�v���C���[�Ƃ̏Փ˔���
		Vector2 fPos = fire->GetPos().ToVector2();
		Vector2 fSize = { FireBall::SIZE_X,
						  FireBall::SIZE_Y };

		int pRadius = player_->GetSize().y / 2;

		//�v���C���[�Ƃ̏Փ˔���
		if (fire->GetState() == FireBall::STATE::FIRE &&
			Collision::IsCollisionCircle(player_->GetPos().ToVector2(),
				pRadius,
				fire->GetPos().ToVector2(),
				FireBall::RADIUS))
		{
			fire->SetState(FireBall::STATE::BLAST);
			SetStopCnt(HIT_STOP_CNT);
			player_->SetIsDeath(true);
		}

		//�u���b�N�Ƃ̏Փ˔���
		if (fire->GetState() == FireBall::STATE::FIRE &&
			IsHitField(fPos))
		{
			fire->SetState(FireBall::STATE::BLAST);
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::FIRE_BALL_HIT));
		}
		else if (fire->GetState() == FireBall::STATE::FIRE &&
			IsHitMino(fPos, fSize))
		{
			fire->SetState(FireBall::STATE::BLAST);
			SoundManager::GetInstance().PlayEffectSound(SoundManager::EFFECT_TYPE::GIMIC, static_cast<int>(SoundManager::GIMIC::FIRE_BALL_HIT));
		}

	}
}

void Level6::BlastUpdate()
{
	auto blasts = block_->GetBlast();
	for (auto blast : blasts)
	{
		//����������
		blast->Update();

		//�������ĂȂ��Ƃ�
		if (blast->GetState() == Blast::STATE::NONE)
		{
			isBlast_ = false;
		}

		//�������̏���
		if (blast->GetState() == Blast::STATE::BLAST)
		{
			isBlast_ = true;
			//�Փ˔���
			if (!player_->IsDeath() &&
				Collision::IsCollisionCircle(player_->GetPos().ToVector2(),
					player_->GetSize().x / 2,
					blast->GetPos(),
					blast->GetRadius()))
			{
				SetStopCnt(HIT_STOP_CNT);
				player_->SetIsDeath(true);
			}
		}
	}
}

void Level6::CreateFireBall()
{
	//���Ԍ��炷
	fireCnt_++;
	int cnt = GetCreateFireBallCnt();
	if (fireCnt_ >= fireCreateCnt_)
	{
		for (int i = 0; i < cnt; i++)
		{
			FireBall* fire = GetValidFireBall();

			//�����̐���
			fire->Create(this, FIRE_BALL_SPEED);
		}
		fireCnt_ = 0;
		fireCreateCnt_ = CREATE_INTERVAL + rand() % CREATE_RAND_RANGE;
	}
}

//�������Ƃɉ΂̋ʂ̐����������߂�
int Level6::GetCreateFireBallCnt()
{
	// �������擾
	int height = GetBlockHeight();

	// �J�E���g�l��������
	int cnt = CNT_VALUES[EVENT_CHANGE];  // �ŏ��l����J�n

	// 臒l�Ɋ�Â��ăJ�E���g�l��ݒ�
	for (int i = 0; i < EVENT_CHANGE; ++i)
	{
		if (height >= HEIGHT_THRESHOLDS[i]) 
		{
			cnt = CNT_VALUES[i];
			break;
		}
	}

	// ��������Ԃ�
	return cnt;
}

FireBall* Level6::GetValidFireBall()
{
	FireBall* fire = new FireBall();
	fire_.push_back(fire);
	return fire;
}
