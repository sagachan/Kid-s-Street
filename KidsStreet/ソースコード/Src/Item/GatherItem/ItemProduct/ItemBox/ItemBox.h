//ItemBox.h
//ItemBox�V�[��

#pragma once

#include "../../GatherFactory/GatherBase/GatherBase.h"

//ItemBox�N���X
class CItemBox : public CGatherBase
{
public:
	CItemBox() {}
	~CItemBox() {}

	
	void Init() override;			//������
	void Load() override {}			//�ǂݍ���
	void Set() override {}			//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Step() override {}			//���t���[���Ăԏ���
	void Draw() override {}			//�`��
	void Fin() override {}			//�㏈��
};