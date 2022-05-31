#ifndef __AI_Kid_H__
#define __AI_Kid_H__

#include "../AIBase.h"


class AIKid : public AIBase
{

public:
	AIKid();
	~AIKid();

public:
	//メンバ変数初期化
	void Init();
	// 基底クラスから必ず継承する
	int GetNextState(CEnemyBase* enemy) override;


private:
	// 歩き状態から次にどの状態になるか
	int AIKidFromWalk(CEnemyBase* enemy);
	// 捕縛状態から次にどの状態になるか
	int AIKidFromBind(CEnemyBase* enemy);

private:
	
};

#endif
