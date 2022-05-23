//Inter.h
//交差点クラス

#pragma once

#include "DxLib.h"
#include "../FieldCommon.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Enemy/EnemyCommon.h"


class CInter
{
public:

public:
	CInter();
	~CInter();

public:
	void Init();
	void Set();
	void Load();
	void Delete();
	void Fin();

public://交差点関数
	void InterManager();											//交差点管理関数(これを読み込めば交差点関数のすべてに通る
	void CheckComeInter(VECTOR carPos,int frmNum,int interNum,int carNum);		//車が交差点に入っているかどうかを確認する、もし入っているならdirInfoの使用フラグを立てる。この処理は使用フラグが立っているときは通らない
	void CheckOutInter(VECTOR carPos, int interNum, int carNum);	//交差点から出る時に通る処理										//交差点の外に出たことが確認された場合、使用フラグを折る。使用フラグがおられているときはこの処理は通らない
	void JudgeInter(VECTOR carPos, int interNum, int carNum);		//どの方向に行くかを判定する
	int	 CheckInter(bool* inter,int carNum);												//現在車がどちらの向きからきているのかを判定する処理

public://取得、セット関数
	int GetFrmHndl()				 { return frmHndl_; }			//ハンドル情報取得
	float GetInterRad();											//交差点の範囲を返す処理

private:
	InterInfo			interInfo_[INTER_MAX_NUM];						//交差点タイプ構造体配列

	int					frmHndl_;									//ボーン情報ハンドル

	bool				carFlg_[APPEAR_CAR_NUM];					//車が交差点に入っている場合はtrue
};