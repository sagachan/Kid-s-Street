//Pencil.cpp
//���M�N���X

#include "../../../Library/MyMath/MyMath.h"
#include "../../../Player/PlayerManager.h"
#include "../../../Enemy/EnemyManager.h"
#include "../ItemManager.h"
#include "../../../Enemy/EnemyBase.h"
#include "Pencil.h"
#include "../../../Library/Input/Input.h"

namespace
{
	const float SCALE = 1.0;						//�傫��
	const VECTOR POS = VGet(0.0f,0.0f,0.0f);		//�ʒu
	const VECTOR ROT = VGet(4.71f,0.0f,0.0f);		//��]�l
	const float SPEED = 1.0;						//��ԑ��x
	const float SIMPLE_HIT_RADIUS = 1.0;			//�ȈՓ����蔻��p
	const int DMG = 15;
	
}

void CPencil::Load()
{
	//���f���n���h���ǂݍ���
	LoadModel("Data/Item/Enpitu.x");
	id_ = ITEM_ID_PENCIL;
}


void CPencil::Set()
{

	add_pos_ = SPEED;
	rot_ = ROT;
	dmg_ = DMG;
	rad_ = SIMPLE_HIT_RADIUS;
}


void CPencil::Step()
{
	//�v���C���[�N���X�擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	
	//�����Ă���A�C�e�����v���C���[�̌����Ă����������������
	rot_.y = player->GetRot().y;
}


void CPencil::Draw()
{
	//���f���̉�]
	MV1SetRotationXYZ(hndl_, rot_);

	//���f���̈ʒu���W�Z�b�g
	MV1SetPosition(hndl_, pos_);
	MV1SetScale(hndl_, scale_);
	//���f���`��
	MV1DrawModel(hndl_);
}

void CPencil::Fin()
{
	DeleteModel();
}