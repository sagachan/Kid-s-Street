  //エネミー用基底クラス

#pragma once
#include "DxLib.h"
#include "../Animation/Animation.h"

class CItemBase : public CAnim3D
{
public:
	CItemBase();
	virtual ~CItemBase();

	//初期化
	virtual void Init() = 0;
	//読み込み
	virtual void Load() = 0;
	//設定
	virtual void Set() = 0;
	//毎フレーム呼ぶ処理
	virtual void Step() = 0;
	//移動計算処理
	virtual void Move() = 0;
	//描画
	virtual void Draw() = 0;
	//更新
	virtual void Update() = 0;
	//削除
	virtual void Delete() = 0;
	//後処理
	virtual void Fin() = 0;

	//当たり判定用
	virtual VECTOR	GetHit() = 0;
	virtual float	GetSimpleHit() = 0;

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

	//現在ボスに取られているか
	bool GetBossFlg() { return bossFlg_; }
	void SetBossFlg(bool flg) { bossFlg_ = flg; }

	//ボスに投げられたときにフラグを立てる
	void SetBossThrowFlg(bool flg) { bossThrowFlg_ = flg; }

protected:
	bool	doOnce_;			//一度だけ通る処理用
	bool	isUse_;				//使用フラグ
	bool	endflg_;			//使用終了フラグ
	int		dmg_;				//ダメージ量
	float	radius_;			//簡易当たり判定
	VECTOR	hit_radius_;		//当たり範囲の広さ
	bool	appear_flg_;		//現在存在しているかどうかのフラグ
	float	add_pos_;			//飛ぶ速度のフラグ
	VECTOR	forward_vec_;		//向きベクトル
	int		add_num_;			//加算回数
	bool	bossFlg_;			//ボスにアイテムをとられているかどうか
	bool	bossThrowFlg_;		//ボスがアイテムを投げているかどうか
	bool	bossDoOnce_;		//ボスにキャッチされてから一度だけ通る処理
};