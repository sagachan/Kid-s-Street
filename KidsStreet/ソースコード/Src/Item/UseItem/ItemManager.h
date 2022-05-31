//ItemManager.h
//アイテムマネージャークラス

#pragma once

#include "DxLib.h"
#include "ItemBase.h"
#include "../../Library/Input/Input.h"
#include "../../Player/PlayerManager.h"
#include "../../Collision/CollisionManager.h"
#include "../ItemCommon.h"
#include "../../Common.h"
#include "../GatherItem/GatherFactory/GatherBase/GatherBase.h"
#include "../../Library/LibraryCommon.h"



class CItemManager
{
public:
	enum
	{
		FLG_ERASER,
		FLG_PENCIL,
		MAX_ITEM_KIND
	};

	//ボスが取得したアイテム情報の構造体
	struct BossItem
	{
		ITEM_KIND	kind_;					//ボスにとられたアイテム情報
		int			num_;					//ボスにとられたアイテム番号格納
	};

private:
	//クラスの規定ポインタ配列をチェックするときに使う
	struct ClassNumInfo
	{
		int initNum_;
		int maxNum_;
	};

public:

	CItemManager();		//コンストラクタ
	~CItemManager();		//デストラクタ

public:
	//インスタンス生成
	static void CreateInstance() { if (!instance_) instance_ = new CItemManager; }
	//インスタンス取得
	static CItemManager* GetInstance() { return instance_; }
	//インスタンス削除
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();			//初期化
	void Load();			//読み込み（ロード）
	void Set();				//各変数などに初期値を設定（セット）
	void Step();			//毎フレーム呼ぶ処理（操作）
	void Update();			//更新
	void Draw();			//描画
	void Delete();			//削除
	void Fin();				//後処理

public:
	void HitUpdate();		//当たり判定更新
	void DamageVanish(int num);				//当たり判定処理実行関数
	
public:
	//ゲッター
	bool		GetHold()		{ return itemHoldflg_; }	//プレイヤーの手に持てるかどうか
	bool		GetActivate()	{ return activate_; }		//残りがまだあるかどうか
	ITEM_KIND	GetItemKind()	{ return itemKind_; }
	bool		IDFromKind(ITEM_ID id);
	int			GetUseNum() { return useNum_; }

	//セッター
	void		SetHold(bool flg)		{ itemHoldflg_ = flg; }			//アイテムを手に持たせる
	void		SetThrowflg(bool flg)	{ throwFlg_ = flg; }			//投げた時に呼ぶ
	void		SetBossItemPos(VECTOR pos);								//ボスにとられたアイテム位置座標のセット
	void		SetBossItemInfo(int num);
	void		SetBossItemThrow();										//ボスが手にしたアイテムを投げる処理


private:
	void MinimizeCall(CItemBase* item[], int maxNum, VOID_TYPE type);	//構造体参照処理短縮
	void MinimizeCall(CGatherBase* item[], int maxNum, VOID_TYPE type);	//構造体参照処理短縮
	void SerchItem(CItemBase* item[], ITEM_KIND kind);					//手に持てるアイテムを探す
	ClassNumInfo CheckItem(ITEM_KIND kind);								//引数に入れた種類のアイテムのuseItem配列上の番号を持ってくる
	void StepInput();		//入力処理関係
	void StepMove();		//移動処理関係
	
private:
	static CItemManager* instance_;	//インスタンス

	CGatherBase*	gatherItem_[ITEM_ID_MAX];			//アイテム収集クラス
	CItemBase*		useItem_[MAX_ITEM_NUM];				//アイテム使用クラス
	
	//変数
	bool		throwFlg_;					//現在投げているアイテムが一つでもあるかどうか
	bool		itemHoldflg_;				//手に持つかどうか
	bool		activate_;					//手に付けるものがない場合はfalse（残弾がない場合もfalse
	bool		initFlg_;
	int			useNum_;					//何個目を表示するか	

	BossItem	bossItem_;
	ITEM_KIND	itemKind_;					//アイテムの種類格納

};