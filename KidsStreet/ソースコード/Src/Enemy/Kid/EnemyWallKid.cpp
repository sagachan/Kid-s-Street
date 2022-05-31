//�q���N���X
#include "EnemyWallKid.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Item/GatherItem/GatherFactory/GatherManager.h"
#include "../../Item/ItemCommon.h"
#include "../EnemyManager.h"
#include "../EnemyCommon.h"

namespace{
	const float		KID_RADIUS = 8.0f;										//�q���̓����蔻��͈�
	const int		KID_DMG = 5;
	const int		BIND_TIME = 120;
}

//�R���X�g���N�^
CWallKid::CWallKid()
	:dir_(MOVE_INIT){
	
}

//�f�X�g���N�^
CWallKid::~CWallKid(){
	Fin();
}

//�Z�b�g
void CWallKid::SetPos(VECTOR pos, CEnemyBase::MOVE_DIR dir)
{
	pos_ = pos;
	dir_ = dir;

}


//�Z�b�g
void CWallKid::Set()
{
	LoadModel("Data/Enemy/Kid/mapKidBone.x");
	MV1SetPosition(hndl_, pos_);

	rad_ = KID_RADIUS;

	//�����^�C�v�ɂ���ĉ�]
	if (dir_ == FRONT_MOVE){
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_FRONT);
	}
	if (dir_ == BACK_MOVE){
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_BACK);
	}
	if (dir_ == RIGHT_MOVE){
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_RIGHT);
	}
	if (dir_ == LEFT_MOVE){
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_LEFT);
	}
}

//�ǂݍ��݁i���[�h�j
void CWallKid::Load(){
	//���f���ǂݍ���
	LoadModel("Data/Enemy/Kid/enemy_kid.x");
	//�A�j���[�V��������
	CAnim3D::RequestLoop(BIND, 1.0f, (int)-1, (bool)-1);
}

//�`��
void CWallKid::Draw(){
	CAnim3D::UpdateAnim();
	MV1DrawModel(hndl_);
}

//�폜
void CWallKid::Delete(){
	hndl_ = MV1DeleteModel(hndl_);
}

//�㏈��
void CWallKid::Fin(){
	//Delete���Ă΂�Ă��Ȃ��Ȃ�
	if (hndl_ != 0){
		//�폜s���Ă�ł���
		Delete();
	}
}

void CWallKid::Hit()
{
	//�n���h�����폜����Ă����珈�����Ȃ�
	if (hndl_ != 0)
	{
		//�A�C�e���������Ă���Ȃ�n���h�����폜����
		bool* gatherFlg = CGatherManager::GetInstance()->GetGatherItem();
		if (gatherFlg[GLOVE]) {
			Delete();
		}
		//�v���C���[���A�C�e�����������ɂ��̎q�����������������ɐi�����Ƃ�����O����W�ɖ߂���UI�\��
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		if (pos_.z < player->GetPosition().z)
		{
			player->HitSet();
			CEnemyManager::GetInstance()->GetKidUI()->SetKidFlg(true);
			CGameUIManager::GetInstance()->SetInputFlg(true);
		}

	}
}
