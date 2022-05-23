//EnemyManager.cpp
//�G�l�~�[�Ǘ�
//CEnemy�ւ̃A�N�Z�X�͕K��CEnemyManager���o�R

#include "EnemyManager.h"
#include "../Library/Error/Error.h"
#include "../Field/FieldCommon.h"
#include "Boss/BossHP/BossFrameHP.h"
#include "Boss/BossHP/BossHP.h"
#include "../UI/GameUIManager.h"
#include "../Library/Sound/Sound.h"

namespace
{													
	const VECTOR	ENEMY_BOSS_APPEAR = VGet(-1520.0f, 0.0f,1700.0f);					//�{�X�o�����C��
	const VECTOR	ENEMY_BOSS_AREA_BACK = VGet(4.0f,6.0f,890.0f);
	const VECTOR	ENEMY_BOSS_AREA_FRONT = VGet(4.0f, 6.0f, 970.0f);
}

//CEnemyManager�̎��̐錾�A������
CEnemyManager* CEnemyManager::instance_ = nullptr;


//�R���X�g���N�^
CEnemyManager::CEnemyManager()
{
	//CEnemy�̃R���X�g���N�^�͎����ŌĂ΂�܂�
	Init();
}

//�f�X�g���N�^
CEnemyManager::~CEnemyManager()
{
	//CEnemy�̃f�X�g���N�^�͎����ŌĂ΂�܂�
	
}


//������
void CEnemyManager::Init()
{
	Sceneflg_ = true; //�؂�ւ���ƃV�[���ύX
	pos_plus_ = { 0 };//�ԓ��m�̊Ԋu��

	int enemyNum = 0;
	for (enemyNum = 0; enemyNum < APPEAR_CAR_NUM; enemyNum++){
		car_[enemyNum] = new CEnemy;
		carInfo_[enemyNum] = car_[enemyNum];
		enemy_[enemyNum] = car_[enemyNum];
	}
	for (int enemy_index = 0; enemy_index < APPEAR_KID_NUM; enemy_index++){
		kid_[enemy_index] = new CKid;
		kidInfo_[enemy_index] = kid_[enemy_index];
		enemy_[enemyNum] = kid_[enemy_index];
		enemyNum++;
	}

	for (int enemy_index = 0; enemy_index < APPEAR_WALL_NUM; enemy_index++) {
		wall_[enemy_index] = new CWallKid;
		wallInfo_[enemy_index] = wall_[enemy_index];
		enemy_[enemyNum] = wall_[enemy_index];
		enemyNum++;
	}

	boss_ = new CBoss;
	enemy_[enemyNum] = boss_;
	bossInfo_ = enemy_[enemyNum];
	enemyNum++;
	
	chase_ = new CChaseBoss;
	enemy_[enemyNum] = chase_;
	chaseInfo_ = enemy_[enemyNum];
	enemyNum++;

	//UI�֌W
	ui_[BOSS_HP] = new CBossHP;
	ui_[BOSS_FRAME_HP] = new CBossFrameHP;
	kidUI_ = new CKidUI;
	ui_[KID_ASSERT] = kidUI_;

	MinimizeCall(enemy_, APPEAR_ENEMY_MAX_NUM, VOID_INIT);
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_INIT);
}


//�ǂݍ���
void CEnemyManager::Load()
{
	MinimizeCall(enemy_, APPEAR_ENEMY_MAX_NUM, VOID_LOAD);
	
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_LOAD);
}


//�Z�b�g
void CEnemyManager::Set()
{
	//�Ԃ̏o�����W���{�[���Ō��߂�
	int carAppearFrm = 0;
	//�{�[�����ǂݍ���
	carAppearFrm = MV1LoadModel("Data/Enemy/Car/carPosBone.x");

	//�Ԃ̃{�[���̍ő�l�󂯎��
	int carBoneMax = MV1GetFrameNum(carAppearFrm);

	//�{�[����񂩂�ʒu����ǂݎ��z��ɓ����
	VECTOR* carPos = (VECTOR*)malloc(sizeof(VECTOR) * APPEAR_CAR_NUM);

	//�Ԃ̏o�����W���{�[���ŊǗ��A���W���{�[������ǂݎ��z��ɓ����
	int trueNum = 0;
	for (int frmNum = 0; frmNum < carBoneMax;frmNum++){
		if (frmNum % 2){
			carPos[trueNum] = MV1GetFramePosition(carAppearFrm, frmNum);
			trueNum++;
			if (trueNum == APPEAR_CAR_NUM)
				break;
		}
	}

	//�Ԃ̃e�[�u��
	EnemyInfo carData[APPEAR_CAR_NUM] = { 0 };

	//�Ԃ̏o�����W�̂�����������������
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++){
		carData[carNum] = CAR_DATA[carNum];
		carData[carNum].pos_.z = carPos[carNum].z;
	}

	free(carPos);

	for (int enemy_index = 0; enemy_index < APPEAR_CAR_NUM; enemy_index++){
		//�Ԃ̏����ʒu�ݒ�
		car_[enemy_index]->SetPos(carData[enemy_index].pos_, carData[enemy_index].dir_);
	}


	//�q�ǂ��̏o�����W
	for (int enemy_index = 0; enemy_index < APPEAR_KID_NUM; enemy_index++)
	{
		kid_[enemy_index]->SetRoute(KID_ROUTE_NUM[enemy_index]);
	}

	
	
	for (int enemy_index = 0; enemy_index < APPEAR_WALL_NUM; enemy_index++) {
		//�����ʒu�ݒ�
		wall_[enemy_index]->SetPos(WALL_DATA[enemy_index].pos_, WALL_DATA[enemy_index].dir_);
	}

	CFieldManager* fieldManager = CFieldManager::GetInstance();
	CInter* inter = fieldManager->GetInter();

	//�����_�n���h�����i�[
	int interHndl = inter->GetFrmHndl();
	VECTOR	bossInterPos = MV1GetFramePosition(interHndl, 28);
	bossInterPos.y = -1.0f;
	bossInterPos.z -= 5.0f;

	//�{�X�����ʒu�ݒ�
	boss_->SetPosition(bossInterPos);
	bossflg_ = true;

	MinimizeCall(enemy_, APPEAR_ENEMY_MAX_NUM, VOID_SET);
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_SET);
}


//�X�e�b�v
void CEnemyManager::Step()
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	CFieldManager* fieldManager = CFieldManager::GetInstance();
	CInter* inter = fieldManager->GetInter();
	
	//�����_�n���h�����i�[
	int interHndl = inter->GetFrmHndl();
	VECTOR	bossInterPos = MV1GetFramePosition(interHndl, 28);
	VECTOR	playerPos = player->GetPosition();
	float	interRad = inter->GetInterRad() / 2;


	//�{�X��J�n����
	if (CMyMath::RadiusCheck(bossInterPos.x, interRad, playerPos.x) &&
		CMyMath::RadiusCheck(bossInterPos.z, interRad, playerPos.z) &&
		Sceneflg_ == true)
	{
		CSound::FinSound();
		CSound::LoadBGM(CSound::BGM_BOSS);
		CSound::PlayBGM(CSound::BGM_BOSS);
		Sceneflg_ = false;
	}

	//���^�[�����������Ƃ��Ƀ{�X�킩�甲���Ēʏ탋�[�v�֖߂鏈��
	if (CInput::GetInstance()->IsPush(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_RETURN)){
		Sceneflg_ = true;
		bossflg_ = false;
	}


	if (Sceneflg_){
		MinimizeCall(carInfo_, APPEAR_CAR_NUM, VOID_STEP);
		MinimizeCall(kidInfo_, APPEAR_KID_NUM, VOID_STEP);
		chaseInfo_->Step();
	}
	else{
		bossInfo_->Step();
		WallCage();
	}

	MinimizeCall(wallInfo_, SET_WALL_NUM, VOID_HIT);
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_STEP);
}

//���f
void CEnemyManager::Update()
{
	if (Sceneflg_){
		MinimizeCall(carInfo_, APPEAR_CAR_NUM, VOID_UPDATE);
		MinimizeCall(kidInfo_, APPEAR_KID_NUM, VOID_UPDATE);
		chaseInfo_->Update();
	}
	else{
		bossInfo_->Update();
	}
}


//�`��
void CEnemyManager::Draw()
{
	if (Sceneflg_){
		MinimizeCall(carInfo_, APPEAR_CAR_NUM, VOID_DRAW);
		MinimizeCall(kidInfo_, APPEAR_KID_NUM, VOID_DRAW);
		MinimizeCall(wallInfo_, SET_WALL_NUM, VOID_DRAW);
		chaseInfo_->Draw();
	}
	else{
		bossInfo_->Draw();
		for (int enemy_index = SET_WALL_NUM; enemy_index < APPEAR_WALL_NUM; enemy_index++)
		{
			wallInfo_[enemy_index]->Draw();
		}
	}

	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_DRAW);
}


//�폜
void CEnemyManager::Delete()
{
	MinimizeCall(enemy_, APPEAR_ENEMY_MAX_NUM, VOID_DELETE);
}


//�㏈��
void CEnemyManager::Fin()
{
	MinimizeCall(enemy_, APPEAR_ENEMY_MAX_NUM, VOID_FIN);
	
	for (int enemyNum = 0; enemyNum < APPEAR_ENEMY_MAX_NUM; enemyNum++){
		delete enemy_[enemyNum];
		enemy_[enemyNum] = nullptr;
	}
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_FIN);

	CSound::FinSound();
}

//�I�[�o�[���C�h�����N���X�̍\���̂̒��g��num�Ԗڂ܂ŉ񂵂ĎQ�ƁA�^�C�v�ɂ���ď����𕪂���
void CEnemyManager::MinimizeCall(CEnemyBase* enemy[], int maxNum, VOID_TYPE type)
{
	for (int kind = 0; kind < maxNum; kind++){
		switch (type){
		case VOID_INIT:enemy[kind]->Init(); break;
		case VOID_LOAD:enemy[kind]->Load(); break;
		case VOID_SET:enemy[kind]->Set(); break;
		case VOID_STEP:enemy[kind]->Step(); break;
		case VOID_UPDATE:enemy[kind]->Update(); break;
		case VOID_HIT:enemy[kind]->Hit(); break;
		case VOID_DRAW:enemy[kind]->Draw(); break;
		case VOID_DELETE:enemy[kind]->Delete(); break;
		case VOID_FIN:enemy[kind]->Fin(); break;

		//�ǂ�ɂ������Ȃ��ꍇ
		default:CError::MinimizeVoidError();break;
		}
	}
}

void CEnemyManager::WallCage()
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (WALL_X_START > playerPos.x ||
		WALL_X_END < playerPos.x ||
		WALL_Z_START > playerPos.z ||
		WALL_Z_END < playerPos.z)
	{
		player->HitSet();
	}
}