//GatherManager.h
//UI管理用クラス

#pragma once

#include "GatherBase/GatherItem.h"
#include "../../ItemCommon.h"
#include <vector>

//アイテム収集管理用クラス
class CGatherManager
{
public:
	enum GATHER_TYPE
	{
		BOSS_ONLY_ITEM
	};

public:
	CGatherManager();
	~CGatherManager();

public:
	static void CreateInstance() { if (!instance_) instance_ = new CGatherManager; }
	static CGatherManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

public:
	void Step();						//ステップ
	void Draw();						//描画
	void DeleteAll();					//削除

public:
	CGatherItem* CreateItem(GATHER_TYPE type);	//アイテムの生成
	void GatherItem(ITEM_KIND kind);			//アイテムが集められたときに通る
	ITEM_ID CheckItemID(float posX);			//UI限定のIDゲット
	ITEM_ID CheckItemID(VECTOR pos);			//フィールド上のアイテムのIDゲット
	bool GetIDFlg(ITEM_ID id);
	

public:
	//ゲッター
	bool* GetGatherItem() { return gatherItemFlg_; }

private:
	static CGatherManager* instance_;
	bool gatherItemFlg_[ITEM_MAX_KIND];			//アイテムが集められるとtrueになる


	//今後、どんどんアイテムが増えても大丈夫なように
	//動的配列として宣言
	std::vector<CGatherItem*> item_vec_;
};