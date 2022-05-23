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

//������
void CGatherEraser::Init()
{
	//�A�C�e���Ǘ�����
	CGatherManager* gatherManager = CGatherManager::GetInstance();
	//�t�B�[���h��ɃA�C�e���𐶐�
	CGatherItem* gatherEraser = gatherManager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
	gatherEraser->Init(ERASER_POS);
	gatherEraser->Load("Data/Item/BunishGom.x");

	//UI�Ǘ�
	CGameUIManager* uiManager = CGameUIManager::GetInstance();

	//UI�Ƃ��Ă̏����S������
	CGameUI* uiEraser = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEM);
	uiEraser->Init(ITEM_UI_ERASER, ITEM_UI_Y);
	uiEraser->Load("Data/UI/ItemBox/EraserUI.png");

	//���̃A�C�e�����I�΂�Ă���ۂɋ����\������UI����
	CGameUI* uiEraserBox = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEMBOX);
	uiEraserBox->Init(ITEM_UI_ERASER, ITEM_UI_Y);
	uiEraserBox->Load("Data/UI/ItemBox/ItemBoxPoint.png");
}


//���t���[���Ăԏ���
void CGatherEraser::Step()
{
	Gather();
}




//�A�C�e�����W�X�V
void CGatherEraser::Gather()
{
	//�v���C���[���A�C�e���ɒ�߂����͈͓���ʂ����Ƃ��Ɋl���ł���悤�ɂ���
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, ERASER_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, ERASER_POS.z))
	{
		//�G���A���ɂ���Ȃ�t���O�𗧂Ă�
		CGatherManager::GetInstance()->GatherItem(ERASER);
	}

}