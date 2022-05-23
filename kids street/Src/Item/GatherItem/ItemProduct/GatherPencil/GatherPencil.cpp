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

//������
void CGatherPencil::Init()
{
	//�A�C�e���Ǘ�����
	CGatherManager* ui_manager = CGatherManager::GetInstance();
	//�t�B�[���h��ɃA�C�e���𐶐�
	CGatherItem* gatherPencil = ui_manager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
	gatherPencil->Init(PENCIL_POS);
	gatherPencil->Load("Data/Item/Enpitu.x");

	//UI�Ǘ�
	CGameUIManager* uiManager = CGameUIManager::GetInstance();

	//UI�Ƃ��Ẳ��M����
	CGameUI* uiPencil = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEM);
	uiPencil->Init(ITEM_UI_PENCIL, ITEM_UI_Y);
	uiPencil->Load("Data/UI/ItemBox/PencilUI.png");

	//���̃A�C�e�����I�΂�Ă���ۂɋ����\������UI����
	CGameUI* uiPencilBox = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEMBOX);
	uiPencilBox->Init(ITEM_UI_PENCIL, ITEM_UI_Y);
	uiPencilBox->Load("Data/UI/ItemBox/ItemBoxPoint.png");
}

//���t���[���Ăԏ���
void CGatherPencil::Step()
{
	Gather();
}

//�A�C�e�����W�X�V
void CGatherPencil::Gather()
{
	//�v���C���[���A�C�e���ɒ�߂����͈͓���ʂ����Ƃ��Ɋl���ł���悤�ɂ���
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, PENCIL_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, PENCIL_POS.z))
	{
		//�G���A���ɂ���Ȃ�t���O�𗧂Ă�
		CGatherManager::GetInstance()->GatherItem(PENCIL);
	}
}