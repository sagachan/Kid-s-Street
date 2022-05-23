#ifndef __AI_BASE_H__
#define __AI_BASE_H__

#include "../Enemy/EnemyBase.h"
#include "../Library/Animation/Animation.h"

class AIBase : public CAnim3D
{
public:
	enum BOSS_AIState
	{
		BOSS_APPEAR,
		BOSS_STAND,
		BOSS_TARGET,
		BOSS_MOTION_ATTACK,
		BOSS_NORMAL_ATTACK,
		BOSS_RARE_ATTACK,
		BOSS_CATCH,
		BOSS_THROW,
		BOSS_RAGE

	};

	enum CHASE_AIState
	{
		CHASE_APPEAR,
		CHASE_FINISHER,
		CHASE_PUNCH,
		CHASE_ROLL,
		CHASE_RUN,
		CHASE_WALK
	};

	enum KID_AIState
	{
		KID_WALK,
		KID_BIND
	};

public:
	AIBase();
	virtual ~AIBase();

	
public:
	virtual int GetNextState(CEnemyBase* enemy) = 0;

public:
	bool		findFlg_;		//ÉvÉåÉCÉÑÅ[Çå©Ç¬ÇØÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©

};

#endif
