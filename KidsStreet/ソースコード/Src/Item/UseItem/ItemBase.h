  //エネミー用基底クラス

#pragma once
#include "DxLib.h"
#include "../../Library/Animation/Animation.h"
#include "../ItemCommon.h"

class CItemBase : public CAnim3D
{
public:
	CItemBase();
	virtual ~CItemBase();

	virtual void Init() = 0;//初期化
	virtual void Load() = 0;//読み込み
	virtual void Set() = 0;//設定
	virtual void Step() = 0;//毎フレーム呼ぶ処理
	virtual void Draw() = 0;//描画
	virtual void Update() = 0;//更新
	virtual void Delete() = 0;//削除
	virtual void Fin() = 0;//後処理

public:
	void Move();//移動計算処理

public:
	//使用フラグ
	bool GetUseFlg() { return isUse_; }			//取得
	void SetUseFlg(bool flg) { isUse_ = flg; }	//セット

	//使用終了しているか
	bool GetEndFlg() { return endflg_; }
	void SetEndFlg(bool flg) { endflg_ = flg; }

	//現在移動するか(使用されていて、処理が終わっていない)
	bool GetMoveFlg();

	//ダメージ取得
	int GetDmg() { return dmg_; }

	//アイテム番号セット
	void SetItemNum(int num) { itemNum_ = num; }

	//現在ボスに取られているか
	bool GetBossFlg() { return bossFlg_; }
	void SetBossFlg(bool flg) { bossFlg_ = flg; }

	//ボスに投げられたときにフラグを立てる
	void SetBossThrowFlg(bool flg) { bossThrowFlg_ = flg; }

	//ID取得
	ITEM_ID GetID() { return id_; }

protected:
	bool	doOnce_;			//一度だけ通る処理用
	bool	isUse_;				//使用フラグ
	bool	endflg_;			//使用終了フラグ
	bool	appear_flg_;		//現在存在しているかどうかのフラグ
	bool	bossFlg_;			//ボスにアイテムをとられているかどうか
	bool	bossThrowFlg_;		//ボスがアイテムを投げているかどうか
	bool	bossDoOnce_;		//ボスにキャッチされてから一度だけ通る処理

	int		dmg_;				//ダメージ量
	int		itemNum_;			//アイテム番号
	float	add_pos_;			//飛ぶ速度のフラグ

	VECTOR	forward_vec_;		//向きベクトル
	ITEM_ID id_;
};