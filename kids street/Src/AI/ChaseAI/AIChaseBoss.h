#ifndef __AI_CHASE_BOSS_H__
#define __AI_CHASE_BOSS_H__

#include "../AIBase.h"


class AIChaseBoss : public AIBase 
{

public:
	AIChaseBoss();
	~AIChaseBoss();

public:
	//�����o�ϐ�������
	void Init();
	// ���N���X����K���p������
	int GetNextState(CEnemyBase* enemy) override;


private:
	// �o���Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIChaseFromAppear(CEnemyBase* enemy);
	// ������Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIChaseFromWalk(CEnemyBase* enemy);
	// ���s��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIChaseFromRun(CEnemyBase* enemy);
	// ��]��Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIChaseFromRoll(CEnemyBase* enemy);
	// ���ŏ�Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIChaseFromPunch(CEnemyBase* enemy);
	// �m�E��Ԃ���̓Q�[���I�[�o�[�ɐi��
	int AIChaseFromFinisher(CEnemyBase* enemy);

private:
	bool		doonce_;
};

#endif
