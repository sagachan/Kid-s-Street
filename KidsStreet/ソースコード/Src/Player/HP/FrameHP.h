//FrameHP.h
//FrameHP�V�[��

#pragma once

#include "../../UI/UIBase.h"

//FrameHP�N���X
class CFrameHP : public CUIBase
{
public:
	CFrameHP();
	~CFrameHP();

	
	void Init() override;			//������
	void Load() override;			//�ǂݍ���
	void Set() override;			//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Step() override;			//���t���[���Ăԏ���
	void Draw() override;			//�`��
	void Fin() override;			//�㏈��


};