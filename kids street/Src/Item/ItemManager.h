//ItemManager.h
//アイテムマネージャークラス

#pragma once

#include "DxLib.h"
#include "ItemBase.h"
#include "Eraser/Eraser.h"
#include "Pencil/Pencil.h"
#include "../Input/Input.h"
#include "../Player/PlayerManager.h"
#include "../Collision/CollisionManager.h"
#include "ItemCommon.h"
#include "../Common.h"


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
	void StepInput();		//入力処理関係
	void StepMove();		//移動処理関係
	void HitUpdate();		//当たり判定更新
	void DamageVanish(int num, ITEM_KIND kind);							//当たり判定処理実行関数
	void SetBossItemPos(VECTOR pos);										//ボスにとられたアイテム位置座標のセット
	void SetBossItemInfo(ITEM_KIND kind, int num);
	void SetBossItemThrow();											//ボスが手にしたアイテムを投げる処理

public:
	CItemBase*	GetEraser() {  return *itemEraser_; }
	CItemBase*	GetPencil() {  return *itemPencil_; }
	bool		GetHold() { return itemHoldflg_; }				//プレイヤーが手に持っている処理
	void		SetAppear(bool flg) { appearFlg_ = flg; }		//アイテムを出現させる
	bool		GetAppear() { return appearFlg_; }				//アイテムが現在使用可能かどうか
	void		SetHold(bool flg) { itemHoldflg_ = flg; }		//アイテムを手に持たせる
	bool		GetActivate() { return activate_; }				//残りがまだあるかどうか
	void		SetThrowflg(bool flg) { throwFlg_ = flg; }		//投げた時に呼ぶ
			

private:
	void MinimizeCall(CItemBase* item[], int maxNum, VOID_TYPE type);	//構造体参照処理短縮

private:
	static CItemManager* instance_;	//インスタンス

	//消しゴム
	CItemBase* itemEraser_[MAX_ERASER];				//基底ポインタ
	CEraser eraser_;									//消しゴムクラス

	//鉛筆
	CItemBase* itemPencil_[MAX_PENCIL];				//基底ポインタ
	CPencil pencil_;									//鉛筆クラス
	
	//変数
	bool		appearFlg_;					//出現させるかどうか
	bool		throwFlg_;					//現在投げているアイテムが一つでもあるかどうか
	bool		itemFlg_;					//現在選ばれているアイテムかどうか
	bool		itemHoldflg_;				//手に持つかどうか
	int			itemNum_;					//アイテム番号格納
	ITEM_KIND	itemKind_;					//アイテムの種類格納
	bool		pr_itemFlg_[MAX_ITEM_KIND];	//アイテムの種類分のフラグを用意する(処理速度を上げるため)
	int			dmg_;						//アイテムのダメージ
	bool		activate_;					//手に付けるものがない場合はfalse（残弾がない場合もfalse
	int			useNum_;					//何個目を表示するか		
	BossItem	bossItem_;

	//当たり判定用
	int			maxNum_;					//当たり判定情報受け渡しの時に使う動的配列の格納数を格納
};