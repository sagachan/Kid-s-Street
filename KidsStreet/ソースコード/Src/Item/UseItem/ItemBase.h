  //�G�l�~�[�p���N���X

#pragma once
#include "DxLib.h"
#include "../../Library/Animation/Animation.h"
#include "../ItemCommon.h"

class CItemBase : public CAnim3D
{
public:
	CItemBase();
	virtual ~CItemBase();

	virtual void Init() = 0;//������
	virtual void Load() = 0;//�ǂݍ���
	virtual void Set() = 0;//�ݒ�
	virtual void Step() = 0;//���t���[���Ăԏ���
	virtual void Draw() = 0;//�`��
	virtual void Update() = 0;//�X�V
	virtual void Delete() = 0;//�폜
	virtual void Fin() = 0;//�㏈��

public:
	void Move();//�ړ��v�Z����

public:
	//�g�p�t���O
	bool GetUseFlg() { return isUse_; }			//�擾
	void SetUseFlg(bool flg) { isUse_ = flg; }	//�Z�b�g

	//�g�p�I�����Ă��邩
	bool GetEndFlg() { return endflg_; }
	void SetEndFlg(bool flg) { endflg_ = flg; }

	//���݈ړ����邩(�g�p����Ă��āA�������I����Ă��Ȃ�)
	bool GetMoveFlg();

	//�_���[�W�擾
	int GetDmg() { return dmg_; }

	//�A�C�e���ԍ��Z�b�g
	void SetItemNum(int num) { itemNum_ = num; }

	//���݃{�X�Ɏ���Ă��邩
	bool GetBossFlg() { return bossFlg_; }
	void SetBossFlg(bool flg) { bossFlg_ = flg; }

	//�{�X�ɓ�����ꂽ�Ƃ��Ƀt���O�𗧂Ă�
	void SetBossThrowFlg(bool flg) { bossThrowFlg_ = flg; }

	//ID�擾
	ITEM_ID GetID() { return id_; }

protected:
	bool	doOnce_;			//��x�����ʂ鏈���p
	bool	isUse_;				//�g�p�t���O
	bool	endflg_;			//�g�p�I���t���O
	bool	appear_flg_;		//���ݑ��݂��Ă��邩�ǂ����̃t���O
	bool	bossFlg_;			//�{�X�ɃA�C�e�����Ƃ��Ă��邩�ǂ���
	bool	bossThrowFlg_;		//�{�X���A�C�e���𓊂��Ă��邩�ǂ���
	bool	bossDoOnce_;		//�{�X�ɃL���b�`����Ă����x�����ʂ鏈��

	int		dmg_;				//�_���[�W��
	int		itemNum_;			//�A�C�e���ԍ�
	float	add_pos_;			//��ԑ��x�̃t���O

	VECTOR	forward_vec_;		//�����x�N�g��
	ITEM_ID id_;
};