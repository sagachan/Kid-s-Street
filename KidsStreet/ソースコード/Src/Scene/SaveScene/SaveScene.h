//セーブデータ管理
//前回ゲーム時の位置座標やアイテム獲得フラグなどを保持

#pragma once
#include "DxLib.h"
#include "../../Item/ItemCommon.h"




class CSaveScene
{
public:
	CSaveScene();
	~CSaveScene() {}

public:
	static void CreateInstance() { if (!instance_)instance_ = new CSaveScene; }
	static CSaveScene* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }


public:
	//ゲッター
	bool* GetItemSaveFlg() { return itemSaveFlg_; }
	bool	GetBossFlg() { return bossFlg_; }

	//セッター
	void	SetItemSaveFlg(bool* flg);
	void	SetBossFlg(bool flg) { bossFlg_ = flg; }

private:
	static CSaveScene* instance_;
	bool itemSaveFlg_[ITEM_MAX_KIND];
	bool bossFlg_;						//falseならボス戦に入れている
};
