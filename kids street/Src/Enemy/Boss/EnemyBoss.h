//EnemyBoss.h
//�G�l�~�[�{�X�N���X

#pragma once

#include "DxLib.h"
#include "../../Scene/SceneManager.h"
#include "../EnemyBase.h"
#include "../../AI/AIBase.h"
#include "../../Collision/CollisionManager.h"
#include "../EnemyCommon.h"


class CBoss : public CEnemyBase
{

public:
	CBoss();		//�R���X�g���N�^
	~CBoss();		//�f�X�g���N�^

	//------override-------
public:
	void Init();			//������
	void Load();			//�ǂݍ��݁i���[�h�j
	void Set();				
	void Step();			//���t���[���Ăԏ����i����j
	void Update();			//�X�V
	void Draw();			//�`��
	void Delete();			//�폜
	void Fin();				//�㏈��

	//---------�O����Ă΂��֐�---------
public:
	void Hit();
	void Damage(int dmg);
	void SetBossAIFlg(bool flg);
	int	GetHP() { return hp_; };

public:
	bool GetCounterFlg() { return counterFlg_; }	//�{�X����R���Ă��邩�ǂ���

	//----------���̃N���X�ȊO�Ŏg���Ȃ��֐�-----------
private:
	void GetCount();							//�ǂݍ��܂ꂽ�^�C�~���O�̎��Ԃ��m�ہA���g�̃t���O��܂�A�ړI�̏������ʂ�܂ł͂��̎��Ԃ��m�ۂ���
	void Target(bool flg);						//�^�[�Q�b�g���Ă���Ƃ��̃v���C���[�̕����{�X����������
	void DrawHitCube(VECTOR pos);
	

	//-----------��ԑJ�ڃA�j���[�V�����Ǘ�------------
	void StepAI();
	void StepAppear();				//�ҋ@��ԍX�V
	void StepStand();				//�x����ԍX�V
	void StepTarget();				//�W�I��ԍX�V
	void StepNormAttack();			//�ʏ�U����ԍX�V
	void StepCatch();				//�L���b�`��ԍX�V
	void StepThrow();				//������ԍX�V
	void StepRage();				//�\���ԍX�V
	//void StepMotion();				// �\����ԍX�V
	//void StepRareAttack();			// ����U����ԍX�V
	
private:

	
	bool		is_roop_;						//��񂾂��O����
	bool		is_origin_;						//�������t���O

	int			save_;							//if���ʉߊm�F�p

	float		radius_;						//���a
	float		distance_;						//�v���C���[�܂ł̋���
	float		old_distance_;					//�U���J�n�����Ƃ��̋������L�^���Ă���

	VECTOR		attack_vec_;					//�U������Ƃ��̕ψʃx�N�g��

	MOVE_DIR	dir_;							//�G�l�~�[����
	
	
	
	
	//AI�֌W�ϐ�
	bool		get_timeflg_;					//getcount�֐��p�A��x�����֐���ʂ�Ȃ������Ɏg���A�ړI�̏������I�������false�ɖ߂��Ă���
	bool		counterFlg_;					//���ꂪtrue�Ȃ�A�C�e���𓊂��Ԃ�
	bool		doOnce_;
	bool		doTwice_;

	int			frame_num_;

	float		time_;							//���݂̎��Ԃ��i�[
	
	VECTOR		cube_pos1_;
	VECTOR		cube_pos2_;
	VECTOR		frame_pos_[FRAME_MAX];
	
	//�ʏ�U���p
	bool		norm_attack_flg_;

	float		jump_dis_;

	VECTOR		add_pos_;
	VECTOR		jump_pos_;
	VECTOR		framePos[FRAME_MAX];

	AIBase*		enemy_ai_;

private:
	enum BOSS_ANIM_NO
	{
		STAND_ATTACK_MOTION,
		WEAK,
		CATCH,
		STAND,
		RARE_STAND,
		THROW,
		RAGE,
		RARE_ATTACK,
		APPEAR,
		ATTACK,
		TARGET
	};

	
};