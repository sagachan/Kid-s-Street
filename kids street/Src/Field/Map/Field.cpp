//Field.cpp
//�t�B�[���h�N���X

#include "Field.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Player/PlayerManager.h"

//�t�B�[���h�֘A
namespace
{
	VECTOR FIELD_POS = VGet(0.0f, 0.0f, 0.0f);	//�t�B�[���h�̍��W
	int    FIELD_D = 36;						//�t�B�[���h�̉��s
}

//�R���X�g���N�^
CField::CField()
{
	Init();
}

//�f�X�g���N�^
CField::~CField()
{
	Fin();
}


void CField::Init()
{
	//��]�l
	rot_ = { 0.0f };
	
	for (int type_num = 0; type_num < MAP_TYPE_NUM; type_num++)
	{
		m_handle[type_num] = 0;
	}
}


void CField::Load()
{
	//���[�h
	m_handle[school] = MV1LoadModel("Data/Map/Field/school.x");
	m_handle[bill] = MV1LoadModel("Data/Map/Field/bill.x");
	m_handle[house] = MV1LoadModel("Data/Map/Field/house.x");
	m_handle[sky] = MV1LoadModel("Data/Map/Field/sky.x");
}


void CField::Set()
{
	
}


void CField::Step()
{
	
}


void CField::Update()
{
	//�v���C���[�ʒu���擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//�Ƃ肠�������ꂽ���f���S�������l��
	for (int type_num = 0; type_num < MAP_TYPE_NUM; type_num++)
	{
		MV1SetPosition(m_handle[type_num], VGet(-20.0f, -1.0f, 0.0f));
	}

	//�������W�ɕύX��������̂����������ŕύX
	MV1SetPosition(m_handle[sky], player->GetPosition());
}


void CField::Draw()
{
	

	for (int type_num = 0; type_num < MAP_TYPE_NUM; type_num++)
	{ 
		MV1DrawModel(m_handle[type_num]);
	}
	
}


void CField::Delete()
{
	for (int type_num = 0; type_num < MAP_TYPE_NUM; type_num++)
	{
		MV1DeleteModel(m_handle[type_num]);
		m_handle[type_num] = 0;
	}
}


void CField::Fin()
{
	if (m_handle[0] != 0)
	{
		//Delete���Ă�ł���
		Delete();
	}
}