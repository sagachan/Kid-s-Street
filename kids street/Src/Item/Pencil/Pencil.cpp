//Pencil.cpp
//鉛筆クラス

#include "../../MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../ItemManager.h"
#include "../../Enemy/EnemyBase.h"
#include "Pencil.h"
#include "../../Input/Input.h"

namespace
{
	const float SCALE = 1.0;						//大きさ
	const VECTOR POS = VGet(0.0f,0.0f,0.0f);		//位置
	const VECTOR ROT = VGet(4.71f,0.0f,0.0f);		//回転値
	const float SPEED = 1.0;						//飛ぶ速度
	const VECTOR HIT_RADIUS = VGet(1.0, 1.0, 1.0);	//当たり判定の広さ
	const float SIMPLE_HIT_RADIUS = 1.0;			//簡易当たり判定用
	const int DMG = 15;
	const int END_TIME = 150;					//使用開始されてから使用終了までの時間
	const int BOSS_THROW_TIME = 1000;			//ボスによって投げられた時にどのくらいで消えるか
}

//コンストラクタ
CPencil::CPencil()
{
	Init();
}

//デストラクタ
CPencil::~CPencil()
{
	Fin();
}


void CPencil::Init()
{
	appear_flg_ = false;
	isUse_ = false;
	endflg_ = false;
	doOnce_ = false;
	bossFlg_ = false;
	bossThrowFlg_ = false;
	bossDoOnce_ = false;
}


void CPencil::Load()
{
	//モデルハンドル読み込み
	LoadModel("Data/Item/Enpitu.x");
}


void CPencil::Set()
{
	hit_radius_ = HIT_RADIUS;
	add_pos_ = SPEED;
	m_rot_ = ROT;
	dmg_ = DMG;
	radius_ = SIMPLE_HIT_RADIUS;
}


void CPencil::Step()
{
	//プレイヤークラス取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	m_rot_.y = player->GetRot().y;
}

void CPencil::Move()
{
	//プレイヤークラス取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	CItemManager* item_manager = CItemManager::GetInstance();
	CBoss* boss = CEnemyManager::GetInstance()->GetBoss();

	//この処理を何回通ったかを格納する
	add_num_++;

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

		if (add_num_ > END_TIME)
		{
			endflg_ = true;
			add_num_ = 0;
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
				//ボスの向きベクトルを取得
				forward_vec_ = boss->GetForwardVec();
				bossDoOnce_ = true;
			}
			CCollisionManager::GetInstance()->BossItemHit(pos_, m_rad_);

			//アイテムが投げられた時に格納された方向に向かって
			pos_.x += forward_vec_.x;
			pos_.z += forward_vec_.z;

			//ボスに投げられて一定時間後ボスフラグを折る
			if (add_num_ > BOSS_THROW_TIME)
			{
				bossFlg_ = false;
				bossDoOnce_ = false;
				endflg_ = true;
				add_num_ = 0;
				doOnce_ = 0;

			}
		}
		else
		{
			//ここを通っているときはボスクラスのほうで位置情報が更新されている
		}
	}
}

void CPencil::Update()
{

}


void CPencil::Draw()
{
	//モデルの回転
	MV1SetRotationXYZ(m_hndl_, m_rot_);

	//モデルの位置座標セット
	MV1SetPosition(m_hndl_, pos_);
	MV1SetScale(m_hndl_, m_scale_);
	//モデル描画
	MV1DrawModel(m_hndl_);
}


void CPencil::Delete()
{

}


void CPencil::Fin()
{

}