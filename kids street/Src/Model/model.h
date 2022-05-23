#pragma once
#include <DxLib.h>



//---------------------------------------------
//	3Dモデルを1体表示するためのクラス
//---------------------------------------------
class CModel{
protected:
	VECTOR	m_pos;			// 座標
	VECTOR	m_rot;			// 回転角度
	VECTOR	m_scale;		// 拡大縮小率
	int		m_hndl;			// モデルハンドル


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


	//***************************************
	//		取得関数
	//***************************************
	//		モデルハンドル取得
	//	@memo	:	主にこのモデルをコピーして使いたい他のクラスに
	//			:	渡すためのものです。
	inline int		GetHandle(void){ return	m_hndl; }
	//		位置取得
	//	@return	:	モデルの座標
	inline VECTOR	GetPosition(void){ return m_pos; }
	//		スケール取得
	//	@return	:	モデルのスケール
	inline VECTOR	GetScale(void){ return m_scale; }
	//		回転角度取得
	//	@return	:	モデルの回転角度
	inline VECTOR	GetRot(void){ return m_rot; }

	//***************************************
	//		設定関数
	//***************************************
	//		位置設定
	//	pos		:	現在の位置
	inline void	SetPosition(const VECTOR& pos){ m_pos = pos; }
	//		スケール設定
	//	scale	:	現在のサイズ
	inline void	SetScale(const VECTOR& scale){ m_scale = scale; }
	inline void	SetScale(float scale){ m_scale.x = m_scale.y = m_scale.z = scale; }
	//		回転角度設定
	//	rot		:	現在の角度
	inline void	SetRot(const VECTOR& rot){ m_rot = rot; }
};

