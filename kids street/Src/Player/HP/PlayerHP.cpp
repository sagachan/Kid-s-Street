//PlayerHP.cpp

#include "PlayerHP.h"
#include "DxLib.h"
#include "../../UI/GameUIManager.h"
#include "../PlayerManager.h"
#include "../PlayerCommon.h"


namespace
{
	
}


CPlayerHP::CPlayerHP()
{
	Init();
}

CPlayerHP::~CPlayerHP()
{

}

//������
void CPlayerHP::Init()
{
	//UI�Ǘ�����
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//����
	hp_ = ui_manager->CreateUI(CGameUIManager::UI_TYPE_HP);
	hp_->Init(PLAYER_HP_POS.x, PLAYER_HP_POS.y);
	hp_->Load("Data/UI/HP/HP.png");
	hp_->SetEndPos(ORIGIN_HP_POS);
}

//�ǂݍ���
void CPlayerHP::Load()
{

}

//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CPlayerHP::Set()
{
	
}

//���t���[���Ăԏ���
void CPlayerHP::Step()
{
	

	//���T�v���C���[��HP��UI�ɓn��
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	hp_->SetSize(player->GetHP());
}


//�`��
void CPlayerHP::Draw()
{
	
}


//�㏈��
void CPlayerHP::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();
}