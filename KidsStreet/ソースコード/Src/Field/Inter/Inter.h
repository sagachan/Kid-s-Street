//Inter.h
//�����_�N���X

#pragma once

#include "DxLib.h"
#include "../FieldCommon.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Enemy/EnemyCommon.h"


class CInter
{
public:

public:
	CInter();
	~CInter();

public:
	void Init();
	void Set();
	void Load();
	void Delete();
	void Fin();

public://�����_�֐�
	void InterManager();											//�����_�Ǘ��֐�(�����ǂݍ��߂Ό����_�֐��̂��ׂĂɒʂ�
	void CheckComeInter(VECTOR carPos,int frmNum,int interNum,int carNum);		//�Ԃ������_�ɓ����Ă��邩�ǂ������m�F����A���������Ă���Ȃ�dirInfo�̎g�p�t���O�𗧂Ă�B���̏����͎g�p�t���O�������Ă���Ƃ��͒ʂ�Ȃ�
	void CheckOutInter(VECTOR carPos, int interNum, int carNum);	//�����_����o�鎞�ɒʂ鏈��										//�����_�̊O�ɏo�����Ƃ��m�F���ꂽ�ꍇ�A�g�p�t���O��܂�B�g�p�t���O�������Ă���Ƃ��͂��̏����͒ʂ�Ȃ�
	void JudgeInter(VECTOR carPos, int interNum, int carNum);		//�ǂ̕����ɍs�����𔻒肷��
	int	 CheckInter(bool* inter,int carNum);												//���ݎԂ��ǂ���̌������炫�Ă���̂��𔻒肷�鏈��

public://�擾�A�Z�b�g�֐�
	int GetFrmHndl()				 { return frmHndl_; }			//�n���h�����擾
	float GetInterRad();											//�����_�͈̔͂�Ԃ�����

private:
	InterInfo			interInfo_[INTER_MAX_NUM];						//�����_�^�C�v�\���̔z��

	int					frmHndl_;									//�{�[�����n���h��

	bool				carFlg_[APPEAR_CAR_NUM];					//�Ԃ������_�ɓ����Ă���ꍇ��true
};