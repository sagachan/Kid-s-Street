#pragma once

#include "../Library/Collision/Collision.h"
#include "../Enemy/EnemyManager.h"
#include "../Item/UseItem/ItemManager.h"
#include "DxLib.h"
#include "../Item/ItemCommon.h"
#include "../Enemy/EnemyCommon.h"
#include "../AI/BossAI/AIAttackBoss.h"
#include "../AI/AIBase.h"



class CCollisionManager
{
public:
	struct CollisionData
	{
		VECTOR pos_;
		float rad_;
	};

	struct ITEM_DATA
	{
		VECTOR pos_;
		float rad_;
		bool useflg_;
	};

	enum COLLISION_TYPE
	{
		INIT,
		ALLHIT,
		THROUGH,
		PAWN,
		STATIC,
		DYNAMIC
	};

	enum COLLISION_KIND
	{
		PLAYER,
		ITEM,
		ENEMY,
		BOSS
	};

public:
	CCollisionManager();	//コンストラクタ
	~CCollisionManager();	//デストラクタ

public:
	//インスタンス生成
	static void CreateInstance() { if (!instance_) instance_ = new CCollisionManager; }
	//インスタンス取得
	static CCollisionManager* GetInstance() { return instance_; }
	//インスタンス削除
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();
	//ステップ
	void Step();
	//削除
	void Delete();
	//後処理
	void Fin();
	
public:
	void BossHit();											//ボスの体に触れているかの処理
	void BossItemHit(VECTOR pos, float rad);				//ボスが投げ返してきたアイテムの当たり判定更新
	void ChaseHit();										//追いかけてくるボスの当たり判定更新

public:
	//ボスの当たり判定更新、引数は位置情報を個数分だけ格納した配列のポインタ、
	//当たり判定ボックスの一辺の長さ、ボーンの最大値
	void SetBossCollision(VECTOR framePos[FRAME_MAX], float rad);
	//アイテムの当たり判定更新、引数は位置情報を個数分だけ格納した配列のポインタ
	void SetItemCollision(ITEM_DATA* itemData);
	
	//管理しているクラスのアドレスを格納
	CCollision* GetCollision() { return &collision_; }


private:
	static CCollisionManager*	instance_;					//インスタンス
	CCollision					collision_;
	CollisionData				bossData_[FRAME_MAX];
	ITEM_DATA					itemData_[MAX_ITEM_NUM];
};