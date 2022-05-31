#include "ItemBase.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Enemy/EnemyCommon.h"
#include "ItemManager.h"

CItemBase::CItemBase()
{
	appear_flg_ = false;
	isUse_ = false;
	endflg_ = false;
	doOnce_ = false;
	bossFlg_ = false;
	bossThrowFlg_ = false;
	bossDoOnce_ = false;
	itemNum_ = 0;
}

CItemBase::~CItemBase()
{

}

//���ݎg�p�p�����Ă��邩�ǂ���
bool CItemBase::GetMoveFlg()
{
	if (isUse_ && !endflg_)
	{
		return true;
	}
	else
	{
		return false; 
	}
}

void CItemBase::Move()
{
	//�v���C���[�N���X�擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	CItemManager* item_manager = CItemManager::GetInstance();
	CBoss* boss = CEnemyManager::GetInstance()->GetBoss();

	//���̏���������ʂ��������i�[����
	frm_int_++;

	//�{�X���A�C�e�����L���b�`���Ă��Ȃ�����
	if (!bossFlg_)
	{
		//��x�����ʂ�Ȃ�����
		if (!doOnce_)
		{
			doOnce_ = true;
			//�v���C���[�̌����x�N�g�����擾
			forward_vec_ = player->GetForwardVec();
		}

		//�ړ��v�Z
		pos_.x += forward_vec_.x * add_pos_;
		pos_.z += forward_vec_.z * add_pos_;

		if (frm_int_ > END_TIME)
		{
			endflg_ = true;
			frm_int_ = 0;
			doOnce_ = 0;
		}
	}


	//�{�X���A�C�e�����L���b�`���Ă���Ƃ��̓_���[�W��0�ɂ���
	//�A�C�e���ƃv���C���[�̓����蔻����L����
	if (bossFlg_)
	{
		dmg_ = 0;

		if (bossThrowFlg_)
		{
			if (!bossDoOnce_)
			{
				CBoss* boss = CEnemyManager::GetInstance()->GetBoss();
				CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

				//�{�X�̌����x�N�g�����擾
				forward_vec_ = CMyMath::VecCreate(boss->GetPosition(), player->GetPosition());
				bossDoOnce_ = true;
			}

			//�A�C�e����������ꂽ���Ɋi�[���ꂽ�����Ɍ�������
			pos_.x += forward_vec_.x;
			pos_.z += forward_vec_.z;

			//�{�X�ɓ������Ĉ�莞�Ԍ�{�X�t���O��܂�
			if (frm_int_ > BOSS_THROW_TIME)
			{
				bossFlg_ = false;
				bossDoOnce_ = false;
				endflg_ = true;
				frm_int_ = 0;
				doOnce_ = 0;
			}
		}
	}
}