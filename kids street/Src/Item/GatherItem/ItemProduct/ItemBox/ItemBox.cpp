//ItemBox.cpp

#include "ItemBox.h"
#include "DxLib.h"
#include "../../GatherFactory/GatherManager.h"
#include "../../../ItemCommon.h"
#include "../../../../UI/GameUIManager.h"
#include "../../GatherFactory/GatherBase/GatherItem.h"

namespace
{
	
}

//‰Šú‰»
void CItemBox::Init()
{
	//UIŠÇ—
	CGameUIManager* uiManager = CGameUIManager::GetInstance();
	
	CGameUI* uiEraser = uiManager->CreateUI(CGameUIManager::UI_TYPE_BUTTON);
	uiEraser->Init(ITEM_UI_ERASER, ITEM_UI_Y);
	uiEraser->Load("Data/UI/ItemBox/ItemBoxFrame.png");

	
	CGameUI* uiPencil = uiManager->CreateUI(CGameUIManager::UI_TYPE_BUTTON);
	uiPencil->Init(ITEM_UI_PENCIL, ITEM_UI_Y);
	uiPencil->Load("Data/UI/ItemBox/ItemBoxFrame.png");

	CGameUI* uiRuler = uiManager->CreateUI(CGameUIManager::UI_TYPE_BUTTON);
	uiRuler->Init(ITEM_UI_RULER, ITEM_UI_Y);
	uiRuler->Load("Data/UI/ItemBox/ItemBoxFrame.png");

	CGameUI* uiGlove = uiManager->CreateUI(CGameUIManager::UI_TYPE_BUTTON);
	uiGlove->Init(ITEM_UI_GLOVE, ITEM_UI_Y);
	uiGlove->Load("Data/UI/ItemBox/ItemBoxFrame.png");
}
