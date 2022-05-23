  //�G�l�~�[�p���N���X

#pragma once
#include "DxLib.h"
#include "../Animation/Animation.h"

class CItemBase : public CAnim3D
{
public:
	CItemBase();
	virtual ~CItemBase();

	//������
	virtual void Init() = 0;
	//�ǂݍ���
	virtual void Load() = 0;
	//�ݒ�
	virtual void Set() = 0;
	//���t���[���Ăԏ���
	virtual void Step() = 0;
	//�ړ��v�Z����
	virtual void Move() = 0;
	//�`��
	virtual void Draw() = 0;
	//�X�V
	virtual void Update() = 0;
	//�폜
	virtual void Delete() = 0;
	//�㏈��
	virtual void Fin() = 0;

	//�����蔻��p
	virtual VECTOR	GetHit() = 0;
	virtual float	GetSimpleHit() = 0;

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

	//���݃{�X�Ɏ���Ă��邩
	bool GetBossFlg() { return bossFlg_; }
	void SetBossFlg(bool flg) { bossFlg_ = flg; }

	//�{�X�ɓ�����ꂽ�Ƃ��Ƀt���O�𗧂Ă�
	void SetBossThrowFlg(bool flg) { bossThrowFlg_ = flg; }

protected:
	bool	doOnce_;			//��x�����ʂ鏈���p
	bool	isUse_;				//�g�p�t���O
	bool	endflg_;			//�g�p�I���t���O
	int		dmg_;				//�_���[�W��
	float	radius_;			//�ȈՓ����蔻��
	VECTOR	hit_radius_;		//������͈͂̍L��
	bool	appear_flg_;		//���ݑ��݂��Ă��邩�ǂ����̃t���O
	float	add_pos_;			//��ԑ��x�̃t���O
	VECTOR	forward_vec_;		//�����x�N�g��
	int		add_num_;			//���Z��
	bool	bossFlg_;			//�{�X�ɃA�C�e�����Ƃ��Ă��邩�ǂ���
	bool	bossThrowFlg_;		//�{�X���A�C�e���𓊂��Ă��邩�ǂ���
	bool	bossDoOnce_;		//�{�X�ɃL���b�`����Ă����x�����ʂ鏈��
};