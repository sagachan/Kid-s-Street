//GameUIHP.cpp

#include "GameUIHP.h"
#include "DxLib.h"
#include "../../Player/PlayerCommon.h"

namespace
{
	const int ORIGIN_LENGTH = 100;
}

CGameUIHP::CGameUIHP()
	:handle_(0)
{
}

CGameUIHP::~CGameUIHP()
{
}


//������
void CGameUIHP::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//�ǂݍ���
void CGameUIHP::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
}


//�X�e�b�v
void CGameUIHP::Step()
{
	//HP���m�F���Ă���ɉ����ăo�[�̊g�k���������邱�Ƃ�
	//HP�o�[�Ƃ��Č�����
}

//�`��
void CGameUIHP::Draw()
{
	float endPosX_ = endPos_.x * size_ / 100 + posX_;
	DrawExtendGraph((int)posX_, (int)posY_,
		(int)endPosX_, (int)endPos_.y, handle_,true);
}

//�폜
void CGameUIHP::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//�㏈��
void CGameUIHP::Fin()
{
	//�摜���폜�ł��ĂȂ��Ȃ�A�폜���Ă�
	if (handle_) {
		Delete();
	}
}