#ifndef __AI_ATTACK_BOSS_H__
#define __AI_ATTACK_BOSS_H__

#include "../AIBase.h"


class AIAttackBoss : public AIBase {
public:
	AIAttackBoss();
	~AIAttackBoss();

public:
	//�����o�ϐ�������
	void Init();
	
	// �x����ԂɂȂ�͈͂�ݒ�
	void SetTargetTime(float target_time, float attack_time) { target_time_ = target_time,attack_time_ = attack_time; }
	// ���N���X����K���p������
	int GetNextState(CEnemyBase* enemy) override;
	//�J�E���^�[������Ƃ��Ɏg���t���O
	void SetCounterFlg(bool flg) { counterFlg_ = flg; }

private:
	// �o���Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIAttackFromAppear(CEnemyBase* enemy);
	// �ҋ@��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIAttackFromStand(CEnemyBase* enemy);
	// �W�I��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIAttackFromTarget(CEnemyBase* enemy);
	// �\����Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIAttackFromReady(CEnemyBase* enemy);
	// ���ŏ�Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIAttackFromPunch(CEnemyBase* enemy);
	// �W�����v�U����Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIAttackFromJump(CEnemyBase* enemy);
	// �L���b�`��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIAttackFromCatch(CEnemyBase* enemy);
	// ������Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIAttackFromThrow(CEnemyBase* enemy);
	// �\���Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIAttackFromRage(CEnemyBase* enemy);
	// 
	int AIAttackFromSlash(CEnemyBase* enemy);
	


	void GetCount();
	bool SetWaitCount(float wait_time);			//�����������ɓ��ꂽ���l���̎��Ԃ��҂��ꂽ���ǂ������m�F����A�҂��ꂽ�Ȃ�true
	

private:
	bool		get_timeflg_;					//getcount�֐��p�A��x�����֐���ʂ�Ȃ������Ɏg���A�ړI�̏������I�������false�ɖ߂��Ă���(��̓I�ɂ̓^�[�Q�b�g��Ԃ��U���I�����Ɍ��ɖ߂�̂ł��̎��Ɉꏏ�ɖ߂��Ă���
	bool		counterFlg_;

	float		target_time_;					//�v���C���[���^�[�Q�b�g���邽�߂ɂ����鎞��
	float		time_;							//���݂̎��Ԃ��i�[
	float		attack_time_;
	};

#endif
