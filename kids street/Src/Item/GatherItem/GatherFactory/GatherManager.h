//GatherManager.h
//UI�Ǘ��p�N���X

#pragma once

#include "GatherBase/GatherItem.h"
#include "../../ItemCommon.h"
#include <vector>

//�A�C�e�����W�Ǘ��p�N���X
class CGatherManager
{
public:
	enum GATHER_TYPE
	{
		BOSS_ONLY_ITEM
	};

public:
	CGatherManager();
	~CGatherManager();

public:
	static void CreateInstance() { if (!instance_) instance_ = new CGatherManager; }
	static CGatherManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

public:
	void Step();						//�X�e�b�v
	void Draw();						//�`��
	void DeleteAll();					//�폜

public:
	CGatherItem* CreateItem(GATHER_TYPE type);	//�A�C�e���̐���
	void GatherItem(ITEM_KIND kind);			//�A�C�e�����W�߂�ꂽ�Ƃ��ɒʂ�
	ITEM_ID CheckItemID(float posX);			//UI�����ID�Q�b�g
	ITEM_ID CheckItemID(VECTOR pos);			//�t�B�[���h��̃A�C�e����ID�Q�b�g
	bool GetIDFlg(ITEM_ID id);
	

public:
	//�Q�b�^�[
	bool* GetGatherItem() { return gatherItemFlg_; }

private:
	static CGatherManager* instance_;
	bool gatherItemFlg_[ITEM_MAX_KIND];			//�A�C�e�����W�߂����true�ɂȂ�


	//����A�ǂ�ǂ�A�C�e���������Ă����v�Ȃ悤��
	//���I�z��Ƃ��Đ錾
	std::vector<CGatherItem*> item_vec_;
};