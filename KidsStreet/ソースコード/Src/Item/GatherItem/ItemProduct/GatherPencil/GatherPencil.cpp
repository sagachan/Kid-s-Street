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

//������
void CGatherPencil::Init()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	kind_ = PENCIL;

	//���łɊl������Ă���Ȃ琶�����Ȃ�
	if (!uiFlg[PENCIL]) {
		//�A�C�e���Ǘ�����
		CGatherManager* ui_manager = CGatherManager::GetInstance();
		//�t�B�[���h��ɃA�C�e���𐶐�
		CGatherItem* gatherPencil = ui_manager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
		gatherPencil->Init(PENCIL_POS);
		gatherPencil->Load("Data/Item/Enpitu.x");
		//�A�C�e�����\������
		uiProperty_[PROPERTY_OPEN] = CGameUIManager::GetInstance()->CreateUI(CGameUIManager::UI_TYPE_ASSERT);
		uiProperty_[PROPERTY_OPEN]->Init(ITEM_PROPERTY_POS.x, ITEM_PROPERTY_POS.y);
		uiProperty_[PROPERTY_OPEN]->Load("Data/UI/ItemProperty/PencilPro.png");
	}

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

	//���łɊl������Ă���Ȃ�t���O�𗧂ĂĂ���
	if (uiFlg[PENCIL]) {
		uiPencil->SetDrawFlg(false);
	}
}

//���t���[���Ăԏ���
void CGatherPencil::Step()
{
	//�W�߂��Ă��Ȃ��Ȃ�
	if (!endFlg_)
		Gather();

	PropertyWindow();
}

//�A�C�e�����W�X�V
void CGatherPencil::Gather()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	//���łɊl������Ă���Ȃ�ʂ�Ȃ�
	if (uiFlg[PENCIL]) { return; }

	//�v���C���[���A�C�e���ɒ�߂����͈͓���ʂ����Ƃ��Ɋl���ł���悤�ɂ���
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, PENCIL_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, PENCIL_POS.z))
	{
		//�G���A���ɂ���Ȃ�t���O�𗧂Ă�
		CGatherManager::GetInstance()->GatherItem(PENCIL);
		CSound::PlaySE(CSound::SE_GET);
		//�����I���t���O�����Ă�
		endFlg_ = true;
		propertyFlg_ = true;
	}
}