//PlayerHP.h
//PlayerHP�V�[��

#pragma once

#include "../../UI/UIBase.h"
#include "../../UI/GameUIManager.h"
//PlayerHP�N���X
class CPlayerHP : public CUIBase
{
public:
	CPlayerHP();
	~CPlayerHP();

	//������
	void Init() override;

	//�ǂݍ���
	void Load() override;

	//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Set() override;

	//���t���[���Ăԏ���
	void Step() override;

	//�`��
	void Draw() override;

	//�㏈��
	void Fin() override;

private:
	CGameUI* hp_;
};