//GatherEraser.cpp

#include "GatherEraser.h"
#include "DxLib.h"
#include "../../GatherFactory/GatherManager.h"
#include "../../../ItemCommon.h"
#include "../../../../Player/PlayerManager.h"
#include "../../../../Library/MyMath/MyMath.h"
#include "../../GatherFactory/GatherBase/GatherItem.h"
#include "../../../../UI/GameUIManager.h"

namespace
{
	
}

//初期化
void CGatherEraser::Init()
{
	//アイテム管理生成
	CGatherManager* gatherManager = CGatherManager::GetInstance();
	//フィールド上にアイテムを生成
	CGatherItem* gatherEraser = gatherManager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
	gatherEraser->Init(ERASER_POS);
	gatherEraser->Load("Data/Item/BunishGom.x");

	//UI管理
	CGameUIManager* uiManager = CGameUIManager::GetInstance();

	//UIとしての消しゴム生成
	CGameUI* uiEraser = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEM);
	uiEraser->Init(ITEM_UI_ERASER, ITEM_UI_Y);
	uiEraser->Load("Data/UI/ItemBox/EraserUI.png");

	//このアイテムが選ばれている際に強調表示するUI生成
	CGameUI* uiEraserBox = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEMBOX);
	uiEraserBox->Init(ITEM_UI_ERASER, ITEM_UI_Y);
	uiEraserBox->Load("Data/UI/ItemBox/ItemBoxPoint.png");
}


//毎フレーム呼ぶ処理
void CGatherEraser::Step()
{
	Gather();
}




//アイテム収集更新
void CGatherEraser::Gather()
{
	//プレイヤーがアイテムに定めた一定範囲内を通ったときに獲得できるようにする
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, ERASER_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, ERASER_POS.z))
	{
		//エリア内にいるならフラグを立てる
		CGatherManager::GetInstance()->GatherItem(ERASER);
	}

}