//GameUISprite.cpp
//UI�X�v���C�g�N���X

#include "GameUISprite.h"
#include "DxLib.h"

CGameUISprite::CGameUISprite()
	:handle_(0)
{
}

CGameUISprite::~CGameUISprite()
{
}


//������
void CGameUISprite::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//�ǂݍ���
void CGameUISprite::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
}


//�X�e�b�v
void CGameUISprite::Step()
{
	//�X�v���C�g�̍X�V����
}


//�`��
void CGameUISprite::Draw()
{
	DrawGraph((int)posX_, (int)posY_, handle_, true);
}


//�폜
void CGameUISprite::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//�㏈��
void CGameUISprite::Fin()
{
	//�摜���폜�ł��ĂȂ��Ȃ�A�폜���Ă�
	if (handle_) {
		Delete();
	}
}