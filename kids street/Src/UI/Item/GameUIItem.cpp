

#include "GameUIItem.h"
#include "DxLib.h"

namespace
{
	
}

CGameUIItem::CGameUIItem()
	:handle_(0)
	,id_(ITEM_ID_NONE)
{
}

CGameUIItem::~CGameUIItem()
{
}


//������
void CGameUIItem::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//�ǂݍ���
void CGameUIItem::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
	//�����ō��ǂݍ��܂�Ă���A�C�e���̈ʒu����
	//�ʒu��񂩂�m�F����ID���擾
	id_ = CGatherManager::GetInstance()->CheckItemID(posX_);
}

//�X�e�b�v
void CGameUIItem::Step()
{
	
}


//�`��
void CGameUIItem::Draw()
{
	//ID���g���č��`�悵�Ă����̂����m�F����
	if(CGatherManager::GetInstance()->GetIDFlg(id_))
		DrawGraph((int)posX_, (int)posY_, handle_, true);
}


//�폜
void CGameUIItem::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//�㏈��
void CGameUIItem::Fin()
{
	//�摜���폜�ł��ĂȂ��Ȃ�A�폜���Ă�
	if (handle_) {
		Delete();
	}
}