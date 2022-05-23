#pragma once
#include <DxLib.h>



//---------------------------------------------
//	3D���f����1�̕\�����邽�߂̃N���X
//---------------------------------------------
class CModel {
protected:
	VECTOR	pos_;			// ���W
	VECTOR  m_old_pos_;		// �ړ��O���W
	VECTOR	m_rot_;			// ��]�p�x
	VECTOR	m_scale_;		// �g��k����
	float	m_rad_;			// ���a
	int		m_hndl_;		// ���f���n���h��


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
	inline int		GetHandle(void) { return m_hndl_; }				//�n���h��
	inline VECTOR	GetPosition(void) { return pos_; }			//���f���̍��W
	inline VECTOR	GetOldPosition(void) { return m_old_pos_; }		//���f���̑O���[�v���W
	inline VECTOR	GetScale(void) { return m_scale_; }				//���f���̃X�P�[��
	inline VECTOR	GetRot(void) { return m_rot_; }					//���f���̉�]
	inline float	GetRad(void) { return m_rad_; }					//���f���̔��a

	//�ݒ�
	//���݂̈ʒu
	inline void	SetPosition(const VECTOR& pos) { pos_ = pos; }
	//���݂̃T�C�Y
	inline void	SetScale(const VECTOR& scale) { m_scale_ = scale; }
	inline void	SetScale(float scale) { m_scale_.x = m_scale_.y = m_scale_.z = scale; }
	//���݂̊p�x
	inline void	SetRot(const VECTOR& rot) { m_rot_ = rot; }
};

