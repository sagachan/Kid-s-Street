
#include "../Player/PlayerManager.h"
#include "CollisionManager.h"
#include "../Library/MyMath/MyMath.h"
#include "../Player/PlayerCommon.h"
#include "../Enemy/EnemyCommon.h"
#include "ColField/ColField.h"

//CEnemyManager�̎��̐錾�A������
CCollisionManager* CCollisionManager::instance_ = nullptr;


CCollisionManager::CCollisionManager()
{
	//�����ŌĂ΂��
	Init();
}

CCollisionManager::~CCollisionManager()
{
	//�����ŌĂ΂��
	Delete();
}

void CCollisionManager::Init()
{
	
}

void CCollisionManager::Step()
{
	//�����蔻������擾
	//�i���̊֐����ň�����n����setcollision�֐����Ă�ł���
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();
	enemyManager->GetBoss()->Hit();
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		enemyManager->GetEnemy(carNum)->CheckColCube();
	}
	CItemManager::GetInstance()->HitUpdate();
	BossHit();

	//�}�b�v�Ƃ̓����蔻��֌W�X�V
	CColField::CheckColField();
}

void CCollisionManager::Delete()
{
	Fin();
}

void CCollisionManager::Fin()
{
	
}

void CCollisionManager::SetBossCollision(VECTOR framePos[FRAME_MAX], float rad)
{
	for (int kind = 0; kind < FRAME_MAX; kind++)
	{
 		bossData_[kind].pos_ = framePos[kind];
		bossData_[kind].rad_ = rad;
	}
}

void CCollisionManager::SetItemCollision(ITEM_DATA* itemData)
{
	for (int kind = 0; kind < MAX_ITEM_NUM; kind++){
		itemData_[kind].pos_ = itemData[kind].pos_;
		itemData_[kind].useflg_ = itemData[kind].useflg_;
		itemData_[kind].rad_ = itemData[kind].rad_;
	}
	
}

//�{�X�Ɋւ��铖���蔻�� (�ʃN���X�ɕ�����
void CCollisionManager::BossHit()
{
	//�v���C���[�̏��擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR player_pos = player->GetPosition();
	CItemManager* itemManager = CItemManager::GetInstance();
	CBoss* boss = CEnemyManager::GetInstance()->GetBoss();

	//�����ł̓{�X�̃{�[����---���ׂ鏈��
	//�{�X�̃{�[���̐��������[�v����Q�Ə���
	for (int frame_num = 0; frame_num < FRAME_MAX; frame_num++){
		//�A�C�e���̐������`�F�b�N����
		for (int item_num = 0; item_num < MAX_ITEM_NUM; item_num++){
			//���ݎg�p����Ă�����̂����`�F�b�N���Ȃ��Ă�����
			if (itemData_[item_num].useflg_){
				//�����蔻��m�F
				//�A�C�e��
				if (CCollision::IsHitRect(bossData_[frame_num].pos_, bossData_[frame_num].rad_, bossData_[frame_num].rad_, bossData_[frame_num].rad_,
					itemData_[item_num].pos_, itemData_[item_num].rad_, itemData_[item_num].rad_, itemData_[item_num].rad_))
				{
					//�����蔻�菈�����������Ă���Ȃ炱����ʂ�
					//�{�X���Ή��ł���ꍇ
					if (boss->GetCounterFlg())
					{
						//�{�XAI�̃J�E���^�[�t���O��true��
						boss->SetBossAIFlg(true);
						//�G�ꂽ�A�C�e���̃{�X�擾�t���O��true�ɂ���֐����Ă�
						itemManager->SetBossItemInfo(item_num);
					}
					else if (!boss->GetCounterFlg())
					{
						//�A�C�e���������āA���̃A�C�e���̃_���[�W���{�X�ɗ^����
						itemManager->DamageVanish(item_num);
					}
				}
			}
		}

		//�v���C���[
		if (CCollision::IsHitRect(bossData_[frame_num].pos_, bossData_[frame_num].rad_, bossData_[frame_num].rad_, bossData_[frame_num].rad_,
			player_pos, PLAYER_COL.x, PLAYER_COL.y, PLAYER_COL.z) == true)
		{
			//�����������ɋN���鏈��
			CPlayerManager::GetInstance()->GetPlayer()->AddDamage(1);
		}
	}
	
}

//�A�C�e�����{�X�ɂ���ē������Ă���Ƃ��ɒʂ铖���蔻�菈��
void CCollisionManager::BossItemHit(VECTOR pos, float rad)
{
	//�v���C���[�̏��擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR player_pos = player->GetPosition();
	VECTOR PLAYER_COL = player->GetSize();

	//�v���C���[
	if (CCollision::IsHitRect(pos, rad, rad, rad,
		player_pos, PLAYER_COL.x, PLAYER_COL.y, PLAYER_COL.z))
	{
		//�����������ɋN���鏈��
		player->AddDamage(ERASER_DMG);
	}
}

void CCollisionManager::ChaseHit()
{
	//�����Ń`�F�C�X�{�X�̈ʒu���ƊȈՔ��a���󂯎��A������J�n����
	//��̃{�X�̓����蔻��Ƃ͈Ⴂ�A�ȈՔ���ɂ��邱�Ƃœ�Փx���グ
	//�v���C���[�ɋْ�������������
	//�ȈՔ��a����̓G�l�~�[�𒆐S�Ƃ��Ďl�p���L���[�u���C���[�W���č�邽�ߐ����`�̓����蔻����g�p�\


}

