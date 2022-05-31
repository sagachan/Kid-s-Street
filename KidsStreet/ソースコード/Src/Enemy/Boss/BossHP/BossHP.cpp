//BossHP.cpp

#include "BossHP.h"
#include "DxLib.h"
#include "../../../UI/GameUIManager.h"
#include "../../EnemyManager.h"
#include "../../EnemyCommon.h"


namespace
{
	const float UI_posX = 10.0f;
	const float UI_posY = 25.0f;
}


CBossHP::CBossHP()
{
	Init();
}

CBossHP::~CBossHP()
{

}

//������
void CBossHP::Init()
{
	//UI�Ǘ�����
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//�w�i����
	hp_ = ui_manager->CreateUI(CGameUIManager::UI_TYPE_HP);
	hp_->Init(BOSS_HP_POS.x, BOSS_HP_POS.y);
	hp_->Load("Data/UI/HP/BossHP.png");
	hp_->SetEndPos(BOSS_HP_END_POS);
}

//�ǂݍ���
void CBossHP::Load()
{

}

//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CBossHP::Set()
{
	
}

//���t���[���Ăԏ���
void CBossHP::Step()
{
	//���THP��UI�ɓn��
	CBoss* boss = CEnemyManager::GetInstance()->GetBoss();
	hp_->SetSize(boss->GetHP());
}


//�`��
void CBossHP::Draw()
{
	
}


//�㏈��
void CBossHP::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();
}