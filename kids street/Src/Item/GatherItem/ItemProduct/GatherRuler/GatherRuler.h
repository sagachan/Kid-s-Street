//GatherRuler.h
//GatherRuler�V�[��

#pragma once

#include "../../GatherFactory/GatherBase/GatherBase.h"

//GatherRuler�N���X
class CGatherRuler : public CGatherBase
{
public:
	CGatherRuler() {}
	~CGatherRuler() {}

	
	void Init() override;			//������
	void Load() override {}			//�ǂݍ���
	void Set() override {}			//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Step() override;			//���t���[���Ăԏ���
	void Draw() override {}			//�`��
	void Fin() override {}			//�㏈��

private:
	void Gather();					//�A�C�e�����W�X�V
};