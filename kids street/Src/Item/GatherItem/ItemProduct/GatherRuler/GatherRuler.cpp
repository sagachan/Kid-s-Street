//GatherRuler.cpp

#include "GatherRuler.h"
#include "DxLib.h"
#include "../../GatherFactory/GatherManager.h"
#include "../../../ItemCommon.h"
#include "../../../../Player/PlayerManager.h"
#include "../../../../Library/MyMath/MyMath.h"
#include "../../GatherFactory/GatherBase/GatherItem.h"

namespace
{
	
}

//初期化
void CGatherRuler::Init()
{
	//アイテム管理生成
	CGatherManager* ui_manager = CGatherManager::GetInstance();
	//フィールド上にアイテムを生成
	CGatherItem* GatherRuler = ui_manager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
	GatherRuler->Init(RULER_POS);
	GatherRuler->Load("Data/Item/Ruler.x");

	//UI管理
	CGameUIManager* uiManager = CGameUIManager::GetInstance();

	//UIとしての生成
	CGameUI* uiPencil = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEM);
	uiPencil->Init(ITEM_UI_RULER, ITEM_UI_Y);
	uiPencil->Load("Data/UI/ItemBox/RulerUI.png");

	//このアイテムが選ばれている際に強調表示するUI生成
	CGameUI* uiPencilBox = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEMBOX);
	uiPencilBox->Init(ITEM_UI_RULER, ITEM_UI_Y);
	uiPencilBox->Load("Data/UI/ItemBox/ItemBoxPoint.png");
}

//毎フレーム呼ぶ処理
void CGatherRuler::Step()
{
	Gather();
}

//アイテム収集更新
void CGatherRuler::Gather()
{
	//プレイヤーがアイテムに定めた一定範囲内を通ったときに獲得できるようにする
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, RULER_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, RULER_POS.z))
	{
		//エリア内にいるならフラグを立てる
		CGatherManager::GetInstance()->GatherItem(RULER);
	}
}