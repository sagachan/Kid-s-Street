//GameUIManager.h
//UI管理用クラス

#pragma once

#include "UIBase.h"
#include "HP/GameUIHP.h"
#include <vector>
#include "../Library/LibraryCommon.h"
#include "../Item/ItemCommon.h"

//UI管理用クラス
class CGameUIManager
{
public:
	enum UI_TYPE
	{
		UI_TYPE_SPRITE,		//背景や画面全体表示
		UI_TYPE_BUTTON,		//いくつかを組み合わせる個別の物
		UI_TYPE_HP,			//HPバー
		UI_TYPE_ITEM,		//途中表示するアイテム
		UI_TYPE_ITEMBOX,	//アイテムボックス
		UI_TYPE_ASSERT		//外部からの描画フラグ参照によって描画を切り替えるUI
	};

public:
	CGameUIManager();
	~CGameUIManager();

public:
	static void CreateInstance() { if (!instance_) instance_ = new CGameUIManager; }
	static CGameUIManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

public:
	CGameUI* CreateUI(UI_TYPE type);	//UIの生成
	void Step();						//ステップ
	void Draw();						//描画
	void DeleteUI(ITEM_ID id);					//UIを選択削除
	void DeleteAll();					//UIの削除
	void MinimizeCall(CUIBase* ui[], int max, VOID_TYPE type);

public:
	//ゲッター
	bool GetInputFlg() { return inputFlg_; }
	//セッター
	void SetInputFlg(bool flg) { inputFlg_ = flg; }

	void SetBossFlg(bool flg);

private:
	static CGameUIManager* instance_;

	//UIが画面表示されていてプレイヤーなどの入力処理よりも
	//UIを読ませたり使わせたりすることを優先させたいときに使う
	bool inputFlg_;						

	//今後、どんどんUIが増えても大丈夫なように
	//動的配列として宣言
	std::vector<CGameUI*> ui_vec_;

};