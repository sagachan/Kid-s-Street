//GatherPencil.cpp

#include "GatherPencil.h"
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
void CGatherPencil::Init()
{
	//アイテム管理生成
	CGatherManager* ui_manager = CGatherManager::GetInstance();
	//フィールド上にアイテムを生成
	CGatherItem* gatherPencil = ui_manager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
	gatherPencil->Init(PENCIL_POS);
	gatherPencil->Load("Data/Item/Enpitu.x");

	//UI管理
	CGameUIManager* uiManager = CGameUIManager::GetInstance();

	//UIとしての鉛筆生成
	CGameUI* uiPencil = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEM);
	uiPencil->Init(ITEM_UI_PENCIL, ITEM_UI_Y);
	uiPencil->Load("Data/UI/ItemBox/PencilUI.png");

	//このアイテムが選ばれている際に強調表示するUI生成
	CGameUI* uiPencilBox = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEMBOX);
	uiPencilBox->Init(ITEM_UI_PENCIL, ITEM_UI_Y);
	uiPencilBox->Load("Data/UI/ItemBox/ItemBoxPoint.png");
}

//毎フレーム呼ぶ処理
void CGatherPencil::Step()
{
	Gather();
}

//アイテム収集更新
void CGatherPencil::Gather()
{
	//プレイヤーがアイテムに定めた一定範囲内を通ったときに獲得できるようにする
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, PENCIL_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, PENCIL_POS.z))
	{
		//エリア内にいるならフラグを立てる
		CGatherManager::GetInstance()->GatherItem(PENCIL);
	}
}