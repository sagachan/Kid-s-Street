//EnemyBoss.h
//エネミーボスクラス

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
	CBoss();		//コンストラクタ
	~CBoss();		//デストラクタ

	//------override-------
public:
	void Init();			//初期化
	void Load();			//読み込み（ロード）
	void Set();				
	void Step();			//毎フレーム呼ぶ処理（操作）
	void Update();			//更新
	void Draw();			//描画
	void Delete();			//削除
	void Fin();				//後処理
	void Hit();				//中で受け渡しが行われる


	//セッター
public:
	void Damage(int dmg);
	void SetBossAIFlg(bool flg);
	
	//ゲッター
	bool GetCounterFlg() { return counterFlg_; }	//ボスが抵抗してくるかどうか
	int	GetHP() { return hp_; };					//HP渡し
	VECTOR GetBossHand();

	//----------このクラス以外で使えない関数-----------
private:
	void Target(bool flg);						//ターゲットしているときのプレイヤーの方をボスが向く処理
	
	

	//-----------状態遷移アニメーション管理------------
	void StepAI();
	void StepAppear();				//待機状態更新
	void StepStand();				//警戒状態更新
	void StepTarget();				//標的状態更新
	void StepNormAttack();			//通常攻撃状態更新
	void StepCatch();				//キャッチ状態更新
	void StepThrow();				//投擲状態更新
	void StepRage();				//暴れ状態更新
	void StepSlash();				//薙ぎ状態更新
	void StepMotion();				// 構え状態更新
	void StepRareAttack();			// 特殊攻撃状態更新
	
private:
	//AI関係変数
	bool		counterFlg_;					//これがtrueならアイテムを投げ返す
	bool		doonce_;

	float		time_;							//現在の時間を格納
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