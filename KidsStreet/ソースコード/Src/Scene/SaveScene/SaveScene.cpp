
#include "SaveScene.h"

//CSaveScene�̎��̐錾�A������
CSaveScene* CSaveScene::instance_ = nullptr;

CSaveScene::CSaveScene()
{
	bossFlg_ = true;
	for (int itemNum = 0; itemNum < ITEM_MAX_KIND; itemNum++) {
		itemSaveFlg_[itemNum] = false;
	}
}

void CSaveScene::SetItemSaveFlg(bool* flg)
{
	for (int itemNum = 0; itemNum < ITEM_MAX_KIND; itemNum++) {
		itemSaveFlg_[itemNum] = flg[itemNum];
	}
}