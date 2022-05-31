#ifndef __AI_Kid_H__
#define __AI_Kid_H__

#include "../AIBase.h"


class AIKid : public AIBase
{

public:
	AIKid();
	~AIKid();

public:
	//�����o�ϐ�������
	void Init();
	// ���N���X����K���p������
	int GetNextState(CEnemyBase* enemy) override;


private:
	// ������Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIKidFromWalk(CEnemyBase* enemy);
	// �ߔ���Ԃ��玟�ɂǂ̏�ԂɂȂ邩
	int AIKidFromBind(CEnemyBase* enemy);

private:
	
};

#endif
