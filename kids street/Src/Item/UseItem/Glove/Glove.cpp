//Glove.cpp

#include "../../../Library/MyMath/MyMath.h"
#include "../ItemManager.h"
#include "../../../Enemy/EnemyBase.h"
#include "Glove.h"

namespace
{
	const float SIMPLE_HIT_RADIUS = 4.0;			//ŠÈˆÕ“–‚½‚è”»’è—p
	const int DMG = 15;
	
}

void CGlove::Load()
{
	id_ = ITEM_ID_GLOVE;
}


void CGlove::Set()
{
	rad_ = SIMPLE_HIT_RADIUS;
}
