//GatherGlove.cpp

#include "GatherGlove.h"
#include "DxLib.h"
#include "../../GatherFactory/GatherManager.h"
#include "../../../ItemCommon.h"
#include "../../../../Player/PlayerManager.h"
#include "../../../../Library/MyMath/MyMath.h"
#include "../../GatherFactory/GatherBase/GatherItem.h"
#include "../../../../UI/GameUIManager.h"
#include "../../../../Library/Sound/Sound.h"

namespace
{
	
}

//初期化
void CGatherGlove::Init()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	kind_ = GLOVE;

	//すでに獲得されているなら生成しない
	if (!uiFlg[GLOVE]) {
		//アイテム管理生成
		CGatherManager* gatherManager = CGatherManager::GetInstance();
		//フィールド上にアイテムを生成
		CGatherItem* gatherGlove = gatherManager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
		gatherGlove->Init(GLOVE_POS);
		gatherGlove->Load("Data/Item/glove.x");
		//アイテム情報表示生成
		uiProperty_[PROPERTY_OPEN] = CGameUIManager::GetInstance()->CreateUI(CGameUIManager::UI_TYPE_ASSERT);
		uiProperty_[PROPERTY_OPEN]->Init(ITEM_PROPERTY_POS.x, ITEM_PROPERTY_POS.y);
		uiProperty_[PROPERTY_OPEN]->Load("Data/UI/ItemProperty/GlovePro.png");
	}

	//UI管理
	CGameUIManager* uiManager = CGameUIManager::GetInstance();

	//UIとしての生成
	CGameUI* uiGlove = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEM);
	uiGlove->Init(ITEM_UI_GLOVE, ITEM_UI_Y);
	uiGlove->Load("Data/UI/ItemBox/GloveUI.png");

	//このアイテムが選ばれている際に強調表示するUI生成
	CGameUI* uiGloveBox = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEMBOX);
	uiGloveBox->Init(ITEM_UI_GLOVE, ITEM_UI_Y);
	uiGloveBox->Load("Data/UI/ItemBox/ItemBoxPoint.png");

	//すでに獲得されているならフラグを立てておく
	if (uiFlg[GLOVE]) {
		uiGlove->SetDrawFlg(false);
	}
}


//毎フレーム呼ぶ処理
void CGatherGlove::Step()
{
	//集められていないなら
	if (!endFlg_)
		Gather();
}




//アイテム収集更新
void CGatherGlove::Gather()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	//すでに獲得されているなら通らない
	if (uiFlg[GLOVE]) { return; }

	//プレイヤーがアイテムに定めた一定範囲内を通ったときに獲得できるようにする
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, GLOVE_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, GLOVE_POS.z))
	{
		//エリア内にいるならフラグを立てる
		CGatherManager::GetInstance()->GatherItem(GLOVE);
		CSound::PlaySE(CSound::SE_GET);
		//処理終了フラグをたてる
		endFlg_ = true;
		propertyFlg_ = true;
	}
}

