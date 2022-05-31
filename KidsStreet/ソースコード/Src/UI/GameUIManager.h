//GameUIManager.h
//UI�Ǘ��p�N���X

#pragma once

#include "UIBase.h"
#include "HP/GameUIHP.h"
#include <vector>
#include "../Library/LibraryCommon.h"
#include "../Item/ItemCommon.h"

//UI�Ǘ��p�N���X
class CGameUIManager
{
public:
	enum UI_TYPE
	{
		UI_TYPE_SPRITE,		//�w�i���ʑS�̕\��
		UI_TYPE_BUTTON,		//��������g�ݍ��킹��ʂ̕�
		UI_TYPE_HP,			//HP�o�[
		UI_TYPE_ITEM,		//�r���\������A�C�e��
		UI_TYPE_ITEMBOX,	//�A�C�e���{�b�N�X
		UI_TYPE_ASSERT		//�O������̕`��t���O�Q�Ƃɂ���ĕ`���؂�ւ���UI
	};

public:
	CGameUIManager();
	~CGameUIManager();

public:
	static void CreateInstance() { if (!instance_) instance_ = new CGameUIManager; }
	static CGameUIManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

public:
	CGameUI* CreateUI(UI_TYPE type);	//UI�̐���
	void Step();						//�X�e�b�v
	void Draw();						//�`��
	void DeleteUI(ITEM_ID id);					//UI��I���폜
	void DeleteAll();					//UI�̍폜
	void MinimizeCall(CUIBase* ui[], int max, VOID_TYPE type);

public:
	//�Q�b�^�[
	bool GetInputFlg() { return inputFlg_; }
	//�Z�b�^�[
	void SetInputFlg(bool flg) { inputFlg_ = flg; }

	void SetBossFlg(bool flg);

private:
	static CGameUIManager* instance_;

	//UI����ʕ\������Ă��ăv���C���[�Ȃǂ̓��͏�������
	//UI��ǂ܂�����g�킹���肷�邱�Ƃ�D�悳�������Ƃ��Ɏg��
	bool inputFlg_;						

	//����A�ǂ�ǂ�UI�������Ă����v�Ȃ悤��
	//���I�z��Ƃ��Đ錾
	std::vector<CGameUI*> ui_vec_;

};