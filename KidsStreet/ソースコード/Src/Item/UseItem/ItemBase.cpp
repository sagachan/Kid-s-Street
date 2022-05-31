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

//現在使用継続しているかどうか
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
	//プレイヤークラス取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	CItemManager* item_manager = CItemManager::GetInstance();
	CBoss* boss = CEnemyManager::GetInstance()->GetBoss();

	//この処理を何回通ったかを格納する
	frm_int_++;

	//ボスがアイテムをキャッチしていない時は
	if (!bossFlg_)
	{
		//一度しか通らない処理
		if (!doOnce_)
		{
			doOnce_ = true;
			//プレイヤーの向きベクトルを取得
			forward_vec_ = player->GetForwardVec();
		}

		//移動計算
		pos_.x += forward_vec_.x * add_pos_;
		pos_.z += forward_vec_.z * add_pos_;

		if (frm_int_ > END_TIME)
		{
			endflg_ = true;
			frm_int_ = 0;
			doOnce_ = 0;
		}
	}


	//ボスがアイテムをキャッチしているときはダメージを0にする
	//アイテムとプレイヤーの当たり判定も有効化
	if (bossFlg_)
	{
		dmg_ = 0;

		if (bossThrowFlg_)
		{
			if (!bossDoOnce_)
			{
				CBoss* boss = CEnemyManager::GetInstance()->GetBoss();
				CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

				//ボスの向きベクトルを取得
				forward_vec_ = CMyMath::VecCreate(boss->GetPosition(), player->GetPosition());
				bossDoOnce_ = true;
			}

			//アイテムが投げられた時に格納された方向に向かって
			pos_.x += forward_vec_.x;
			pos_.z += forward_vec_.z;

			//ボスに投げられて一定時間後ボスフラグを折る
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