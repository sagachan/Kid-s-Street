//Eraser.cpp
//消しゴムクラス

#include "../../../Library/MyMath/MyMath.h"
#include "../../../Player/PlayerManager.h"
#include "../../../Enemy/EnemyManager.h"
#include "../ItemManager.h"
#include "../../../Enemy/EnemyBase.h"
#include "Eraser.h"
#include "../../../Library/Input/Input.h"
#include "../../../Library/MyMath/MyMath.h"
#include "../../../Collision/CollisionManager.h"
#include "../../../Collision/CollisionCommon.h"
#include "../../../Library/LibraryCommon.h"

namespace
{
	const float SCALE = 1.0;								//大きさ
	const VECTOR POS = VGet(0.0f, 0.0f, 0.0f);				//位置
	const VECTOR ROT = VGet(0.0f, 0.0f, 0.0f);				//回転値
	const float SPEED = 0.3f;								//飛ぶ速度
	const float SIMPLE_HIT_RADIUS = 2.0;					//簡易当たり判定用
	const VECTOR	COL_RADIUS = VGet(4.0f, 4.0f, 4.0f);	//当たり判定範囲(VECTOR)
	
}

void CEraser::Load()
{
	//モデルハンドル読み込み
	LoadModel("Data/Item/BunishGom.x");
	id_ = ITEM_ID_ERASER;
}

void CEraser::Set()
{
	add_pos_ = SPEED;
	dmg_ = ERASER_DMG;
	rad_ = SIMPLE_HIT_RADIUS;
	rot_ = ROT;

	//当たり判定を生成
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_.pos_ = pos_;
	colData_.cubeRad_ = COL_RADIUS;
	colData_.useFlg_ = false;
	colData_.myList_ = COL_CHECK_ITEM;
	colData_.type_.pawn_ = CHECK_BOX_HIT;
	colData_.type_.static_ = CHECK_BOX_NONE;
	colData_.type_.dynamic_ = CHECK_BOX_NONE;
	colData_.object_ = OBJECT_PAWN;
	colData_.shapeCol_ = SHAPE_CUBE;

	colNum_ = collision->CreateCol(&colData_);
}

void CEraser::Step()
{
	
	//プレイヤークラス取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//持っているアイテムがプレイヤーの向いている方向を向く処理
	rot_.y = player->GetRot().y;
}

void CEraser::Update()
{
	Hit();
	//当たり判定関係更新
	CCollisionManager::GetInstance()->SetUpdateColInfo(colNum_, pos_, GetMoveFlg());
}

void CEraser::Hit()
{
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_ = collision->GetCollisionData(colNum_);
	//複数の当たり判定listに同じオブジェクトが触れていた場合に処理を複数回繰り返してしまわないようにする
	//処理を行ったリストのタイプの元enum番号のフラグを立てる
	bool checkFlg[COL_CHECK_MAX] = { false };

	if (colData_.hitFlg_)
	{
		for (int checkNum = 0; checkNum < COL_CHECK_MAX; checkNum++)
		{
			//当たっていたのがボスの時
			if (colData_.list_[checkNum] == COL_CHECK_BOSS && !checkFlg[COL_CHECK_BOSS])
			{
				CBoss* boss = CEnemyManager::GetInstance()->GetBoss();
				CItemManager* itemManager = CItemManager::GetInstance();
				//ボスが対応できる場合
				if (boss->GetCounterFlg())
				{
					boss->SetBossAIFlg(true);
					itemManager->SetBossItemInfo(itemNum_);
					
				}
				else
				{
					//アイテムを消して、そのアイテムのダメージをボスに与える
					itemManager->DamageVanish(itemNum_);
				}
				//当たり判定関係更新
				CCollisionManager::GetInstance()->SetUpdateColInfo(colNum_, OBJECT_DYNAMIC);
				checkFlg[COL_CHECK_BOSS] = true;
			}
		}
	}
}

void CEraser::Draw()
{
	
	//モデルの回転
	MV1SetRotationXYZ(hndl_, rot_);
	//モデルの位置座標セット
	MV1SetPosition(hndl_, pos_);
	MV1SetScale(hndl_, scale_);
	//モデル描画
	MV1DrawModel(hndl_);
}

void CEraser::Fin()
{
	DeleteModel();
}

