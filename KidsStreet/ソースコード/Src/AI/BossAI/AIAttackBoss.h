#ifndef __AI_ATTACK_BOSS_H__
#define __AI_ATTACK_BOSS_H__

#include "../AIBase.h"


class AIAttackBoss : public AIBase {
public:
	AIAttackBoss();
	~AIAttackBoss();

public:
	//メンバ変数初期化
	void Init();
	
	// 警戒状態になる範囲を設定
	void SetTargetTime(float target_time, float attack_time) { target_time_ = target_time,attack_time_ = attack_time; }
	// 基底クラスから必ず継承する
	int GetNextState(CEnemyBase* enemy) override;
	//カウンターをするときに使うフラグ
	void SetCounterFlg(bool flg) { counterFlg_ = flg; }

private:
	// 登場状態から次にどの状態になるか
	int AIAttackFromAppear(CEnemyBase* enemy);
	// 待機状態から次にどの状態になるか
	int AIAttackFromStand(CEnemyBase* enemy);
	// 標的状態から次にどの状態になるか
	int AIAttackFromTarget(CEnemyBase* enemy);
	// 構え状態から次にどの状態になるか
	int AIAttackFromReady(CEnemyBase* enemy);
	// 殴打状態から次にどの状態になるか
	int AIAttackFromPunch(CEnemyBase* enemy);
	// ジャンプ攻撃状態から次にどの状態になるか
	int AIAttackFromJump(CEnemyBase* enemy);
	// キャッチ状態から次にどの状態になるか
	int AIAttackFromCatch(CEnemyBase* enemy);
	// 投擲状態から次にどの状態になるか
	int AIAttackFromThrow(CEnemyBase* enemy);
	// 暴れ状態から次にどの状態になるか
	int AIAttackFromRage(CEnemyBase* enemy);
	// 
	int AIAttackFromSlash(CEnemyBase* enemy);
	


	void GetCount();
	bool SetWaitCount(float wait_time);			//自分が引数に入れた数値分の時間が待たれたかどうかを確認する、待たれたならtrue
	

private:
	bool		get_timeflg_;					//getcount関数用、一度しか関数を通らない処理に使う、目的の処理が終わったらfalseに戻しておく(具体的にはターゲット状態が攻撃終了時に元に戻るのでその時に一緒に戻しておく
	bool		counterFlg_;

	float		target_time_;					//プレイヤーをターゲットするためにかかる時間
	float		time_;							//現在の時間を格納
	float		attack_time_;
	};

#endif
