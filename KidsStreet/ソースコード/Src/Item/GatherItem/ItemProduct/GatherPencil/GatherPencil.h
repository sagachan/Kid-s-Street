//GatherPencil.h
//GatherPencil�V�[��

#pragma once

#include "../../GatherFactory/GatherBase/GatherBase.h"

//GatherPencil�N���X
class CGatherPencil : public CGatherBase
{
public:
	CGatherPencil() {}
	~CGatherPencil() {}

	
	void Init() override;			//������
	void Load() override {}			//�ǂݍ���
	void Set() override {}			//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Step() override;			//���t���[���Ăԏ���
	void Draw() override {}			//�`��
	void Fin() override {}			//�㏈��

private:
	void Gather();					//�A�C�e�����W�X�V
};