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
	
	//	アニメ全再生時間取得
	float GetAnimEndFrm() const { return anim_data_.end_frm_; }

	//	アニメ再生時間取得
	float GetAnimFrm() const { return anim_data_.frm_; }

	//	再生中のアニメID取得
	//	@memo	:	アニメが再生されていない場合は-1が戻ってくる
	int GetAnimID() const { return anim_data_.id_; }

	//	アニメが終了したか
	bool IsEndAnim() const { return anim_data_.end_frm_ == anim_data_.frm_ || anim_data_.end_frm_ == 0.f; }


	//	アニメ再生時間設定
	void SetAnimFrm(float fFrm) { anim_data_.frm_ = fFrm; }

	//	アニメ速度設定
	void SetAnimSpd(float fSpd) { anim_data_.spd_ = fSpd; }


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

public:
	//-------継承変数取得関数----------
	//int型のフレームを取得
	int GetFrmInt() { return frm_int_; }

	//アニメが現在再生されているかの確認変数を取得
	bool GetEndAnimFlg() { return end_animFlg_; }

private:
	//アニメ関連のデータをまとめた構造体
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