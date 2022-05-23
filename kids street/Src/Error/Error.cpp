

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
		//0より小さい又は現在決められている最大値以上に大きい場合はエラー
		assert(0 > car->GetInterInfo().check_ || INTER_DIR_NUM <= car->GetInterInfo().check_ ||
			0 > car->GetInterInfo().just_ || INTER_DIR_NUM <= car->GetInterInfo().just_);
	}
}

void CError::PlayerError()
{

}

void CError::VoidError()
{
	//ここを通った時点で確実にエラー
	assert(true);
}