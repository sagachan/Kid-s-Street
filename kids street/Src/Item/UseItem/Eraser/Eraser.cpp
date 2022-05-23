//Eraser.cpp
//�����S���N���X

#include "../../../Library/MyMath/MyMath.h"
#include "../../../Player/PlayerManager.h"
#include "../../../Enemy/EnemyManager.h"
#include "../ItemManager.h"
#include "../../../Enemy/EnemyBase.h"
#include "Eraser.h"
#include "../../../Library/Input/Input.h"
#include "../../../Library/MyMath/MyMath.h"

namespace
{
	const float SCALE = 1.0;//�傫��
	const VECTOR POS = VGet(0.0f, 0.0f, 0.0f);	//�ʒu
	const VECTOR ROT = VGet(0.0f, 0.0f, 0.0f);	//��]�l
	const float SPEED = 0.3f;		//��ԑ��x
	const float SIMPLE_HIT_RADIUS = 2.0;			//�ȈՓ����蔻��p
	const int DMG = 10;
}

void CEraser::Load()
{
	//���f���n���h���ǂݍ���
	LoadModel("Data/Item/BunishGom.x");
	id_ = ITEM_ID_ERASER;
}

void CEraser::Set()
{
	add_pos_ = SPEED;
	dmg_ = DMG;
	rad_ = SIMPLE_HIT_RADIUS;
	rot_ = ROT;
}

void CEraser::Draw()
{
	//���f���̉�]
	MV1SetRotationXYZ(hndl_, rot_);
	//���f���̈ʒu���W�Z�b�g
	MV1SetPosition(hndl_, pos_);
	MV1SetScale(hndl_, scale_);
	//���f���`��
	MV1DrawModel(hndl_);
}

void CEraser::Fin()
{
	DeleteModel();
}

