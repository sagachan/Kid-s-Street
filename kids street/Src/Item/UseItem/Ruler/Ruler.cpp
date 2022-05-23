//Ruler.cpp

#include "../../../Library/MyMath/MyMath.h"
#include "../ItemManager.h"
#include "../../../Enemy/EnemyBase.h"
#include "Ruler.h"

namespace
{
	const float SCALE = 1.0;						//�傫��
	const VECTOR POS = VGet(0.0f,0.0f,0.0f);		//�ʒu
	const VECTOR ROT = VGet(4.71f,1.6f,0.0f);		//��]�l
	const float ROLL_SPD = 0.5f;							//��]���x
	const float SPEED = 1.0;						//��ԑ��x
	const float SIMPLE_HIT_RADIUS = 4.0;			//�ȈՓ����蔻��p
	const int DMG = 15;
	
}

void CRuler::Load()
{
	//���f���n���h���ǂݍ���
	LoadModel("Data/Item/Ruler.x");
	id_ = ITEM_ID_RULER;
}


void CRuler::Set()
{

	add_pos_ = SPEED;
	dmg_ = DMG;
	rad_ = SIMPLE_HIT_RADIUS;
	rot_ = ROT;
}


void CRuler::Step()
{
	//�v���C���[�N���X�擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//�����Ă���A�C�e�����v���C���[�̌����Ă����������������
	rot_.y = player->GetRot().y + ROT.y;

	rot_.x = ROT.x;
}

void CRuler::Update()
{
	rot_.x = 0.0f;
	rot_.y += ROLL_SPD;
}


void CRuler::Draw()
{
	//���f���̉�]
	MV1SetRotationXYZ(hndl_, rot_);

	//���f���̈ʒu���W�Z�b�g
	MV1SetPosition(hndl_, pos_);
	MV1SetScale(hndl_, scale_);
	//���f���`��
	MV1DrawModel(hndl_);
}


void CRuler::Fin()
{
	DeleteModel();
}