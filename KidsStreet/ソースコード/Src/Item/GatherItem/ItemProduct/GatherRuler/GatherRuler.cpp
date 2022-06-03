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

//������
void CGatherRuler::Init()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	kind_ = RULER;

	//���łɊl������Ă���Ȃ琶�����Ȃ�
	if (!uiFlg[RULER]) {
		//�A�C�e���Ǘ�����
		CGatherManager* ui_manager = CGatherManager::GetInstance();
		//�t�B�[���h��ɃA�C�e���𐶐�
		CGatherItem* GatherRuler = ui_manager->CreateItem(CGatherManager::BOSS_ONLY_ITEM);
		GatherRuler->Init(RULER_POS);
		GatherRuler->Load("Data/Item/Ruler.x");
		//�A�C�e�����\������
		uiProperty_[PROPERTY_OPEN] = CGameUIManager::GetInstance()->CreateUI(CGameUIManager::UI_TYPE_ASSERT);
		uiProperty_[PROPERTY_OPEN]->Init(ITEM_PROPERTY_POS.x, ITEM_PROPERTY_POS.y);
		uiProperty_[PROPERTY_OPEN]->Load("Data/UI/ItemProperty/RulerPro.png");
	}

	//UI�Ǘ�
	CGameUIManager* uiManager = CGameUIManager::GetInstance();

	//UI�Ƃ��Ă̐���
	CGameUI* uiRuler = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEM);
	uiRuler->Init(ITEM_UI_RULER, ITEM_UI_Y);
	uiRuler->Load("Data/UI/ItemBox/RulerUI.png");

	//���̃A�C�e�����I�΂�Ă���ۂɋ����\������UI����
	CGameUI* uiRulerBox = uiManager->CreateUI(CGameUIManager::UI_TYPE_ITEMBOX);
	uiRulerBox->Init(ITEM_UI_RULER, ITEM_UI_Y);
	uiRulerBox->Load("Data/UI/ItemBox/ItemBoxPoint.png");

	//���łɊl������Ă���Ȃ�t���O�𗧂ĂĂ���
	if (uiFlg[RULER]) {
		uiRuler->SetDrawFlg(false);
	}
}

//���t���[���Ăԏ���
void CGatherRuler::Step()
{
	//�W�߂��Ă��Ȃ��Ȃ�
	if (!endFlg_)
		Gather();

	PropertyWindow();
}

//�A�C�e�����W�X�V
void CGatherRuler::Gather()
{
	bool* uiFlg = CGatherManager::GetInstance()->GetGatherItem();
	//���łɊl������Ă���Ȃ�ʂ�Ȃ�
	if (uiFlg[RULER]) { return; }

	//�v���C���[���A�C�e���ɒ�߂����͈͓���ʂ����Ƃ��Ɋl���ł���悤�ɂ���
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (CMyMath::RadiusCheck(playerPos.x, ITEM_GATHER_AREA, RULER_POS.x) &&
		CMyMath::RadiusCheck(playerPos.z, ITEM_GATHER_AREA, RULER_POS.z))
	{
		//�G���A���ɂ���Ȃ�t���O�𗧂Ă�
		CGatherManager::GetInstance()->GatherItem(RULER);
		CSound::PlaySE(CSound::SE_GET);
		//�����I���t���O�����Ă�
		endFlg_ = true;
		propertyFlg_ = true;
	}
}