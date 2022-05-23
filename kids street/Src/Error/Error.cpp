

#include "Error.h"
#include <cassert>
#include "../Enemy/EnemyManager.h"
#include "../Enemy/EnemyCommon.h"
#include "../Field/FieldCommon.h"

void CError::ErrorManager()
{
	EnemyError();
}


void CError::EnemyError()
{
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();
	
	
	for (int enemyNum = 0; enemyNum < APPEAR_CAR_NUM; enemyNum++)
	{
		CEnemy* car = enemyManager->GetEnemy(enemyNum);
		//0��菬�������͌��݌��߂��Ă���ő�l�ȏ�ɑ傫���ꍇ�̓G���[
		assert(0 > car->GetInterInfo().check_ || INTER_DIR_NUM <= car->GetInterInfo().check_ ||
			0 > car->GetInterInfo().just_ || INTER_DIR_NUM <= car->GetInterInfo().just_);
	}
}

void CError::PlayerError()
{

}

void CError::VoidError()
{
	//������ʂ������_�Ŋm���ɃG���[
	assert(true);
}