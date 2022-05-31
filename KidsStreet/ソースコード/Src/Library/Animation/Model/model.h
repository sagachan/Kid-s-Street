#pragma once
#include <DxLib.h>
#include "../../LibraryCommon.h"



//---------------------------------------------
//	3D���f����1�̕\�����邽�߂̃N���X
//---------------------------------------------
class CModel {
protected:
	VECTOR		pos_;			// ���W
	VECTOR		oldPos_;		// �ړ��O���W
	VECTOR		rot_;			// ��]�p�x
	VECTOR		oldRot_;
	VECTOR		scale_;			// �g��k����
	VECTOR		move_;
	float		rad_;			// ���a
	int			hndl_;			// ���f���n���h��
	int			colNum_;		//�����蔻��ԍ��i�[�ϐ�
	COL_DATA	colData_;			//�����蔻��\����

public:
	CModel();
	virtual ~CModel();

	//		������
	virtual void	Init(void);
	//		�I������
	virtual void	Fin(void);
	//		���l�̍X�V����
	virtual void	Update(void);
	//		���f���`��
	virtual void	Draw(void);



	//***************************************
	//		�摜�ǂݍ��݊֘A
	//***************************************
	//		���f���ʏ탍�[�h
	//	fileName	:	�ǂݍ��݂������f���f�[�^��
	bool	LoadModel(const char* fileName);
	//		���f���R�s�[���[�h
	//	@memo		:	���łɓǂݍ���ł��郂�f���𕡐��\���������ꍇ�Ɏg�p���܂��B
	//	srcHndl	:	�ǂݍ��݂������f���̃n���h��
	bool	DuplicateModel(int srcHndl);
	//		���f���f�[�^�폜
	void	DeleteModel(void);


	//�Q�b�^�[�B
	inline int		GetHandle(void) { return hndl_; }				//�n���h��
	inline VECTOR	GetPosition(void) { return pos_; }				//���f���̍��W
	inline VECTOR	GetOldPosition(void) { return oldPos_; }		//���f���̑O���[�v���W
	inline VECTOR	GetOldRotation(void) { return oldRot_; }		//���f���̑O���[�v��]�l
	inline VECTOR	GetScale(void) { return scale_; }				//���f���̃X�P�[��
	inline VECTOR	GetRot(void) { return rot_; }					//���f���̉�]
	inline VECTOR	GetMove(void) { return move_; }					//���f���̈ړ��l
	inline float	GetRad(void) { return rad_; }					//���f���̔��a

	//�ݒ�
	//���݂̈ʒu
	inline void	SetPosition(const VECTOR& pos) { pos_ = pos; }
	//���݂̃T�C�Y
	inline void	SetScale(const VECTOR& scale) { scale_ = scale; }
	inline void	SetScale(float scale) { scale_.x = scale_.y = scale_.z = scale; }
	//���݂̊p�x
	inline void	SetRot(const VECTOR& rot) { rot_ = rot; }
};

