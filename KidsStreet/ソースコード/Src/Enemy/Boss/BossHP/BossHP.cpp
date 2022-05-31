//BossHP.cpp

#include "BossHP.h"
#include "DxLib.h"
#include "../../../UI/GameUIManager.h"
#include "../../EnemyManager.h"
#include "../../EnemyCommon.h"


namespace
{
	const float UI_posX = 10.0f;
	const float UI_posY = 25.0f;
}


CBossHP::CBossHP()
{
	Init();
}

CBossHP::~CBossHP()
{

}

//‰Šú‰»
void CBossHP::Init()
{
	//UIŠÇ—¶¬
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//”wŒi¶¬
	hp_ = ui_manager->CreateUI(CGameUIManager::UI_TYPE_HP);
	hp_->Init(BOSS_HP_POS.x, BOSS_HP_POS.y);
	hp_->Load("Data/UI/HP/BossHP.png");
	hp_->SetEndPos(BOSS_HP_END_POS);
}

//“Ç‚Ýž‚Ý
void CBossHP::Load()
{

}

//Še•Ï”‚È‚Ç‚É‰Šú’l‚ðÝ’èiƒZƒbƒgj
void CBossHP::Set()
{
	
}

//–ˆƒtƒŒ[ƒ€ŒÄ‚Ôˆ—
void CBossHP::Step()
{
	//–ˆTHP‚ðUI‚É“n‚·
	CBoss* boss = CEnemyManager::GetInstance()->GetBoss();
	hp_->SetSize(boss->GetHP());
}


//•`‰æ
void CBossHP::Draw()
{
	
}


//Œãˆ—
void CBossHP::Fin()
{
	//UIŠÇ—Œãˆ—
	CGameUIManager::GetInstance()->DeleteAll();
}