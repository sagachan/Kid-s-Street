//GatherPencil.cpp

#include "GatherPencil.h"
#include "DxLib.h"
#include "../../GatherFactory/GatherManager.h"
#include "../../../ItemCommon.h"
#include "../../../../Player/PlayerManager.h"
#include "../../../../Library/MyMath/MyMath.h"
#include "../../GatherFactory/GatherBase/GatherItem.h"
#include "../../../../Library/Sound/Sound.h"

namespace
{
	
}

//初期化
void CGatherPencil::Init()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	kind_ = PENCIL;

	//すでに獲得されているなら生成しない
	if (!uiFlg[PENCIL]) {
		//アイテム管理生成
		CGatherManager* ui_manager = CGatherManager::GetInstance();
		//フィールド上にアイテムを生成
		CGatherItem* gatherPencil = ui_manager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
		gatherPencil->Init(PENCIL_POS);
		gatherPencil->Load("Data/Item/Enpitu.x");
		//アイテム情報表示生成
		uiProperty_[PROPERTY_OPEN] = CGameUIManager::GetInstance()->CreateUI(CGameUIManager::UI_TYPE_ASSERT);
		uiProperty_[PROPERTY_OPEN]->Init(ITEM_PROPERTY_POS.x, ITEM_PROPERTY_POS.y);
		uiProperty_[PROPERTY_OPEN]->Load("Data/UI/ItemProperty/PencilPro.png");
	}

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

	//すでに獲得されているならフラグを立てておく
	if (uiFlg[PENCIL]) {
		uiPencil->SetDrawFlg(false);
	}
}

//毎フレーム呼ぶ処理
void CGatherPencil::Step()
{
	//集められていないなら
	if (!endFlg_)
		Gather();

	PropertyWindow();
}

//アイテム収集更新
void CGatherPencil::Gather()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	//すでに獲得されているなら通らない
	if (uiFlg[PENCIL]) { return; }

	//プレイヤーがアイテムに定めた一定範囲内を通ったときに獲得できるようにする
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, PENCIL_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, PENCIL_POS.z))
	{
		//エリア内にいるならフラグを立てる
		CGatherManager::GetInstance()->GatherItem(PENCIL);
		CSound::PlaySE(CSound::SE_GET);
		//処理終了フラグをたてる
		endFlg_ = true;
		propertyFlg_ = true;
	}
}