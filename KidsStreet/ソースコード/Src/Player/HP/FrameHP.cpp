//FrameHP.cpp

#include "FrameHP.h"
#include "DxLib.h"
#include "../../UI/GameUIManager.h"


namespace
{

}


CFrameHP::CFrameHP()
{
	Init();
}

CFrameHP::~CFrameHP()
{

}

//������
void CFrameHP::Init()
{
	//UI�Ǘ�����
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//����
	CGameUI* frame = ui_manager->CreateUI(CGameUIManager::UI_TYPE_BUTTON);
	frame->Init(700.0f, 650.0f);
	frame->Load("Data/UI/HP/FrameHP.png");
	
}

//�ǂݍ���
void CFrameHP::Load()
{

}

//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CFrameHP::Set()
{

}

//���t���[���Ăԏ���
void CFrameHP::Step()
{

	//UI�Ǘ��X�e�b�v
	CGameUIManager::GetInstance()->Step();
}


//�`��
void CFrameHP::Draw()
{
	
}


//�㏈��
void CFrameHP::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();

}