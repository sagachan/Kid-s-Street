//Pole.cpp
//�t�B�[���h�N���X
//�����蔻�����ʂȏ����������Ȃ��I�u�W�F�N�g�֌W

#include "Pole.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"

//�t�B�[���h�֘A
namespace
{
	VECTOR FIELD_POS = VGet(-1550.0f, 1.0f, 1750.0f);	//�t�B�[���h�̍��W
	VECTOR POLE_ROT = VGet(0.0f, 0.0f, 0.0f);
}

CPole::CPole()
	:posFlg_(true)
{
	
}

//�f�X�g���N�^
CPole::~CPole()
{
	Fin();
}

void CPole::Set()
{
	MV1SetPosition(hndl_, FIELD_POS);
}

void CPole::Load()
{
	LoadModel("Data/Map/Field/UtilityPole.x");
}


void CPole::Update()
{
	//�{�X�����̓d�����������ǂ���
	CBoss* boss = CEnemyManager::GetInstance()->GetBoss();
	if (boss->ai_state_ == AIBase::BOSS_SLASH)
		posFlg_ = false;
	else
		posFlg_ = true;

	//�g���ĂȂ��Ȃ珉���ʒu�A������]�l�ɖ߂�
	if (posFlg_){
		pos_ = FIELD_POS;
		rot_ = POLE_ROT;
	}
	

	MV1SetPosition(hndl_, pos_);
	MV1SetRotationXYZ(hndl_, rot_);
}


void CPole::Draw()
{
	MV1DrawModel(hndl_);
}


void CPole::Delete()
{
	DeleteModel();
}


void CPole::Fin()
{
	if (hndl_ != 0){
		//Delete���Ă�ł���
		Delete();
	}
}

