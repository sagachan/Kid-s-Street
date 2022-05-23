//BossFrameHP.cpp

#include "BossFrameHP.h"
#include "DxLib.h"
#include "../../../UI/GameUIManager.h"


namespace
{

}


CBossFrameHP::CBossFrameHP()
{
	Init();
}

CBossFrameHP::~CBossFrameHP()
{

}

//������
void CBossFrameHP::Init()
{
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//����
	CGameUI* hp = ui_manager->CreateUI(CGameUIManager::UI_TYPE_BUTTON);
	hp->Init(10.0f, 20.0f);
	hp->Load("Data/UI/HP/FrameHP.png");
}

//�ǂݍ���
void CBossFrameHP::Load()
{

}

//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CBossFrameHP::Set()
{

}

//���t���[���Ăԏ���
void CBossFrameHP::Step()
{

	//UI�Ǘ��X�e�b�v
	CGameUIManager::GetInstance()->Step();
}


//�`��
void CBossFrameHP::Draw()
{
	
}


//�㏈��
void CBossFrameHP::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();

}