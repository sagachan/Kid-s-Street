//GameUIButton.cpp
//UI�{�^���N���X

#include "GameUIButton.h"
#include "DxLib.h"

CGameUIButton::CGameUIButton()
	:handle_(0)
{
}

CGameUIButton::~CGameUIButton()
{
}


//������
void CGameUIButton::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//�ǂݍ���
void CGameUIButton::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
}


//�X�e�b�v
void CGameUIButton::Step()
{
	//�{�^���̍X�V����
}


//�`��
void CGameUIButton::Draw()
{
	if (!drawFlg_)
	{
		DrawGraph((int)posX_, (int)posY_, handle_, true);
	}
}
	


//�폜
void CGameUIButton::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//�㏈��
void CGameUIButton::Fin()
{
	//�摜���폜�ł��ĂȂ��Ȃ�A�폜���Ă�
	if (handle_) {
		Delete();
	}
}