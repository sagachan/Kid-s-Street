
#include "EnemyBase.h"
#include "../Library/MyMath/MyMath.h"

CEnemyBase::CEnemyBase()
{
	ai_state_ = 0;
	hp_ = 0;
	forward_ = { 0 };
	dmg_ = 0;
	colFlg_ = false;
	move_ = 0.0f;
	findFlg_ = false;
}

CEnemyBase::~CEnemyBase()
{

}