#include "model.h"

// 定義関連
static const VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };		// オール0のVECTOR
static const VECTOR DEFAULT_SCALE = { 1.0f, 1.0f, 1.0f };	// 通常スケールはオール1なので


//------------------------------
//		コンストラクタ
//------------------------------
CModel::CModel() : pos_(VECTOR_ZERO), m_rot_(VECTOR_ZERO), m_scale_(DEFAULT_SCALE)
, m_hndl_(-1),m_old_pos_(VECTOR_ZERO),m_rad_(0.0f)
{
}


//------------------------------
//		デストラクタ
//------------------------------
CModel::~CModel()
{
	if (m_hndl_ != -1)
	{
		MV1DeleteModel(m_hndl_);
		m_hndl_ = -1;
	}
}


//---------------------------------
//		初期化
//---------------------------------
void	CModel::Init(void)
{
	Fin();
	pos_ = VECTOR_ZERO;
	m_rot_ = VECTOR_ZERO;
	m_scale_ = DEFAULT_SCALE;
}


//---------------------------------
//		終了処理
//---------------------------------
void	CModel::Fin(void)
{
	DeleteModel();
}


//---------------------------------
//		更新処理
//---------------------------------
void	CModel::Update(void)
{
	MV1SetPosition(m_hndl_, pos_);
	MV1SetRotationXYZ(m_hndl_, m_rot_);
	MV1SetScale(m_hndl_, m_scale_);
}


//------------------------------
//		データ読み込み
//------------------------------
bool	CModel::LoadModel(const char* fileName)
{
	if (m_hndl_ != -1) return false;		// モデル読み込み済み
	m_hndl_ = MV1LoadModel(fileName);
	if (m_hndl_ == -1) return false;		// モデルの読み込み失敗
	return true;
}


//------------------------------
//		コピーデータ読み込み
//------------------------------
bool	CModel::DuplicateModel(int srcHndl)
{
	if (m_hndl_ != -1) return false;		// モデル読み込み済み
	m_hndl_ = MV1DuplicateModel(srcHndl);
	if (m_hndl_ == -1) return false;		// モデルの読み込み失敗
	return true;
}


//---------------------------------
//		モデルデータ削除
//---------------------------------
void	CModel::DeleteModel(void)
{
	if (m_hndl_ == -1) return;

	MV1DeleteModel(m_hndl_);
	m_hndl_ = -1;
}


//---------------------------------
//		モデルデータ描画
//---------------------------------
void	CModel::Draw(void)
{
	MV1DrawModel(m_hndl_);
}
