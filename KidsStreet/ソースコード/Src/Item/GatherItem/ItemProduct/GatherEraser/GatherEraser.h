//GatherEraser.h
//GatherEraser�V�[��

#pragma once

#include "../../GatherFactory/GatherBase/GatherBase.h"

//GatherEraser�N���X
class CGatherEraser : public CGatherBase
{
public:
	CGatherEraser() {}
	~CGatherEraser() {}

	
	void Init() override;			//������
	void Load() override {}			//�ǂݍ���
	void Set() override {}			//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Step() override;			//���t���[���Ăԏ���
	void Draw() override {}			//�`��
	void Fin() override {}			//�㏈��

private:
	void Gather();					//�A�C�e�����W�X�V

	
};