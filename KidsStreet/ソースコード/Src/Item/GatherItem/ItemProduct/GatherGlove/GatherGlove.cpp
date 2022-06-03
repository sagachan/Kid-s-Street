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

//������
void CGatherGlove::Init()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	kind_ = GLOVE;

	//���łɊl������Ă���Ȃ琶�����Ȃ�
	if (!uiFlg[GLOVE]) {
		//�A�C�e���Ǘ�����
		CGatherManager* gatherManager = CGatherManager::GetInstance();
		//�t�B�[���h��ɃA�C�e���𐶐�
		CGatherItem* gatherGlove = gatherManager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
		gatherGlove->Init(GLOVE_POS);
		gatherGlove->Load("Data/Item/glove.x");
		//�A�C�e�����\������
		uiProperty_[PROPERTY_OPEN] = CGameUIManager::GetInstance()->CreateUI(CGameUIManager::UI_TYPE_ASSERT);
		uiProperty_[PROPERTY_OPEN]->Init(ITEM_PROPERTY_POS.x, ITEM_PROPERTY_POS.y);
		uiProperty_[PROPERTY_OPEN]->Load("Data/UI/ItemProperty/GlovePro.png");
	}

	//UI�Ǘ�
	CGameUIManager* uiManager = CGameUIManager::GetInstance();

	//UI�Ƃ��Ă̐���
	CGameUI* uiGlove = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEM);
	uiGlove->Init(ITEM_UI_GLOVE, ITEM_UI_Y);
	uiGlove->Load("Data/UI/ItemBox/GloveUI.png");

	//���̃A�C�e�����I�΂�Ă���ۂɋ����\������UI����
	CGameUI* uiGloveBox = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEMBOX);
	uiGloveBox->Init(ITEM_UI_GLOVE, ITEM_UI_Y);
	uiGloveBox->Load("Data/UI/ItemBox/ItemBoxPoint.png");

	//���łɊl������Ă���Ȃ�t���O�𗧂ĂĂ���
	if (uiFlg[GLOVE]) {
		uiGlove->SetDrawFlg(false);
	}
}


//���t���[���Ăԏ���
void CGatherGlove::Step()
{
	//�W�߂��Ă��Ȃ��Ȃ�
	if (!endFlg_)
		Gather();
}




//�A�C�e�����W�X�V
void CGatherGlove::Gather()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	//���łɊl������Ă���Ȃ�ʂ�Ȃ�
	if (uiFlg[GLOVE]) { return; }

	//�v���C���[���A�C�e���ɒ�߂����͈͓���ʂ����Ƃ��Ɋl���ł���悤�ɂ���
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, GLOVE_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, GLOVE_POS.z))
	{
		//�G���A���ɂ���Ȃ�t���O�𗧂Ă�
		CGatherManager::GetInstance()->GatherItem(GLOVE);
		CSound::PlaySE(CSound::SE_GET);
		//�����I���t���O�����Ă�
		endFlg_ = true;
		propertyFlg_ = true;
	}
}

