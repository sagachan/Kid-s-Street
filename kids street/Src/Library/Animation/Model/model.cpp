#include "model.h"

// ��`�֘A
static const VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };		// �I�[��0��VECTOR
static const VECTOR DEFAULT_SCALE = { 1.0f, 1.0f, 1.0f };	// �ʏ�X�P�[���̓I�[��1�Ȃ̂�


//------------------------------
//		�R���X�g���N�^
//------------------------------
CModel::CModel() : pos_(VECTOR_ZERO), rot_(VECTOR_ZERO), scale_(DEFAULT_SCALE)
, hndl_(-1),oldPos_(VECTOR_ZERO),rad_(0.0f),move_({0.0f}),oldRot_({0.0f})
{
}


//------------------------------
//		�f�X�g���N�^
//------------------------------
CModel::~CModel()
{
	if (hndl_ != -1)
	{
		MV1DeleteModel(hndl_);
		hndl_ = -1;
	}
}


//---------------------------------
//		������
//---------------------------------
void	CModel::Init(void)
{
	Fin();
	pos_ = VECTOR_ZERO;
	rot_ = VECTOR_ZERO;
	scale_ = DEFAULT_SCALE;
}


//---------------------------------
//		�I������
//---------------------------------
void	CModel::Fin(void)
{
	DeleteModel();
}


//---------------------------------
//		�X�V����
//---------------------------------
void	CModel::Update(void)
{
	MV1SetPosition(hndl_, pos_);
	MV1SetRotationXYZ(hndl_, rot_);
	MV1SetScale(hndl_, scale_);
}


//------------------------------
//		�f�[�^�ǂݍ���
//------------------------------
bool	CModel::LoadModel(const char* fileName)
{
	if (hndl_ != -1) return false;		// ���f���ǂݍ��ݍς�
	hndl_ = MV1LoadModel(fileName);
	if (hndl_ == -1) return false;		// ���f���̓ǂݍ��ݎ��s
	return true;
}


//------------------------------
//		�R�s�[�f�[�^�ǂݍ���
//------------------------------
bool	CModel::DuplicateModel(int srcHndl)
{
	if (hndl_ != -1) return false;		// ���f���ǂݍ��ݍς�
	hndl_ = MV1DuplicateModel(srcHndl);
	if (hndl_ == -1) return false;		// ���f���̓ǂݍ��ݎ��s
	return true;
}


//---------------------------------
//		���f���f�[�^�폜
//---------------------------------
void	CModel::DeleteModel(void)
{
	if (hndl_ == -1) return;

	MV1DeleteModel(hndl_);
	hndl_ = -1;
}


//---------------------------------
//		���f���f�[�^�`��
//---------------------------------
void	CModel::Draw(void)
{
	MV1DrawModel(hndl_);
}
