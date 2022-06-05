//FieldManager.cpp
//�t�B�[���h�Ǘ�
//CField�ւ̃A�N�Z�X�͕K��CFieldManager���o�R

#include "FieldManager.h"
//CFieldManager�̎��̐錾�A������
CFieldManager* CFieldManager::instance_ = nullptr;

//�ǂݍ���
void CFieldManager::Load()
{
	field_.Load();
	road_.Load();
	inter_.Load();
	pole_.Load();
	navi_.Load();
}

//�Z�b�g
void CFieldManager::Set()
{
	field_.Set();
	road_.Set();
	inter_.Set();
	pole_.Set();
}

//�X�e�b�v
void CFieldManager::Step()
{
	inter_.InterManager();
	navi_.Step();
}

//�X�V
void CFieldManager::Update()
{
	field_.Update();
	road_.Update();
	pole_.Update();
}

//�`��
void CFieldManager::Draw()
{
	field_.Draw();
	road_.Draw();
	pole_.Draw();
	navi_.Draw();
}


