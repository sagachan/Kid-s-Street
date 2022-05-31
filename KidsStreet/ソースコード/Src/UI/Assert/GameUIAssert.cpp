//GameUIAssert.cpp

#include "GameUIAssert.h"
#include "DxLib.h"
#include "../../Player/PlayerCommon.h"

namespace
{
}

CGameUIAssert::CGameUIAssert()
	:handle_(0)
{
}

CGameUIAssert::~CGameUIAssert()
{
}


//������
void CGameUIAssert::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//�ǂݍ���
void CGameUIAssert::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
}


//�X�e�b�v
void CGameUIAssert::Step()
{
	
}

//�`��
void CGameUIAssert::Draw()
{
	if(drawFlg_)
	DrawGraph((int)posX_, (int)posY_, handle_, true);
}

//�폜
void CGameUIAssert::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//�㏈��
void CGameUIAssert::Fin()
{
	//�摜���폜�ł��ĂȂ��Ȃ�A�폜���Ă�
	if (handle_) {
		Delete();
	}
}