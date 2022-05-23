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
	CCollisionManager();	//�R���X�g���N�^
	~CCollisionManager();	//�f�X�g���N�^

public:
	//�C���X�^���X����
	static void CreateInstance() { if (!instance_) instance_ = new CCollisionManager; }
	//�C���X�^���X�擾
	static CCollisionManager* GetInstance() { return instance_; }
	//�C���X�^���X�폜
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();
	//�X�e�b�v
	void Step();
	//�폜
	void Delete();
	//�㏈��
	void Fin();
	
public:
	void BossHit();											//�{�X�̑̂ɐG��Ă��邩�̏���
	void BossItemHit(VECTOR pos, float rad);				//�{�X�������Ԃ��Ă����A�C�e���̓����蔻��X�V
	void ChaseHit();										//�ǂ������Ă���{�X�̓����蔻��X�V

public:
	//�{�X�̓����蔻��X�V�A�����͈ʒu�������������i�[�����z��̃|�C���^�A
	//�����蔻��{�b�N�X�̈�ӂ̒����A�{�[���̍ő�l
	void SetBossCollision(VECTOR framePos[FRAME_MAX], float rad);
	//�A�C�e���̓����蔻��X�V�A�����͈ʒu�������������i�[�����z��̃|�C���^
	void SetItemCollision(ITEM_DATA* itemData);
	
	//�Ǘ����Ă���N���X�̃A�h���X���i�[
	CCollision* GetCollision() { return &collision_; }


private:
	static CCollisionManager*	instance_;					//�C���X�^���X
	CCollision					collision_;
	CollisionData				bossData_[FRAME_MAX];
	ITEM_DATA					itemData_[MAX_ITEM_NUM];
};