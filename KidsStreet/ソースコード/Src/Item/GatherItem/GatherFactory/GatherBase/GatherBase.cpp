
#include "GatherBase.h"
#include "../../../../Library/Input/Input.h"
#include "../../../../UI/GameUIManager.h"
#include "../../../UseItem/ItemManager.h"
#include"../GatherManager.h"

CGatherBase::CGatherBase()
	:kind_(ITEM_INIT)
	,endFlg_(false)
	,propertyFlg_(false)
	,type_(PROPERTY_OPEN)
{
	
}

CGatherBase::~CGatherBase()
{

}

void CGatherBase::Update()
{
	SelectWindow();
	PropertyWindow();
}

void CGatherBase::PropertyWindow()
{
	if (propertyFlg_)
	{
		CInput* input = CInput::GetInstance();
		if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_RETURN)) {
			type_++;
		}

		switch (type_) {
		case PROPERTY_OPEN:
			uiProperty_[PROPERTY_OPEN]->SetDrawFlg(true);
			CGameUIManager::GetInstance()->SetInputFlg(true);
			break;
		case PROPERTY_CLOSE:
			propertyFlg_ = false;
			uiProperty_[PROPERTY_OPEN]->SetDrawFlg(false);
			CGameUIManager::GetInstance()->SetInputFlg(false);
			type_ = 0;
			break;
		}
	}
}

void CGatherBase::SelectWindow()
{
	if (!propertyFlg_)
	{
		//���ݑI�����Ă���A�C�e�������肳��Ă��邩���m�F
		CItemManager* itemManager = CItemManager::GetInstance();
		ITEM_KIND kindHold = itemManager->GetItemKind();

		if (kind_ == kindHold)
		{
			CGatherManager* gatherManager = CGatherManager::GetInstance();
			bool* gatherFlg = gatherManager->GetGatherItem();
			if (gatherFlg[kind_])
			{
				//���肳��Ă���Ȃ�o���������Ƃ��Ƀv���p�e�B���J��
				CInput* input = CInput::GetInstance();
				if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_P)) {
					propertyFlg_ = true;
				}
			}
		}
	}
}