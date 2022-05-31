#include "AIKid.h"
#include "../../Scene/SceneManager.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Library/MyMath/MyMath.h"

namespace
{
	const int LOW_HP = 35;					//これ以上少ないとプレイヤーの体力が少ないと認められる
}

AIKid::AIKid() : AIBase()
{
	Init();
}

AIKid::~AIKid()
{
}

void AIKid::Init()
{

}

int AIKid::GetNextState(CEnemyBase* enemy)
{
	// 返却用変数next
	int next = 0;

	//現在アニメーションが再生されていないか
	end_animFlg_ = enemy->GetEndAnimFlg();

	//現在ターゲットがされているかどうかを更新する
	findFlg_ = enemy->GetFindFlg();

	// 現在の状態を取得
	int now_state = enemy->GetEnemyAIState();

	// 現在の状態ごとの処理の関数分け
	switch (now_state) {
	
	case KID_WALK:			//歩行状態からの遷移
		next = AIKidFromWalk(enemy);
		break;

	case KID_BIND:
		next = AIKidFromBind(enemy);
		break;
	}
	// 次はどの状態かを返却
	return next;
}



// 歩行状態遷移
int AIKid::AIKidFromWalk(CEnemyBase* enemy)
{
	//プレイヤーをロックオンした場合
	if (findFlg_)
	{
		//条件を満たしている場合に走行状態にする
		return KID_BIND;
	}

	// 何もなければ
	return KID_WALK;
}

int AIKid::AIKidFromBind(CEnemyBase* enemy)
{
	//アニメーション終了
	if (end_animFlg_)
	{
		enemy->ChangeAnim(true);
		return KID_WALK;
	}

	//何もなければ
	return KID_BIND;
}
