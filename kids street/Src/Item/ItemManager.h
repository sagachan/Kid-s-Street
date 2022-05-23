//ItemManager.h
//�A�C�e���}�l�[�W���[�N���X

#pragma once

#include "DxLib.h"
#include "ItemBase.h"
#include "Eraser/Eraser.h"
#include "Pencil/Pencil.h"
#include "../Input/Input.h"
#include "../Player/PlayerManager.h"
#include "../Collision/CollisionManager.h"
#include "ItemCommon.h"
#include "../Common.h"


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
	void StepInput();		//���͏����֌W
	void StepMove();		//�ړ������֌W
	void HitUpdate();		//�����蔻��X�V
	void DamageVanish(int num, ITEM_KIND kind);							//�����蔻�菈�����s�֐�
	void SetBossItemPos(VECTOR pos);										//�{�X�ɂƂ�ꂽ�A�C�e���ʒu���W�̃Z�b�g
	void SetBossItemInfo(ITEM_KIND kind, int num);
	void SetBossItemThrow();											//�{�X����ɂ����A�C�e���𓊂��鏈��

public:
	CItemBase*	GetEraser() {  return *itemEraser_; }
	CItemBase*	GetPencil() {  return *itemPencil_; }
	bool		GetHold() { return itemHoldflg_; }				//�v���C���[����Ɏ����Ă��鏈��
	void		SetAppear(bool flg) { appearFlg_ = flg; }		//�A�C�e�����o��������
	bool		GetAppear() { return appearFlg_; }				//�A�C�e�������ݎg�p�\���ǂ���
	void		SetHold(bool flg) { itemHoldflg_ = flg; }		//�A�C�e������Ɏ�������
	bool		GetActivate() { return activate_; }				//�c�肪�܂����邩�ǂ���
	void		SetThrowflg(bool flg) { throwFlg_ = flg; }		//���������ɌĂ�
			

private:
	void MinimizeCall(CItemBase* item[], int maxNum, VOID_TYPE type);	//�\���̎Q�Ə����Z�k

private:
	static CItemManager* instance_;	//�C���X�^���X

	//�����S��
	CItemBase* itemEraser_[MAX_ERASER];				//���|�C���^
	CEraser eraser_;									//�����S���N���X

	//���M
	CItemBase* itemPencil_[MAX_PENCIL];				//���|�C���^
	CPencil pencil_;									//���M�N���X
	
	//�ϐ�
	bool		appearFlg_;					//�o�������邩�ǂ���
	bool		throwFlg_;					//���ݓ����Ă���A�C�e������ł����邩�ǂ���
	bool		itemFlg_;					//���ݑI�΂�Ă���A�C�e�����ǂ���
	bool		itemHoldflg_;				//��Ɏ����ǂ���
	int			itemNum_;					//�A�C�e���ԍ��i�[
	ITEM_KIND	itemKind_;					//�A�C�e���̎�ފi�[
	bool		pr_itemFlg_[MAX_ITEM_KIND];	//�A�C�e���̎�ޕ��̃t���O��p�ӂ���(�������x���グ�邽��)
	int			dmg_;						//�A�C�e���̃_���[�W
	bool		activate_;					//��ɕt������̂��Ȃ��ꍇ��false�i�c�e���Ȃ��ꍇ��false
	int			useNum_;					//���ڂ�\�����邩		
	BossItem	bossItem_;

	//�����蔻��p
	int			maxNum_;					//�����蔻����󂯓n���̎��Ɏg�����I�z��̊i�[�����i�[
};