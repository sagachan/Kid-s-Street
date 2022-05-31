#pragma once

#include "Model/Model.h"

//3D�A�j���[�V�����N���X
class CAnim3D :public CModel
{
public:
	CAnim3D();				//�R���X�g���N�^
	virtual ~CAnim3D();		//�f�X�g���N�^

public:
	virtual void Init() override;		//������
	virtual void Update() override;		//�X�V
	virtual void Fin() override;		//�㏈��

public:
	//--------�Q�b�^�[---------------
	float	GetAnimEndFrm() const { return anim_data_.end_frm_; }//�A�j���S�Đ����Ԏ擾
	float	GetAnimFrm() const { return anim_data_.frm_; }		//�A�j���Đ����Ԏ擾
	int		GetAnimID() const { return anim_data_.id_; }		//�Đ����̃A�j��ID�擾�A�A�j�����Đ�����Ă��Ȃ��ꍇ��-1���߂��Ă���
	bool	IsEndAnim()											//�A�j�����I��������
		const { return anim_data_.end_frm_ == anim_data_.frm_ || anim_data_.end_frm_ == 0.f; }
	
	//-------�Z�b�^�[-------------
	void SetAnimFrm(float fFrm) { anim_data_.frm_ = fFrm; }		//�A�j���Đ����Ԑݒ�
	void SetAnimSpd(float fSpd) { anim_data_.spd_ = fSpd; }		//	�A�j�����x�ݒ�
	void SetChangeFlg() { changeFlg_ = true; }					//��ԑJ�ڂ��s��ꂽ�Ƃ���true��


public:
	//�A�j���A�b�v�f�[�g
	//�A�j���X�V�����A����Ă�ł�������
	void UpdateAnim();

	//���[�v�A�j�����N�G�X�g
	//�A�j�����ŏI�t���[���ɂȂ�����ŏ��ɖ߂�܂��B
	void RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);

	//�G���h�A�j�����N�G�X�g
	//�A�j�����ŏI�t���[���ɂȂ����炻�̂܂܂Ŏ~�܂�܂��B
	void RequestEndLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);

	//�p���p
protected:
	int		frm_int_;	//int�^�̃t���[��
	bool	end_animFlg_;
	bool	changeFlg_;	//�A�j���[�V�����ύX���ɕK�v�ȃt���O

public:
	//-------�p���ϐ��֌W�̊֐�----------
	int GetFrmInt() { return frm_int_; }						//int�^�̃t���[�����擾
	bool GetEndAnimFlg() { return end_animFlg_; }				//�A�j�������ݍĐ�����Ă��Ȃ��Ȃ�true
	void ChangeAnim(bool flg) { changeFlg_ = flg; }				//�A�j���[�V�����ύX���s�������ɌĂ�
private:
	typedef struct {
		float	end_frm_;	//�A�j���S�Đ�����
		float	frm_;		//�A�j���Đ�����
		float	spd_;		//�A�j���Đ����x
		int		handle_;	//�A�j���n���h��
		int		id_;		//�Đ����̃A�j��ID
		int		state_;		//�A�j���̏��
	}ANIM_DATA;

	ANIM_DATA	anim_data_;	//�A�j���Đ��֘A�f�[�^

private:
	//���S�ɃA�j�����f�^�b�`
	void DetachAnim();
	//�A�j�����N�G�X�g
	void Request(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
};