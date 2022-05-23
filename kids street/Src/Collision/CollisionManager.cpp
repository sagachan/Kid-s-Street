
#include "../Player/PlayerManager.h"
#include "CollisionManager.h"
#include "../Library/MyMath/MyMath.h"
#include "../Player/PlayerCommon.h"
#include "../Enemy/EnemyCommon.h"
#include "ColField/ColField.h"

//CEnemyManagerの実体宣言、初期化
CCollisionManager* CCollisionManager::instance_ = nullptr;


CCollisionManager::CCollisionManager()
{
	//自動で呼ばれる
	Init();
}

CCollisionManager::~CCollisionManager()
{
	//自動で呼ばれる
	Delete();
}

void CCollisionManager::Init()
{
	
}

void CCollisionManager::Step()
{
	//当たり判定情報を取得
	//（この関数内で引数を渡したsetcollision関数を呼んでいる
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();
	enemyManager->GetBoss()->Hit();
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		enemyManager->GetEnemy(carNum)->CheckColCube();
	}
	CItemManager::GetInstance()->HitUpdate();
	BossHit();

	//マップとの当たり判定関係更新
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

//ボスに関する当たり判定 (別クラスに分ける
void CCollisionManager::BossHit()
{
	//プレイヤーの情報取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR player_pos = player->GetPosition();
	CItemManager* itemManager = CItemManager::GetInstance();
	CBoss* boss = CEnemyManager::GetInstance()->GetBoss();

	//ここではボスのボーンと---を比べる処理
	//ボスのボーンの数だけループする参照処理
	for (int frame_num = 0; frame_num < FRAME_MAX; frame_num++){
		//アイテムの数だけチェックする
		for (int item_num = 0; item_num < MAX_ITEM_NUM; item_num++){
			//現在使用されているものしかチェックしなくてもいい
			if (itemData_[item_num].useflg_){
				//当たり判定確認
				//アイテム
				if (CCollision::IsHitRect(bossData_[frame_num].pos_, bossData_[frame_num].rad_, bossData_[frame_num].rad_, bossData_[frame_num].rad_,
					itemData_[item_num].pos_, itemData_[item_num].rad_, itemData_[item_num].rad_, itemData_[item_num].rad_))
				{
					//当たり判定処理が発生しているならここを通る
					//ボスが対応できる場合
					if (boss->GetCounterFlg())
					{
						//ボスAIのカウンターフラグをtrueに
						boss->SetBossAIFlg(true);
						//触れたアイテムのボス取得フラグをtrueにする関数を呼ぶ
						itemManager->SetBossItemInfo(item_num);
					}
					else if (!boss->GetCounterFlg())
					{
						//アイテムを消して、そのアイテムのダメージをボスに与える
						itemManager->DamageVanish(item_num);
					}
				}
			}
		}

		//プレイヤー
		if (CCollision::IsHitRect(bossData_[frame_num].pos_, bossData_[frame_num].rad_, bossData_[frame_num].rad_, bossData_[frame_num].rad_,
			player_pos, PLAYER_COL.x, PLAYER_COL.y, PLAYER_COL.z) == true)
		{
			//当たった時に起きる処理
			CPlayerManager::GetInstance()->GetPlayer()->AddDamage(1);
		}
	}
	
}

//アイテムがボスによって投げられているときに通る当たり判定処理
void CCollisionManager::BossItemHit(VECTOR pos, float rad)
{
	//プレイヤーの情報取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR player_pos = player->GetPosition();
	VECTOR PLAYER_COL = player->GetSize();

	//プレイヤー
	if (CCollision::IsHitRect(pos, rad, rad, rad,
		player_pos, PLAYER_COL.x, PLAYER_COL.y, PLAYER_COL.z))
	{
		//当たった時に起きる処理
		player->AddDamage(ERASER_DMG);
	}
}

void CCollisionManager::ChaseHit()
{
	//ここでチェイスボスの位置情報と簡易半径を受け取り、判定を開始する
	//上のボスの当たり判定とは違い、簡易判定にすることで難易度を上げ
	//プレイヤーに緊張感を持たせる
	//簡易半径判定はエネミーを中心として四角いキューブをイメージして作るため正方形の当たり判定を使用可能


}

