#pragma once
#include <DxLib.h>
#include "../../LibraryCommon.h"



//---------------------------------------------
//	3Dモデルを1体表示するためのクラス
//---------------------------------------------
class CModel {
protected:
	VECTOR		pos_;			// 座標
	VECTOR		oldPos_;		// 移動前座標
	VECTOR		rot_;			// 回転角度
	VECTOR		oldRot_;
	VECTOR		scale_;			// 拡大縮小率
	VECTOR		move_;
	float		rad_;			// 半径
	int			hndl_;			// モデルハンドル
	int			colNum_;		//当たり判定番号格納変数
	COL_DATA	colData_;			//当たり判定構造体

public:
	CModel();
	virtual ~CModel();

	//		初期化
	virtual void	Init(void);
	//		終了処理
	virtual void	Fin(void);
	//		数値の更新処理
	virtual void	Update(void);
	//		モデル描画
	virtual void	Draw(void);



	//***************************************
	//		画像読み込み関連
	//***************************************
	//		モデル通常ロード
	//	fileName	:	読み込みたいモデルデータ名
	bool	LoadModel(const char* fileName);
	//		モデルコピーロード
	//	@memo		:	すでに読み込んであるモデルを複数表示したい場合に使用します。
	//	srcHndl	:	読み込みたいモデルのハンドル
	bool	DuplicateModel(int srcHndl);
	//		モデルデータ削除
	void	DeleteModel(void);


	//ゲッター。
	inline int		GetHandle(void) { return hndl_; }				//ハンドル
	inline VECTOR	GetPosition(void) { return pos_; }				//モデルの座標
	inline VECTOR	GetOldPosition(void) { return oldPos_; }		//モデルの前ループ座標
	inline VECTOR	GetOldRotation(void) { return oldRot_; }		//モデルの前ループ回転値
	inline VECTOR	GetScale(void) { return scale_; }				//モデルのスケール
	inline VECTOR	GetRot(void) { return rot_; }					//モデルの回転
	inline VECTOR	GetMove(void) { return move_; }					//モデルの移動値
	inline float	GetRad(void) { return rad_; }					//モデルの半径

	//設定
	//現在の位置
	inline void	SetPosition(const VECTOR& pos) { pos_ = pos; }
	//現在のサイズ
	inline void	SetScale(const VECTOR& scale) { scale_ = scale; }
	inline void	SetScale(float scale) { scale_.x = scale_.y = scale_.z = scale; }
	//現在の角度
	inline void	SetRot(const VECTOR& rot) { rot_ = rot; }
};

