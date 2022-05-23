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

	//---------外から呼ばれる関数---------
public:
	void Hit();
	void Damage(int dmg);
	void SetBossAIFlg(bool flg);
	int	GetHP() { return hp_; };

public:
	bool GetCounterFlg() { return counterFlg_; }	//ボスが抵抗してくるかどうか

	//----------このクラス以外で使えない関数-----------
private:
	void GetCount();							//読み込まれたタイミングの時間を確保、自身のフラグを折り、目的の処理が通るまではこの時間を確保する
	void Target(bool flg);						//ターゲットしているときのプレイヤーの方をボスが向く処理
	void DrawHitCube(VECTOR pos);
	

	//-----------状態遷移アニメーション管理------------
	void StepAI();
	void StepAppear();				//待機状態更新
	void StepStand();				//警戒状態更新
	void StepTarget();				//標的状態更新
	void StepNormAttack();			//通常攻撃状態更新
	void StepCatch();				//キャッチ状態更新
	void StepThrow();				//投擲状態更新
	void StepRage();				//暴れ状態更新
	//void StepMotion();				// 構え状態更新
	//void StepRareAttack();			// 特殊攻撃状態更新
	
private:

	
	bool		is_roop_;						//一回だけ徹処理
	bool		is_origin_;						//初期化フラグ

	int			save_;							//if文通過確認用

	float		radius_;						//半径
	float		distance_;						//プレイヤーまでの距離
	float		old_distance_;					//攻撃開始したときの距離を記録しておく

	VECTOR		attack_vec_;					//攻撃するときの変位ベクトル

	MOVE_DIR	dir_;							//エネミー向き
	
	
	
	
	//AI関係変数
	bool		get_timeflg_;					//getcount関数用、一度しか関数を通らない処理に使う、目的の処理が終わったらfalseに戻しておく
	bool		counterFlg_;					//これがtrueならアイテムを投げ返す
	bool		doOnce_;
	bool		doTwice_;

	int			frame_num_;

	float		time_;							//現在の時間を格納
	
	VECTOR		cube_pos1_;
	VECTOR		cube_pos2_;
	VECTOR		frame_pos_[FRAME_MAX];
	
	//通常攻撃用
	bool		norm_attack_flg_;

	float		jump_dis_;

	VECTOR		add_pos_;
	VECTOR		jump_pos_;
	VECTOR		framePos[FRAME_MAX];

	AIBase*		enemy_ai_;

private:
	enum BOSS_ANIM_NO
	{
		STAND_ATTACK_MOTION,
		WEAK,
		CATCH,
		STAND,
		RARE_STAND,
		THROW,
		RAGE,
		RARE_ATTACK,
		APPEAR,
		ATTACK,
		TARGET
	};

	
};