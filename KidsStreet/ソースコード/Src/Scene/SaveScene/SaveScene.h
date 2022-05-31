//�Z�[�u�f�[�^�Ǘ�
//�O��Q�[�����̈ʒu���W��A�C�e���l���t���O�Ȃǂ�ێ�

#pragma once
#include "DxLib.h"
#include "../../Item/ItemCommon.h"




class CSaveScene
{
public:
	CSaveScene();
	~CSaveScene() {}

public:
	static void CreateInstance() { if (!instance_)instance_ = new CSaveScene; }
	static CSaveScene* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }


public:
	//�Q�b�^�[
	bool* GetItemSaveFlg() { return itemSaveFlg_; }
	bool	GetBossFlg() { return bossFlg_; }

	//�Z�b�^�[
	void	SetItemSaveFlg(bool* flg);
	void	SetBossFlg(bool flg) { bossFlg_ = flg; }

private:
	static CSaveScene* instance_;
	bool itemSaveFlg_[ITEM_MAX_KIND];
	bool bossFlg_;						//false�Ȃ�{�X��ɓ���Ă���
};
