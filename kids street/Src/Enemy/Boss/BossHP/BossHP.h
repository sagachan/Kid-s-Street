//BossHP.h
//BossHP�V�[��

#pragma once

#include "../../../UI/UIBase.h"
#include "../../../UI/GameUIManager.h"
//BossHP�N���X
class CBossHP : public CUIBase
{
public:
	CBossHP();
	~CBossHP();

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