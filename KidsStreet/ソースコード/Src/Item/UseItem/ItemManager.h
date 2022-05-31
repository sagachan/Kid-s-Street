//ItemManager.h
//�A�C�e���}�l�[�W���[�N���X

#pragma once

#include "DxLib.h"
#include "ItemBase.h"
#include "../../Library/Input/Input.h"
#include "../../Player/PlayerManager.h"
#include "../../Collision/CollisionManager.h"
#include "../ItemCommon.h"
#include "../../Common.h"
#include "../GatherItem/GatherFactory/GatherBase/GatherBase.h"
#include "../../Library/LibraryCommon.h"



class CItemManager
{
public:
	enum
	{
		FLG_ERASER,
		FLG_PENCIL,
		MAX_ITEM_KIND
	};

	//�{�X���擾�����A�C�e�����̍\����
	struct BossItem
	{
		ITEM_KIND	kind_;					//�{�X�ɂƂ�ꂽ�A�C�e�����
		int			num_;					//�{�X�ɂƂ�ꂽ�A�C�e���ԍ��i�[
	};

private:
	//�N���X�̋K��|�C���^�z����`�F�b�N����Ƃ��Ɏg��
	struct ClassNumInfo
	{
		int initNum_;
		int maxNum_;
	};

public:

	CItemManager();		//�R���X�g���N�^
	~CItemManager();		//�f�X�g���N�^

public:
	//�C���X�^���X����
	static void CreateInstance() { if (!instance_) instance_ = new CItemManager; }
	//�C���X�^���X�擾
	static CItemManager* GetInstance() { return instance_; }
	//�C���X�^���X�폜
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();			//������
	void Load();			//�ǂݍ��݁i���[�h�j
	void Set();				//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Step();			//���t���[���Ăԏ����i����j
	void Update();			//�X�V
	void Draw();			//�`��
	void Delete();			//�폜
	void Fin();				//�㏈��

public:
	void HitUpdate();		//�����蔻��X�V
	void DamageVanish(int num);				//�����蔻�菈�����s�֐�
	
public:
	//�Q�b�^�[
	bool		GetHold()		{ return itemHoldflg_; }	//�v���C���[�̎�Ɏ��Ă邩�ǂ���
	bool		GetActivate()	{ return activate_; }		//�c�肪�܂����邩�ǂ���
	ITEM_KIND	GetItemKind()	{ return itemKind_; }
	bool		IDFromKind(ITEM_ID id);
	int			GetUseNum() { return useNum_; }

	//�Z�b�^�[
	void		SetHold(bool flg)		{ itemHoldflg_ = flg; }			//�A�C�e������Ɏ�������
	void		SetThrowflg(bool flg)	{ throwFlg_ = flg; }			//���������ɌĂ�
	void		SetBossItemPos(VECTOR pos);								//�{�X�ɂƂ�ꂽ�A�C�e���ʒu���W�̃Z�b�g
	void		SetBossItemInfo(int num);
	void		SetBossItemThrow();										//�{�X����ɂ����A�C�e���𓊂��鏈��


private:
	void MinimizeCall(CItemBase* item[], int maxNum, VOID_TYPE type);	//�\���̎Q�Ə����Z�k
	void MinimizeCall(CGatherBase* item[], int maxNum, VOID_TYPE type);	//�\���̎Q�Ə����Z�k
	void SerchItem(CItemBase* item[], ITEM_KIND kind);					//��Ɏ��Ă�A�C�e����T��
	ClassNumInfo CheckItem(ITEM_KIND kind);								//�����ɓ��ꂽ��ނ̃A�C�e����useItem�z���̔ԍ��������Ă���
	void StepInput();		//���͏����֌W
	void StepMove();		//�ړ������֌W
	
private:
	static CItemManager* instance_;	//�C���X�^���X

	CGatherBase*	gatherItem_[ITEM_ID_MAX];			//�A�C�e�����W�N���X
	CItemBase*		useItem_[MAX_ITEM_NUM];				//�A�C�e���g�p�N���X
	
	//�ϐ�
	bool		throwFlg_;					//���ݓ����Ă���A�C�e������ł����邩�ǂ���
	bool		itemHoldflg_;				//��Ɏ����ǂ���
	bool		activate_;					//��ɕt������̂��Ȃ��ꍇ��false�i�c�e���Ȃ��ꍇ��false
	bool		initFlg_;
	int			useNum_;					//���ڂ�\�����邩	

	BossItem	bossItem_;
	ITEM_KIND	itemKind_;					//�A�C�e���̎�ފi�[

};