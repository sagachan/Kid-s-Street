#pragma once

#include "Model/Model.h"

//3Dアニメーションクラス
class CAnim3D :public CModel
{
public:
	CAnim3D();				//コンストラクタ
	virtual ~CAnim3D();		//デストラクタ

public:
	virtual void Init() override;		//初期化
	virtual void Update() override;		//更新
	virtual void Fin() override;		//後処理

public:
	//--------ゲッター---------------
	float	GetAnimEndFrm() const { return anim_data_.end_frm_; }//アニメ全再生時間取得
	float	GetAnimFrm() const { return anim_data_.frm_; }		//アニメ再生時間取得
	int		GetAnimID() const { return anim_data_.id_; }		//再生中のアニメID取得、アニメが再生されていない場合は-1が戻ってくる
	bool	IsEndAnim()											//アニメが終了したか
		const { return anim_data_.end_frm_ == anim_data_.frm_ || anim_data_.end_frm_ == 0.f; }
	
	//-------セッター-------------
	void SetAnimFrm(float fFrm) { anim_data_.frm_ = fFrm; }		//アニメ再生時間設定
	void SetAnimSpd(float fSpd) { anim_data_.spd_ = fSpd; }		//	アニメ速度設定
	void SetChangeFlg() { changeFlg_ = true; }					//状態遷移が行われたときにtrueに


public:
	//アニメアップデート
	//アニメ更新処理、毎回呼んでください
	void UpdateAnim();

	//ループアニメリクエスト
	//アニメが最終フレームになったら最初に戻ります。
	void RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);

	//エンドアニメリクエスト
	//アニメが最終フレームになったらそのままで止まります。
	void RequestEndLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);

	//継承用
protected:
	int		frm_int_;	//int型のフレーム
	bool	end_animFlg_;
	bool	changeFlg_;	//アニメーション変更時に必要なフラグ

public:
	//-------継承変数関係の関数----------
	int GetFrmInt() { return frm_int_; }						//int型のフレームを取得
	bool GetEndAnimFlg() { return end_animFlg_; }				//アニメが現在再生されていないならtrue
	void ChangeAnim(bool flg) { changeFlg_ = flg; }				//アニメーション変更を行った時に呼ぶ
private:
	typedef struct {
		float	end_frm_;	//アニメ全再生時間
		float	frm_;		//アニメ再生時間
		float	spd_;		//アニメ再生速度
		int		handle_;	//アニメハンドル
		int		id_;		//再生中のアニメID
		int		state_;		//アニメの状態
	}ANIM_DATA;

	ANIM_DATA	anim_data_;	//アニメ再生関連データ

private:
	//安全にアニメをデタッチ
	void DetachAnim();
	//アニメリクエスト
	void Request(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
};