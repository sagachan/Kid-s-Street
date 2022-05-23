#pragma once
#include <DxLib.h>



//---------------------------------------------
//	3Dモデルを1体表示するためのクラス
//---------------------------------------------
class CModel {
protected:
	VECTOR	pos_;			// 座標
	VECTOR  m_old_pos_;		// 移動前座標
	VECTOR	m_rot_;			// 回転角度
	VECTOR	m_scale_;		// 拡大縮小率
	float	m_rad_;			// 半径
	int		m_hndl_;		// モデルハンドル


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
	inline int		GetHandle(void) { return m_hndl_; }				//ハンドル
	inline VECTOR	GetPosition(void) { return pos_; }			//モデルの座標
	inline VECTOR	GetOldPosition(void) { return m_old_pos_; }		//モデルの前ループ座標
	inline VECTOR	GetScale(void) { return m_scale_; }				//モデルのスケール
	inline VECTOR	GetRot(void) { return m_rot_; }					//モデルの回転
	inline float	GetRad(void) { return m_rad_; }					//モデルの半径

	//設定
	//現在の位置
	inline void	SetPosition(const VECTOR& pos) { pos_ = pos; }
	//現在のサイズ
	inline void	SetScale(const VECTOR& scale) { m_scale_ = scale; }
	inline void	SetScale(float scale) { m_scale_.x = m_scale_.y = m_scale_.z = scale; }
	//現在の角度
	inline void	SetRot(const VECTOR& rot) { m_rot_ = rot; }
};

