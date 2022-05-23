//PlayCamera.cpp
//�v���C�V�[���ł̃J����

#include "PlayCamera.h"
#include <math.h>
#include "../Library/MyMath/MyMath.h"
#include "../Library/Input/Input.h"
#include "../Library/Input/Pad/Pad.h"

//�J�����֘A
#define CAMERA_OFFSET_Z			(-12.0f)		//�J�����̒����_����̎�O�I�t�Z�b�g�l
#define CAMERA_LOOK_OFFSET_Y	(4.0f)		//�J�����̒����_�̍����I�t�Z�b�g
#define CAMERA_ROT_SPEED		(0.052f)	//�J�����̉�]���x

namespace
{
	//�J�����̉�]�X�s�[�h
	const float PLAY_CAMERA_ROTATION = (2.0f * DX_PI_F / 180.0f);
	//�J�����̉�]�l�ő�
	const float PLAY_CAMERA_ROTATION_MAX = (2.0f * DX_PI_F);
	//�J������X��]�l�ő�
	const float PLAY_CAMERA_ROTATION_MAX_X = (20.0f * 2.0f * DX_PI_F / 180.0f);
	//�J������X��]�l�ŏ�
	const float PLAY_CAMERA_ROTATION_MIN_X = (-10.0f * 2.0f * DX_PI_F / 180.0f);

	//�J�����̃T�C�Y
	const float PLAY_CAMERA_SIZE_H = 1.0f;
	const float PLAY_CAMERA_SIZE_W = 1.0f;
	const float PLAY_CAMERA_SIZE_D = 1.0f;
	const float PLAY_CAMERA_SIZE_R = 1.0f;
}

//�R���X�g���N�^
CPlayCamera::CPlayCamera()
	:cameraInfo_({0})
	,oldPos_({ 0.0f })
	, forward_({ 0.0f })
{
	
}

//�f�X�g���N�^
CPlayCamera::~CPlayCamera()
{
}

//�������i��������j
void CPlayCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//��������Ȃ�ݒ肷��
	cameraInfo_.pos_ = pos;
	cameraInfo_.look_ = look;
	cameraInfo_.up_ = up;
}


//���t���[���Ăԏ����i����j
void CPlayCamera::Step()
{
	//�O��ʒu���W��ۊ�
	oldPos_ = cameraInfo_.pos_;
	oldRot_.x = cameraInfo_.fRotX_;
	oldRot_.y = cameraInfo_.fRotY_;
	
	//�v���C���[�̏����擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//���͑���N���X�擾
	CInput* input = CInput::GetInstance();

	VECTOR player_rot = player->GetRot();	//��]�l���擾
	VECTOR player_pos = player->GetPosition();	//���W���擾

	
	//----------------------------
	// �J�����̒����_
	//----------------------------
	cameraInfo_.look_ = player->GetPosition();
	cameraInfo_.look_.y = player->GetPosition().y + CAMERA_LOOK_OFFSET_Y;	//�v���C���[�̏����������
	

	//�X�e�B�b�N�̒l���擾
	float stick_x = input->GetStickValue(RIGHT_STICK_X);
	float stick_y = input->GetStickValue(RIGHT_STICK_Y);

	// X����]
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_UP)) {
		cameraInfo_.fRotX_ += CAMERA_ROT_SPEED;
		if (cameraInfo_.fRotX_ > 2.0f * DX_PI_F)cameraInfo_.fRotX_ -= 2.0f * DX_PI_F;
	}
	else if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_DOWN)) {
		cameraInfo_.fRotX_ -= CAMERA_ROT_SPEED;
		if (cameraInfo_.fRotX_ < 0)cameraInfo_.fRotX_ += 2.0f * DX_PI_F;
	}

	// Y����]
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_LEFT)) {
		cameraInfo_.fRotY_ -= CAMERA_ROT_SPEED;
		VECTOR rot = player->GetRot();
		rot.y -= CAMERA_ROT_SPEED;
		player->SetRot(rot);

		if (cameraInfo_.fRotY_ < 0)
		{
			cameraInfo_.fRotY_ += 2.0f * DX_PI_F;
		}

	}
	else if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_RIGHT)) {

		cameraInfo_.fRotY_ += CAMERA_ROT_SPEED;
		VECTOR rot = player->GetRot();
		rot.y += CAMERA_ROT_SPEED;
		player->SetRot(rot);

		if (cameraInfo_.fRotY_ > 2.0f * DX_PI_F)
		{
			cameraInfo_.fRotY_ -= 2.0f * DX_PI_F;
			
		}
	}

	// �����_�����_�ɕ��s�ړ�����s����쐬
	MATRIX origin_look_mat =
		CMyMath::GetTranslateMatrix(VGet(-cameraInfo_.look_.x, -cameraInfo_.look_.y, -cameraInfo_.look_.z));

	//�J�����𒍎��_����O�Ɉړ������镽�s�ړ��s����쐬
	MATRIX fore_look_mat =
		CMyMath::GetTranslateMatrix(VGet(0.0f, 0.0f, CAMERA_OFFSET_Z));

	//�J������X����]�s����쐬
	MATRIX pitch_mat = CMyMath::GetPitchMatrix(cameraInfo_.fRotX_);

	//�J������Y����]�s����쐬
	MATRIX yaw_mat = CMyMath::GetYawMatrix(cameraInfo_.fRotY_);

	// �����_�����̈ʒu�ɕ��s�ړ�����s����쐬
	MATRIX default_look_mat = CMyMath::GetTranslateMatrix(cameraInfo_.look_);

	//�e�s��������i�|���Z�̏��Ԃɒ��ӁI�I�j
	MATRIX mult_mat = CMyMath::MatMult(default_look_mat, yaw_mat);
	mult_mat = CMyMath::MatMult(mult_mat, pitch_mat);
	mult_mat = CMyMath::MatMult(mult_mat, fore_look_mat);
	mult_mat = CMyMath::MatMult(mult_mat, origin_look_mat);

	//�����_�ɍs����|���ăJ�����̍��W���Z�o
	cameraInfo_.pos_ = CMyMath::MatTransform(mult_mat, cameraInfo_.look_);

	//�O�̍��W���獡�̍��W�ւ̌����x�N�g�������߂�
	VECTOR rot = CMyMath::GetRot(oldPos_, cameraInfo_.pos_);
	//�����x�N�g�������߂�
	forward_.x = sinf(rot.y);
	forward_.z = cosf(rot.y);
	
}


//�J�������̍X�V����
void CPlayCamera::Update()
{
	//�J�����̎��_�i���W�j�E�����_�E�A�b�v�x�N�g���ݒ�
	SetCameraPositionAndTargetAndUpVec(cameraInfo_.pos_, cameraInfo_.look_, cameraInfo_.up_);
}


//�㏈��
void CPlayCamera::Fin()
{
}

void CPlayCamera::HitSet()
{
	cameraInfo_.pos_ = oldPos_;
	cameraInfo_.fRotX_ = oldRot_.x;
	cameraInfo_.fRotY_ = oldRot_.y;

	//�v���C���[�̏����擾
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	player->SetRot(player->GetOldRotation());
}