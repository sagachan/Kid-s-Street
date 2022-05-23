//GatherManager.cpp
//UI�Ǘ��p�N���X

#include "GatherManager.h"
#include "ItemType/BossBattleItem.h"
#include "../../../Library/MyMath/MyMath.h"

CGatherManager* CGatherManager::instance_ = nullptr;

CGatherManager::CGatherManager()
{
	for (int itemNum = 0; itemNum < ITEM_MAX_KIND; itemNum++) {
		gatherItemFlg_[itemNum] = false;
	}
}

CGatherManager::~CGatherManager()
{
	DeleteAll();
}

//�A�C�e���̐���
CGatherItem* CGatherManager::CreateItem(GATHER_TYPE type)
{
	CGatherItem* item = nullptr;
	switch (type) 
	{
		case BOSS_ONLY_ITEM:	item = new CBossBattleItem; break;
	}

	item_vec_.push_back(item);
	return item;
}

//�A�C�e�����W�߂鏈��
void CGatherManager::GatherItem(ITEM_KIND kind)
{
	gatherItemFlg_[kind] = true;
}


//�X�e�b�v
void CGatherManager::Step()
{
	for (auto itr = item_vec_.begin(); itr != item_vec_.end(); itr++)
	{
		(*itr)->Step();
	}
}


//�`��
void CGatherManager::Draw()
{
	for (auto itr = item_vec_.begin(); itr != item_vec_.end(); itr++)
	{
		(*itr)->Draw();
	}
}


//UI�̍폜�ivector����UI�����ׂč폜�j
void CGatherManager::DeleteAll()
{
	//�܂�UI���폜���Ă���
	for (auto itr = item_vec_.begin(); itr != item_vec_.end(); itr++)
	{
		CGatherItem* item = (*itr);
		item->Fin();
		delete item;
	}
	//�z����폜����
	item_vec_.clear();
	item_vec_.shrink_to_fit();
}

ITEM_ID CGatherManager::CheckItemID(float posX)
{
	//�ʒu��񂪈�v����ID���܂��͒T��
	if (posX == ITEM_UI_ERASER)
		return ITEM_ID_ERASER;
	if (posX == ITEM_UI_PENCIL)
		return ITEM_ID_PENCIL;
	if (posX == ITEM_UI_RULER)
		return ITEM_ID_RULER;
	if (posX = ITEM_UI_GLOVE)
		return ITEM_ID_GLOVE;
	
	return ITEM_ID_NONE;
}

ITEM_ID CGatherManager::CheckItemID(VECTOR pos)
{
	//�ʒu��񂪈�v����ID���܂��͒T��
	if (CMyMath::VectorEqual(pos,ERASER_POS))
		return ITEM_ID_ERASER;
	if (CMyMath::VectorEqual(pos, PENCIL_POS))
		return ITEM_ID_PENCIL;
	if (CMyMath::VectorEqual(pos, RULER_POS))
		return ITEM_ID_RULER;
	if (CMyMath::VectorEqual(pos, GLOVE_POS))
		return ITEM_ID_GLOVE;

	return ITEM_ID_NONE;
}

bool CGatherManager::GetIDFlg(ITEM_ID id)
{
	//���`�悵�Ă����̂��`�F�b�N����
	if (id == ITEM_ID_ERASER)
		return gatherItemFlg_[ERASER];
	if (id == ITEM_ID_PENCIL)
		return gatherItemFlg_[PENCIL];
	if (id == ITEM_ID_RULER)
		return gatherItemFlg_[RULER];
	if (id == ITEM_ID_GLOVE)
		return gatherItemFlg_[GLOVE];

	return false;
}