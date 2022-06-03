//KidUI.h
//KidUI�V�[��

#pragma once

#include "../../../UI/GameUIManager.h"
#include "../../../UI/UIBase.h"
#include "../../EnemyCommon.h"

//KidUI�N���X
class CKidUI : public CUIBase
{
public:
	CKidUI();
	~CKidUI();
private:
	enum ASSERT_TYPE
	{
		ASSERT_INIT = -1,

		ASSERT_START,
		ASSERT_END,
		ASSERT_FINISH
	};

public:
	
	void Init() override;			//������
	void Load() override;			//�ǂݍ���
	void Set() override;			//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Step() override;			//���t���[���Ăԏ���
	void Draw() override;			//�`��
	void Fin() override;			//�㏈��

public:
	void SetKidFlg(bool flg) { kidFlg_ = flg; }

private:
	bool kidFlg_;
	CGameUI* uiAssert_[ASSERT_FINISH];
	int type_;
};