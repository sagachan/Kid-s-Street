

#include "GameUIItemBox.h"
#include "../../Item/UseItem/ItemManager.h"
#include "../../Item/GatherItem/GatherFactory/GatherManager.h"

namespace
{
	
}


CGameUIItemBox::CGameUIItemBox()
	:handle_(0)
	,id_(ITEM_ID_NONE)
{
}

CGameUIItemBox::~CGameUIItemBox()
{
}


//������
void CGameUIItemBox::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//�ǂݍ���
void CGameUIItemBox::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
	//�����ō��ǂݍ��܂�Ă���A�C�e���̈ʒu����
	//�ʒu��񂩂�m�F����ID���擾
	id_ = CGatherManager::GetInstance()->CheckItemID(posX_);
}


//�X�e�b�v
void CGameUIItemBox::Step()
{
	
}


//�`��
void CGameUIItemBox::Draw()
{
	//ID���g���č��`�悵�Ă����̂����m�F����
	if(CItemManager::GetInstance()->IDFromKind(id_))
		DrawGraph((int)posX_, (int)posY_, handle_, true);
}


//�폜
void CGameUIItemBox::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//�㏈��
void CGameUIItemBox::Fin()
{
	//�摜���폜�ł��ĂȂ��Ȃ�A�폜���Ă�
	if (handle_) {
		Delete();
	}
}