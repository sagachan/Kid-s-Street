//PlayCamera.h
//�v���C�V�[���ł̃J����

#pragma once

#include "DxLib.h"
#include "../Player/PlayerManager.h"

class CPlayCamera
{
	
public:
	CPlayCamera();	//�R���X�g���N�^
	~CPlayCamera();	//�f�X�g���N�^

public:
	//������
	void Init(){}
	void Init(VECTOR pos, VECTOR look, VECTOR up);

	//���t���[���Ăԏ����i����j
	void Step();

	//�J�������̍X�V����
	void Update();

	//�㏈��
	void Fin();

	
public:
	//�Q�b�^�[
	VECTOR GetPos() { return cameraInfo_.pos_; }			//���W�擾
	VECTOR GetLook() { return cameraInfo_.look_; }			//�����_�擾
	VECTOR GetOldPos() { return oldPos_; }					//�O�̍��W�擾

	//�Z�b�^�[
	void SetPos(VECTOR pos) { cameraInfo_.pos_ = pos; }

private:

	//�J�������
	struct CameraInfo
	{
		VECTOR	pos_;		//���_
		VECTOR	look_;		//�����_
		VECTOR	up_;			//�A�b�v�x�N�g��
		float fRotX_;		//�����p�x(X���p�x)
		float fRotY_;		//�����p�x(Y���p�x)
	};
	VECTOR oldPos_;
	VECTOR oldRot_;
	CameraInfo cameraInfo_;
};