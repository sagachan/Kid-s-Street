//Ruler.cpp

#include "../../../Library/MyMath/MyMath.h"
#include "../ItemManager.h"
#include "../../../Enemy/EnemyBase.h"
#include "Ruler.h"
#include "../../../Collision/CollisionManager.h"
#include "../../../Collision/CollisionCommon.h"
#include "../../../Library/LibraryCommon.h"
#include "../../../Enemy/EnemyManager.h"

namespace
{
	const float SCALE = 1.0;						//�傫��
	const VECTOR POS = VGet(0.0f,0.0f,0.0f);		//�ʒu
	const VECTOR ROT = VGet(4.71f,1.6f,0.0f);		//��]�l
	const float ROLL_SPD = 0.5f;							//��]���x
	const float SPEED = 1.0;						//��ԑ��x
	const float SIMPLE_HIT_RADIUS = 4.0;			//�ȈՓ����蔻��p
	const VECTOR COL_RADIUS = VGet(4.0f, 4.0f, 4.0f);
	
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
	dmg_ = RULER_DMG;
	rad_ = SIMPLE_HIT_RADIUS;
	rot_ = ROT;

	//�����蔻��𐶐�
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_.pos_ = pos_;
	colData_.cubeRad_ = COL_RADIUS;
	colData_.useFlg_ = false;
	colData_.myList_ = COL_CHECK_ITEM;
	colData_.type_.pawn_ = CHECK_BOX_HIT;
	colData_.type_.static_ = CHECK_BOX_NONE;
	colData_.type_.dynamic_ = CHECK_BOX_NONE;
	colData_.object_ = OBJECT_DYNAMIC;
	colData_.shapeCol_ = SHAPE_CUBE;

	colNum_ = collision->CreateCol(&colData_);
}


void CRuler::Step()
{
	Hit();
	//�v���C���[�N���X�擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//�����Ă���A�C�e�����v���C���[�̌����Ă����������������
	rot_.y = player->GetRot().y + ROT.y;

	rot_.x = ROT.x;
}

void CRuler::Update()
{
	Hit();

	rot_.x = 0.0f;
	rot_.y += ROLL_SPD;

	//�����蔻��֌W�X�V
	CCollisionManager::GetInstance()->SetUpdateColInfo(colNum_, pos_, GetMoveFlg());
}

void CRuler::Hit()
{
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_ = collision->GetCollisionData(colNum_);
	//�����̓����蔻��list�ɓ����I�u�W�F�N�g���G��Ă����ꍇ�ɏ����𕡐���J��Ԃ��Ă��܂�Ȃ��悤�ɂ���
	//�������s�������X�g�̃^�C�v�̌�enum�ԍ��̃t���O�𗧂Ă�
	bool checkFlg[COL_CHECK_MAX] = { false };

	if (colData_.hitFlg_)
	{
		for (int checkNum = 0; checkNum < COL_CHECK_MAX; checkNum++)
		{
			//�������Ă����̂��{�X�̎�
			if (colData_.list_[checkNum] == COL_CHECK_BOSS && !checkFlg[COL_CHECK_BOSS])
			{
				CBoss* boss = CEnemyManager::GetInstance()->GetBoss();
				CItemManager* itemManager = CItemManager::GetInstance();
				//�{�X���Ή��ł���ꍇ
				if (boss->GetCounterFlg())
				{
					boss->SetBossAIFlg(true);
					itemManager->SetBossItemInfo(itemNum_);
				}
				else
				{
					//�A�C�e���������āA���̃A�C�e���̃_���[�W���{�X�ɗ^����
					itemManager->DamageVanish(itemNum_);
				}

				checkFlg[COL_CHECK_BOSS] = true;
			}
		}
	}
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