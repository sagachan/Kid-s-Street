//Player.h
//�v���C���[�N���X

#pragma once

#include "DxLib.h"
#include "../Library/Animation/Animation.h"

#define HAND_FRAME_NUM (12)

class CPlayer : public CAnim3D
{
private:

	enum PLAYER_ANIM_STATE
	{
		PLAYER_INIT,
		PLAYER_STAND,
		PLAYER_WALK,
		PLAYER_RUN,
		PLAYER_JUMP,
		PLAYER_THROW,
		PLAYER_RELOAD,
		PLAYER_ATTACK
	};

	enum PLAYER_ANIM_NO
	{
		INIT,
		ATTACK,
		RUN,
		THROW,
		ARMATURE,
		JUMP,
		STAND,
		WALK,
		RELOAD,
		ANIM_MAX_NUM
	};

public:
	CPlayer();		//�R���X�g���N�^
	~CPlayer();		//�f�X�g���N�^

public:
	void Init();			//������
	void Load();			//�ǂݍ��݁i���[�h�j
	void Set();				//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void HitSet(bool flg);	//�����蔻��p�֐��t���O�Ǘ��֐�
	void HitSet();			//�����蔻��p�֐��Aoldpos�ɖ߂�
	void Hit();				//�����蔻����܂Ƃ߂��֐�
	void Step();			//���t���[���Ăԏ����i����j
	void Update();			//�X�V
	void Draw();			//�`��
	void Delete();			//�폜
	void Fin();				//�㏈��

public:
	void StepInput();							//���̓X�e�b�v
	void StatesSet();							//�A�j���[�V������ԑJ��
	void AddDamage(int dmg);					//�v���C���[�̗̑͂����炷

	//�Q�b�^�[
public:
	VECTOR	GetForwardVec() { return forward_; }
	VECTOR	GetPlayerHandPos()
	{return MV1GetFramePosition(hndl_, HAND_FRAME_NUM);}	//�v���C���[�̎�̍��W���擾								//�v���C���[�̐����t���O�����擾
	bool	GetIsInAir()
	{if (state_ == PLAYER_JUMP)  return true; else return false;}
	int		GetHP() { return hp_; }

	//�Z�b�^�[
public:
	

private:
	void FromStand();// �ҋ@��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	void FromWalk();// ���s��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	void FromRun();// ���s��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	void FromJump();// �W�����v��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	void FromThrow();// ������Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	void FromReload();// ���U��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	void FromAttack();// �U����Ԃ��玟�ɂǂ̏�ԂɂȂ邩

private:
	PLAYER_ANIM_STATE	state_;			//��ԁi�X�e�[�^�X�j
	PLAYER_ANIM_STATE	old_state_;		//�O���[�v��ԁi�X�e�[�^�X�j
	VECTOR				forward_;			//�v���C���[�̌����x�N�g���i�[
	bool				hit_flg_;			//�ʃN���X�����蔻��t���O
	float				jump_time_;			//�W�����v�̎���
	int					hp_;				//�v���C���[�̗̑�
};