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
	void Hit();				//���Ŏ󂯓n�����s����


	//�Z�b�^�[
public:
	void Damage(int dmg);
	void SetBossAIFlg(bool flg);
	
	//�Q�b�^�[
	bool GetCounterFlg() { return counterFlg_; }	//�{�X����R���Ă��邩�ǂ���
	int	GetHP() { return hp_; };					//HP�n��
	VECTOR GetBossHand();

	//----------���̃N���X�ȊO�Ŏg���Ȃ��֐�-----------
private:
	void Target(bool flg);						//�^�[�Q�b�g���Ă���Ƃ��̃v���C���[�̕����{�X����������
	
	

	//-----------��ԑJ�ڃA�j���[�V�����Ǘ�------------
	void StepAI();
	void StepAppear();				//�ҋ@��ԍX�V
	void StepStand();				//�x����ԍX�V
	void StepTarget();				//�W�I��ԍX�V
	void StepNormAttack();			//�ʏ�U����ԍX�V
	void StepCatch();				//�L���b�`��ԍX�V
	void StepThrow();				//������ԍX�V
	void StepRage();				//�\���ԍX�V
	void StepSlash();				//�ガ��ԍX�V
	void StepMotion();				// �\����ԍX�V
	void StepRareAttack();			// ����U����ԍX�V
	
private:
	//AI�֌W�ϐ�
	bool		counterFlg_;					//���ꂪtrue�Ȃ�A�C�e���𓊂��Ԃ�
	bool		doonce_;

	float		time_;							//���݂̎��Ԃ��i�[
	float		jump_dis_;

	VECTOR		add_pos_;
	VECTOR		jump_pos_;

	AIBase*		enemy_ai_;
	COL_DATA	colFrmData_[FRAME_MAX];

private:
	enum BOSS_ANIM_NO
	{
		STAND_ATTACK_MOTION,
		SLASH,
		WEAK,
		CATCH,
		RARE_STAND,
		STAND,
		THROW,
		RAGE,
		RARE_ATTACK,
		APPEAR,
		TARGET,
		ATTACK
	};
};