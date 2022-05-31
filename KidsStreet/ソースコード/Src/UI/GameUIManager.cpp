//GameUIManager.cpp
//UI�Ǘ��p�N���X

#include "GameUIManager.h"
#include "Item/GameUIItem.h"
#include "Item/GameUIItemBox.h"
#include "GameUISprite.h"
#include "GameUIButton.h"
#include "Assert/GameUIAssert.h"
#include "../Library/Error/Error.h"
#include "../Enemy/EnemyCommon.h"

CGameUIManager* CGameUIManager::instance_ = nullptr;

CGameUIManager::CGameUIManager()
	:inputFlg_(false)
{
}

CGameUIManager::~CGameUIManager()
{
}

//UI�̐���
CGameUI* CGameUIManager::CreateUI(UI_TYPE type)
{
	CGameUI* ui = nullptr;
	switch (type) {
		case UI_TYPE_SPRITE:	ui = new CGameUISprite;		break;
		case UI_TYPE_BUTTON:	ui = new CGameUIButton;		break;
		case UI_TYPE_HP:		ui = new CGameUIHP;			break;
		case UI_TYPE_ITEMBOX:	ui = new CGameUIItemBox;	break;
		case UI_TYPE_ITEM:		ui = new CGameUIItem;		break;
		case UI_TYPE_ASSERT:	ui = new CGameUIAssert;		break;
	}

	ui_vec_.push_back(ui);
	return ui;
}


//�X�e�b�v
void CGameUIManager::Step()
{
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		(*itr)->Step();
	}
}


//�`��
void CGameUIManager::Draw()
{
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		(*itr)->Draw();
	}
}

void CGameUIManager::DeleteUI(ITEM_ID id)
{
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		if (id == ITEM_ID_ERASER && ITEM_UI_ERASER == (*itr)->GetPosX())
		{
			(*itr)->SetDrawFlg(true);
		}
		
		if (id == ITEM_ID_PENCIL && ITEM_UI_PENCIL == (*itr)->GetPosX())
		{
			(*itr)->SetDrawFlg(true);
		}

		if (id == ITEM_ID_RULER && ITEM_UI_RULER == (*itr)->GetPosX())
		{
			(*itr)->SetDrawFlg(true);
		}
	}
}

//�{�X��UI��z�񂩂�T���ăt���O�𗧂Ă鏈��
void CGameUIManager::SetBossFlg(bool flg)
{
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		if (BOSS_HP_UI_X == (*itr)->GetPosX())
		{
			(*itr)->SetDrawFlg(flg);
		}
	}
}

//UI�̍폜�ivector����UI�����ׂč폜�j
void CGameUIManager::DeleteAll()
{
	//�܂�UI���폜���Ă���
	for (auto itr = ui_vec_.begin(); itr != ui_vec_.end(); itr++)
	{
		CGameUI* ui = (*itr);
		ui->Fin();
		delete ui;
	}
	//�z����폜����
	ui_vec_.clear();
	ui_vec_.shrink_to_fit();
}

//�I�[�o�[���C�h�����N���X�̍\���̂̒��g��num�Ԗڂ܂ŉ񂵂ĎQ�ƁA�^�C�v�ɂ���ď����𕪂���
void CGameUIManager::MinimizeCall(CUIBase* ui[], int maxNum, VOID_TYPE type)
{
	//-------------�����ł�肽������----------------
	//  ����for���������Ċ֐����Ă΂Ȃ��Ƃ����Ȃ����̂͂����܂Ƃ߂ČĂׂ�悤�Ɋ֐�����Ă��܂���
	// ---------------------------------------------- 

	for (int kind = 0; kind < maxNum; kind++)
	{
		switch (type)
		{
		case VOID_INIT:ui[kind]->Init(); break;
		case VOID_LOAD:ui[kind]->Load(); break;
		case VOID_SET:ui[kind]->Set(); break;
		case VOID_STEP:ui[kind]->Step(); break;
		case VOID_DRAW:ui[kind]->Draw(); break;
		case VOID_FIN:ui[kind]->Fin(); break;

			//�ǂ�ɂ������Ȃ��ꍇ
		default:CError::MinimizeVoidError();break;
		}
	}

	
}
