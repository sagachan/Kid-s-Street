//GatherRuler.cpp

#include "GatherRuler.h"
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
void CGatherRuler::Init()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	kind_ = RULER;

	//すでに獲得されているなら生成しない
	if (!uiFlg[RULER]) {
		//アイテム管理生成
		CGatherManager* ui_manager = CGatherManager::GetInstance();
		//フィールド上にアイテムを生成
		CGatherItem* GatherRuler = ui_manager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
		GatherRuler->Init(RULER_POS);
		GatherRuler->Load("Data/Item/Ruler.x");
		//アイテム情報表示生成
		uiProperty_[PROPERTY_OPEN] = CGameUIManager::GetInstance()->CreateUI(CGameUIManager::UI_TYPE_ASSERT);
		uiProperty_[PROPERTY_OPEN]->Init(ITEM_PROPERTY_POS.x, ITEM_PROPERTY_POS.y);
		uiProperty_[PROPERTY_OPEN]->Load("Data/UI/ItemProperty/RulerPro.png");
	}

	//UI管理
	CGameUIManager* uiManager = CGameUIManager::GetInstance();

	//UIとしての生成
	CGameUI* uiRuler = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEM);
	uiRuler->Init(ITEM_UI_RULER, ITEM_UI_Y);
	uiRuler->Load("Data/UI/ItemBox/RulerUI.png");

	//このアイテムが選ばれている際に強調表示するUI生成
	CGameUI* uiRulerBox = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEMBOX);
	uiRulerBox->Init(ITEM_UI_RULER, ITEM_UI_Y);
	uiRulerBox->Load("Data/UI/ItemBox/ItemBoxPoint.png");

	//すでに獲得されているならフラグを立てておく
	if (uiFlg[RULER]) {
		uiRuler->SetDrawFlg(false);
	}
}

//毎フレーム呼ぶ処理
void CGatherRuler::Step()
{
	//集められていないなら
	if (!endFlg_)
		Gather();

	PropertyWindow();
}

//アイテム収集更新
void CGatherRuler::Gather()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	//すでに獲得されているなら通らない
	if (uiFlg[RULER]) { return; }

	//プレイヤーがアイテムに定めた一定範囲内を通ったときに獲得できるようにする
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, RULER_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, RULER_POS.z))
	{
		//エリア内にいるならフラグを立てる
		CGatherManager::GetInstance()->GatherItem(RULER);
		CSound::PlaySE(CSound::SE_GET);
		//処理終了フラグをたてる
		endFlg_ = true;
		propertyFlg_ = true;
	}
}