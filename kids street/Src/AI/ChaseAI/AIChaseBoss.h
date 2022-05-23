#ifndef __AI_CHASE_BOSS_H__
#define __AI_CHASE_BOSS_H__

#include "../AIBase.h"


class AIChaseBoss : public AIBase 
{

public:
	AIChaseBoss();
	~AIChaseBoss();

public:
	//メンバ変数初期化
	void Init();
	// 基底クラスから必ず継承する
	int GetNextState(CEnemyBase* enemy) override;


private:
	// 登場状態から次にどの状態になるか
	int AIChaseFromAppear(CEnemyBase* enemy);
	// 歩き状態から次にどの状態になるか
	int AIChaseFromWalk(CEnemyBase* enemy);
	// 走行状態から次にどの状態になるか
	int AIChaseFromRun(CEnemyBase* enemy);
	// 回転状態から次にどの状態になるか
	int AIChaseFromRoll(CEnemyBase* enemy);
	// 殴打状態から次にどの状態になるか
	int AIChaseFromPunch(CEnemyBase* enemy);
	// 確殺状態からはゲームオーバーに進む
	int AIChaseFromFinisher(CEnemyBase* enemy);

private:
	bool		doonce_;
};

#endif
