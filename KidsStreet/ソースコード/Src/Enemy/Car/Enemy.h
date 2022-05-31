//Enemy.h
//�G�l�~�[�N���X

#pragma once

#include "DxLib.h"
#include "../../Scene/PlayScene.h"
#include "../EnemyBase.h"
#include "../EnemyCommon.h"
#include "../../Field/FieldManager.h"


class CEnemy : public CEnemyBase
{

public:
	CEnemy();				//�R���X�g���N�^
	~CEnemy();				//�f�X�g���N�^

public:
	void Init();			//������
	void Load();			//�ǂݍ��݁i���[�h�j
	void Set();
	void Step();			//���t���[���Ăԏ����i����j
	void Update();			//�X�V
	void Draw();			//�`��
	void Delete();			//�폜
	void Fin();				//�㏈��
	void Hit();

public:
	void InterMove();		//�����_�ɓ������Ƃ��ɒʂ铮�쏈��
	void CheckColCube();
	CEnemy* Clone();		//�N���[��

public:
	void	Move(int dir);																			//�G�̈ړ�����
	bool	AddDamage(VECTOR pos1, VECTOR pos2);													//�_���[�W���菈��
	
	
public:
	//�Q�b�^�[
	bool	GetInterFlg()	{ return interInfo_.flg_; }												//�����_�����J�n�t���O�擾
	int		GetInterNum()	{ return interInfo_.interNum_; }
	bool	GetMoveFlg()	{ return moveFlg_; }

public:
	//�Z�b�^�[
	void	SetInterFlg(bool flg) { interInfo_.flg_ = flg; }										//�����_�J�n�����t���O�Z�b�g
	void	SetInterDir(int num, VECTOR pos) { interInfo_.check_ = num; interInfo_.pos_ = pos; }	//�����Ƃ��Č����_�̕����ԍ����󂯎��A�Ԃ̐i�ޕ������Z�b�g����
	void	SetPos(VECTOR pos, CEnemyBase::MOVE_DIR dir);				//�����l�ݒ�
	void	SetInterInfo(int interDir, VECTOR pos) { interInfo_.check_ = interDir; interInfo_.pos_ = pos; }									//�����_�ϐ��Z�b�g
	void	SetJustInter(int justNum) { interInfo_.just_ = justNum; }
	void	SetInterNum(int num) { interInfo_.interNum_ = num; }
	void	SetEndInter(bool flg) { interInfo_.endFlg_ = flg; }
	void	SetMoveFlg(bool flg) { moveFlg_ = flg; }

public:
	struct InterInfo
	{
		bool		flg_;						//�����_�ł̏������J�n����Ă��邩
		bool		endFlg_;					//�����_�������I�����Ă���ꍇ��true
		int			interNum_;					//�Ȃ���Ƃ��͌����_�ԍ����Ԃ��Ƃɕۑ�����
		int			check_;						//���̐��l�����Ƃɐi�ޕ��������߂�
		int			just_;						//�����݂ǂ̊p�x��������_�ɓ����Ă��邩(0����3�܂ł̐��l�Ŕ��f
		VECTOR		pos_;						//�����_�ʒu���

	};

private:
	
	bool		moveFlg_;						//true�Ȃ�ړ��\
	InterInfo	interInfo_;						//�����_�������
	MOVE_DIR	dir_;							//�G�l�~�[����


public:
	//�G���[�`�F�b�N����������
	InterInfo GetInterInfo() { return interInfo_; }
};