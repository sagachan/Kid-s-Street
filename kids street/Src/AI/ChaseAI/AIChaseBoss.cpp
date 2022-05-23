#include "AIChaseBoss.h"
#include "../../Scene/SceneManager.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Library/MyMath/MyMath.h"

namespace
{
	const int LOW_HP = 35;					//これ以上少ないとプレイヤーの体力が少ないと認められる
}

AIChaseBoss::AIChaseBoss() : AIBase()
{
	Init();
}

AIChaseBoss::~AIChaseBoss()
{
}

void AIChaseBoss::Init()
{
	doonce_ = false;
	
}

int AIChaseBoss::GetNextState(CEnemyBase* enemy)
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
	case CHASE_APPEAR:			// 登場状態からの遷移
		next = AIChaseFromAppear(enemy);
		break;

	case CHASE_WALK:			//歩行状態からの遷移
		next = AIChaseFromWalk(enemy);
		break;

	case CHASE_RUN:
		next = AIChaseFromRun(enemy);
		break;

	case CHASE_ROLL:
		next = AIChaseFromRoll(enemy);
		break;

	case CHASE_PUNCH:
		next = AIChaseFromPunch(enemy);
		break;

	case CHASE_FINISHER:
		next = AIChaseFromFinisher(enemy);
		break;
	}

	// 次はどの状態かを返却
	return next;
}

// 登場状態遷移
int AIChaseBoss::AIChaseFromAppear(CEnemyBase* enemy)
{

	//アニメーションが現在再生されていない時に歩行状態になる処理
	if (end_animFlg_) {
		return CHASE_WALK;
	}

	// 何もなければ登場のまま
	return CHASE_APPEAR;
}

// 歩行状態遷移
int AIChaseBoss::AIChaseFromWalk(CEnemyBase* enemy)
{
	//各関数で使う変数の初期化
	doonce_ = false;

	//プレイヤーをロックオンした場合
	if(findFlg_)
	{
		CEnemyManager* enemyManager = CEnemyManager::GetInstance();
		CChaseBoss* chaseBoss = enemyManager->GetChaseBoss();

		//状態遷移をするので
		chaseBoss->SetChangeFlg();
		//条件を満たしている場合に走行状態にする
		return CHASE_RUN;
	}

	// 何もなければ
	return CHASE_WALK;
}

// 走行状態遷移
int AIChaseBoss::AIChaseFromRun(CEnemyBase* enemy)
{
	CPlayerManager* playerManager = CPlayerManager::GetInstance();
	CPlayer* player = playerManager->GetPlayer();
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();
	CChaseBoss* chaseBoss = enemyManager->GetChaseBoss();
	
	//ボスの半径取得
	float rad = chaseBoss->GetRad();

	//プレイヤーの位置情報取得
	VECTOR playerPos = player->GetPosition();

	//ボスの位置情報取得
	VECTOR bossPos = chaseBoss->GetPosition();


	//見失ったときに歩行状態に変わる処理
	if (!findFlg_) {
		return CHASE_WALK;
	}

	//プレイヤーがボスの攻撃可能圏内にいるとき
	if (CMyMath::RadiusCheck(bossPos.x,rad,playerPos.x) &&
		CMyMath::RadiusCheck(bossPos.z, rad, playerPos.z)) 
	{
		//状態遷移をすることが確定しているので
		chaseBoss->SetChangeFlg();

		//プレイヤーの体力が少ないとき
		if (player->GetHP() < LOW_HP)
		{
			//確殺状態に入る
			return CHASE_FINISHER;
		}
		else
		{
			//条件に合う場合に殴り状態に入る処理
			return CHASE_PUNCH;
		}
	}

	

	// 何もなければ
	return CHASE_RUN;
}

//回転状態
int AIChaseBoss::AIChaseFromRoll(CEnemyBase* enemy)
{
	CPlayerManager* playerManager = CPlayerManager::GetInstance();
	CPlayer* player = playerManager->GetPlayer();
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();
	CChaseBoss* chaseBoss = enemyManager->GetChaseBoss();

	//ボスの半径取得
	float rad = chaseBoss->GetRad();

	//プレイヤーの位置情報取得
	VECTOR playerPos = player->GetPosition();

	//ボスの位置情報取得
	VECTOR bossPos = chaseBoss->GetPosition();


	//アニメーションが現在再生されていない時に歩行状態になる処理
	if (end_animFlg_) {
		return CHASE_WALK;
	}

	//回転中にプレイヤーに触れた場合
	if (CMyMath::RadiusCheck(bossPos, rad, playerPos)) {
		//確殺状態に入る
		return CHASE_FINISHER;
	}

	// 何もなければ
	return CHASE_ROLL;
}

//殴り状態
int AIChaseBoss::AIChaseFromPunch(CEnemyBase* enemy)
{
	//アニメーションが現在再生されていない時に走行状態になる処理
	if (end_animFlg_) {
		CEnemyManager* enemyManager = CEnemyManager::GetInstance();
		CChaseBoss* chaseBoss = enemyManager->GetChaseBoss();

		//状態遷移をするので
		chaseBoss->SetChangeFlg();
		return CHASE_WALK;
	}

	// 何もなければ
	return CHASE_PUNCH;
}

//確殺状態
int AIChaseBoss::AIChaseFromFinisher(CEnemyBase* enemy)
{
	//アニメーションが現在再生されていない時に
	//ゲームオーバー
	if (end_animFlg_) {
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
	}

	// 何もなければ
	return CHASE_FINISHER;
}