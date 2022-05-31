#include "AIAttackBoss.h"
#include "../../Enemy/EnemyCommon.h"
#include "../../Enemy/EnemyManager.h"
namespace
{
	
}

AIAttackBoss::AIAttackBoss() : AIBase()
{
	Init();
}

AIAttackBoss::~AIAttackBoss()
{
}

void AIAttackBoss::Init()
{
	time_ = 0.0f;
	target_time_ = 0.0f;
	attack_time_ = 0.0f;
	counterFlg_ = false;
	get_timeflg_ = false;
}

int AIAttackBoss::GetNextState(CEnemyBase* enemy)
{
	// 返却用変数next
	int next = BOSS_APPEAR;

	//現在アニメーションが再生されていないか
	end_animFlg_ = enemy->GetEndAnimFlg();

	//現在ターゲットがされているかどうかを更新する
	findFlg_ = enemy->GetFindFlg();
	
	// 現在の状態を取得
	int now_state = enemy->GetEnemyAIState();

	// 現在の状態ごとの処理の関数分け
	switch (now_state) {
	case BOSS_APPEAR:			// 登場状態からの遷移
		next = AIAttackFromAppear(enemy);
		break;

	case BOSS_STAND:			//待機状態からの遷移
		next = AIAttackFromStand(enemy);
		break;

	case BOSS_TARGET:			 //標的状態からの遷移
		next = AIAttackFromTarget(enemy);
		break;

	case BOSS_MOTION_ATTACK:	//攻撃開始前構え状態からの遷移
		next = AIAttackFromReady(enemy);
		break;

	case BOSS_NORMAL_ATTACK:	//通常攻撃状態からの遷移
		next = AIAttackFromPunch(enemy);
		break;

	case BOSS_RARE_ATTACK:		//特殊攻撃状態からの遷移
		next = AIAttackFromJump(enemy);
		break;

	case BOSS_CATCH:			//キャッチ状態遷移
		next = AIAttackFromCatch(enemy);
		break;

	case BOSS_THROW:			//投擲状態遷移
		next = AIAttackFromThrow(enemy);
		break;

	case BOSS_RAGE:				//暴れ状態遷移
		next = AIAttackFromRage(enemy);
		break;

	case BOSS_SLASH:				//ダウン状態遷移
		next = AIAttackFromSlash(enemy);
		break;
	}

	//状態が変更されるなら
	if (now_state != next)
	{
		get_timeflg_ = false;
	}
	// 次はどの状態かを返却
	return next;
}

// 登場状態遷移
int AIAttackBoss::AIAttackFromAppear(CEnemyBase* enemy)
{
	
	//アニメーションが現在再生されていない時に待機状態になる処理
	if (end_animFlg_){
		return BOSS_STAND;
	}

	//当たり判定クラスによってカウンターフラグがtrueされているなら
	if (counterFlg_){
		return BOSS_CATCH;//キャッチ状態へ
	}
	
	// 何もなければ登場のまま
	return BOSS_APPEAR;
}

// 待機状態遷移
int AIAttackBoss::AIAttackFromStand(CEnemyBase* enemy)
{
	//当たり判定クラスによってカウンターフラグがtrueされているなら
	if (counterFlg_)	{
		return BOSS_CATCH;//キャッチ状態へ
	}

	//プレイヤーのロックオンができていない時
	if (!findFlg_){
		GetCount();
		//最初に時間を確認した時から指定時間が経過したなら
		if (SetWaitCount(target_time_)){
			return BOSS_TARGET;
		}
	}

	//プレイヤーをロックオンしてから規定時間が過ぎた場合
	if (findFlg_)	{
		GetCount();
		//最初に時間を確認した時から指定時間が経過したなら
		if (SetWaitCount(attack_time_)){
			return BOSS_NORMAL_ATTACK;
		}
	}

	//プレイヤーをロックオンしている場合
	if (findFlg_) {
		if (GetRand(BOSS_RARE_CHANCE) == 0) {
			return BOSS_MOTION_ATTACK;
		}
	}

	//まれに暴れる
	if (GetRand(BOSS_RAGE_CHANCE) == 0){
		return BOSS_RAGE;
	}
	
	if (findFlg_) {
		//ボスの体力取得
		int hp = CEnemyManager::GetInstance()->GetBoss()->GetHP();
		//HPが50％以下のときまれに薙ぎ払い
		if (hp < BOSS_HP_LOW){
			if (GetRand(BOSS_SLASH_CHANCE) == 0){
				return BOSS_SLASH;
			}
		}
	}

	// 何もなければ警戒のまま
	return BOSS_STAND;
}

// 標的状態遷移
int AIAttackBoss::AIAttackFromTarget(CEnemyBase* enemy)
{
	// //アニメーションが現在再生されていない時に待機状態になる処理
	if (end_animFlg_) {
		return BOSS_STAND;
	}

	//当たり判定クラスによってカウンターフラグがtrueされているなら
	if (counterFlg_){
		return BOSS_CATCH;//キャッチ状態へ
	}

	// 何もなければ標的状態のまま
	return BOSS_TARGET;
}

//　構え状態遷移
int AIAttackBoss::AIAttackFromReady(CEnemyBase* enemy)
{
	//アニメーションが現在再生されていない時に待機状態になる処理
	if (end_animFlg_) {
		return BOSS_RARE_ATTACK;
	}

	return BOSS_MOTION_ATTACK;
}

// 殴打状態遷移
int AIAttackBoss::AIAttackFromPunch(CEnemyBase* enemy)
{
	//アニメーションが現在再生されていない時に待機状態になる処理
	if (end_animFlg_) {
		return BOSS_STAND;
	}

	return BOSS_NORMAL_ATTACK;
}

//特殊攻撃状態遷移
int AIAttackBoss::AIAttackFromJump(CEnemyBase* enemy)
{
	//アニメーションが現在再生されていない時に待機状態になる処理
	if (end_animFlg_) {
		return BOSS_STAND;
	}

	return BOSS_RARE_ATTACK;
}

//キャッチ状態遷移
int AIAttackBoss::AIAttackFromCatch(CEnemyBase* enemy)
{
	//キャッチは状態としてあるだけでアニメーションしないため
	return BOSS_THROW;
}

//投擲状態遷移
int AIAttackBoss::AIAttackFromThrow(CEnemyBase* enemy)
{
	//アニメーションが現在再生されていない時に待機状態になる処理
	if (end_animFlg_) {
		counterFlg_ = false;
		return BOSS_STAND;

	}
	return BOSS_THROW;
}

//暴れ状態遷移
int AIAttackBoss::AIAttackFromRage(CEnemyBase* enemy)
{
	//アニメーションが現在再生されていない時に待機状態になる処理
	if (end_animFlg_) {
		return BOSS_STAND;
	}

	
	return BOSS_RAGE;
}

int AIAttackBoss::AIAttackFromSlash(CEnemyBase* enemy)
{
	// //アニメーションが現在再生されていない時に待機状態になる処理
	if (end_animFlg_) {
		return BOSS_STAND;
	}
	
	return BOSS_SLASH;
}
//------ここまでが状態遷移関数-----------------------






//最初に読み込んだ時の時間を格納
void AIAttackBoss::GetCount()
{
	//次にフラグがfalseにされるまでは通らない
	if (!get_timeflg_)
	{
		//読み込み開始時間を変数に格納
		time_ = (float)GetNowCount();
		get_timeflg_ = true;
	}
}


//自分が指定した秒数が経過したか確認する関数
bool AIAttackBoss::SetWaitCount(float wait_time)
{
	//今の時間を変数に格納
	float now_time = (float)GetNowCount();

	//今の時間から読み込み開始時間を引くことで経過時間を出す
	now_time -= time_;

	//設定された秒数より経過時間の方が多いならtrueを返す
	if (wait_time < now_time)
	{
		get_timeflg_ = false;
		return true;
	}
	else
		return false;
}
