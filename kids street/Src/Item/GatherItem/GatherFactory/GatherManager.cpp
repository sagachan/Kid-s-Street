//GatherManager.cpp
//UI管理用クラス

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

//アイテムの生成
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

//アイテムを集める処理
void CGatherManager::GatherItem(ITEM_KIND kind)
{
	gatherItemFlg_[kind] = true;
}


//ステップ
void CGatherManager::Step()
{
	for (auto itr = item_vec_.begin(); itr != item_vec_.end(); itr++)
	{
		(*itr)->Step();
	}
}


//描画
void CGatherManager::Draw()
{
	for (auto itr = item_vec_.begin(); itr != item_vec_.end(); itr++)
	{
		(*itr)->Draw();
	}
}


//UIの削除（vector内のUIをすべて削除）
void CGatherManager::DeleteAll()
{
	//まずUIを削除してから
	for (auto itr = item_vec_.begin(); itr != item_vec_.end(); itr++)
	{
		CGatherItem* item = (*itr);
		item->Fin();
		delete item;
	}
	//配列を削除する
	item_vec_.clear();
	item_vec_.shrink_to_fit();
}

ITEM_ID CGatherManager::CheckItemID(float posX)
{
	//位置情報が一致するIDをまずは探す
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
	//位置情報が一致するIDをまずは探す
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
	//今描画していいのかチェックする
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