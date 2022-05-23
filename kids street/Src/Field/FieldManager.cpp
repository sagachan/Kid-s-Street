//FieldManager.cpp
//�t�B�[���h�Ǘ�
//CField�ւ̃A�N�Z�X�͕K��CFieldManager���o�R

#include "FieldManager.h"
//CFieldManager�̎��̐錾�A������
CFieldManager* CFieldManager::instance_ = nullptr;

//�R���X�g���N�^
CFieldManager::CFieldManager()
{
}

//�f�X�g���N�^
CFieldManager::~CFieldManager()
{
}

void CFieldManager::Init()
{
	field_.Init();
	road_.Init();
	inter_.Init();
	
}


//�ǂݍ���
void CFieldManager::Load()
{
	field_.Load();
	road_.Load();
	inter_.Load();
}



//�Z�b�g
void CFieldManager::Set()
{
	field_.Set();
	road_.Set();
	inter_.Set();
}


//�X�e�b�v
void CFieldManager::Step()
{
	field_.Step();
	road_.Step();
	inter_.InterManager();
}


//�X�V
void CFieldManager::Update()
{
	field_.Update();
	road_.Update();
	
}


//�`��
void CFieldManager::Draw()
{
	field_.Draw();
	road_.Draw();
	
}


//�폜
void CFieldManager::Delete()
{
	field_.Delete();
	road_.Delete();
	inter_.Delete();
}


//�㏈��
void CFieldManager::Fin()
{
	field_.Fin();
	road_.Fin();
	inter_.Fin();
	
}

