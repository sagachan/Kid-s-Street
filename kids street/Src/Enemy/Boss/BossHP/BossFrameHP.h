//BossFrameHP.h
//BossFrameHP�V�[��

#pragma once

#include "../../../UI/UIBase.h"

//BossFrameHP�N���X
class CBossFrameHP : public CUIBase
{
public:
	CBossFrameHP();
	~CBossFrameHP();

	
	void Init() override;			//������
	void Load() override;			//�ǂݍ���
	void Set() override;			//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Step() override;			//���t���[���Ăԏ���
	void Draw() override;			//�`��
	void Fin() override;			//�㏈��


};