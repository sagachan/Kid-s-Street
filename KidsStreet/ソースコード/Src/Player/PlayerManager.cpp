//PlayerManager.cpp
//�v���C���[�Ǘ�
//CPlayer�ւ̃A�N�Z�X�͕K��CPlayerManager���o�R

#include "PlayerManager.h"

//CPlayerManager�̎��̐錾�A������
CPlayerManager* CPlayerManager::instance_ = nullptr;


//�R���X�g���N�^
CPlayerManager::CPlayerManager()
{
	//CPlayer�̃R���X�g���N�^�͎����ŌĂ΂�܂�
}

//�f�X�g���N�^
CPlayerManager::~CPlayerManager()
{
	//CPlayer�̃f�X�g���N�^�͎����ŌĂ΂�܂�
}


//������
void CPlayerManager::Init()
{
	ui_[PLAYER_HP] = &hp_;
	ui_[FRAME_HP] = &hpFrame_;
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_INIT);
}


//�ǂݍ���
void CPlayerManager::Load()
{
	//�v���C���[�̓ǂݍ���
	player_.Load();
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_LOAD);
}


//�Z�b�g
void CPlayerManager::Set()
{
	//�v���C���[�̃Z�b�g
	player_.Set();

	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_SET);
}


//�X�e�b�v
void CPlayerManager::Step()
{
	//�v���C���[�̃X�e�b�v
	player_.Step();

	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_STEP);
}


//���f
void CPlayerManager::Update()
{
	//�v���C���[�̔��f
	player_.Update();
}


//�`��
void CPlayerManager::Draw()
{
	//�v���C���[�̕`��
	player_.Draw();

	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_DRAW);
}


//�폜
void CPlayerManager::Delete()
{
	//�v���C���[�폜
	player_.Delete();

	
}


//�㏈��
void CPlayerManager::Fin()
{
	//�v���C���[�̌㏈�����Ă�
	player_.Fin();

	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_FIN);
}