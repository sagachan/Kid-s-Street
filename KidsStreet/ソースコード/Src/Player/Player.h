//Player.h
//プレイヤークラス

#pragma once

#include "DxLib.h"
#include "../Library/Animation/Animation.h"

#define HAND_FRAME_NUM (12)

class CPlayer : public CAnim3D
{
private:

	enum PLAYER_ANIM_STATE
	{
		PLAYER_INIT,
		PLAYER_STAND,
		PLAYER_WALK,
		PLAYER_RUN,
		PLAYER_JUMP,
		PLAYER_THROW,
		PLAYER_RELOAD,
		PLAYER_ATTACK
	};

	enum PLAYER_ANIM_NO
	{
		INIT,
		ATTACK,
		RUN,
		THROW,
		ARMATURE,
		JUMP,
		STAND,
		WALK,
		RELOAD,
		ANIM_MAX_NUM
	};

public:
	CPlayer();		//コンストラクタ
	~CPlayer();		//デストラクタ

public:
	void Init();			//初期化
	void Load();			//読み込み（ロード）
	void Set();				//各変数などに初期値を設定（セット）
	void HitSet(bool flg);	//当たり判定用関数フラグ管理関数
	void HitSet();			//当たり判定用関数、oldposに戻す
	void Hit();				//当たり判定をまとめた関数
	void Step();			//毎フレーム呼ぶ処理（操作）
	void Update();			//更新
	void Draw();			//描画
	void Delete();			//削除
	void Fin();				//後処理

public:
	void StepInput();							//入力ステップ
	void StatesSet();							//アニメーション状態遷移
	void AddDamage(int dmg);					//プレイヤーの体力を減らす

	//ゲッター
public:
	VECTOR	GetForwardVec() { return forward_; }
	VECTOR	GetPlayerHandPos()
	{return MV1GetFramePosition(hndl_, HAND_FRAME_NUM);}	//プレイヤーの手の座標を取得								//プレイヤーの生存フラグをを取得
	bool	GetIsInAir()
	{if (state_ == PLAYER_JUMP)  return true; else return false;}
	int		GetHP() { return hp_; }

	//セッター
public:
	

private:
	void FromStand();// 待機状態から次にどの状態になるか
	void FromWalk();// 歩行状態から次にどの状態になるか
	void FromRun();// 走行状態から次にどの状態になるか
	void FromJump();// ジャンプ状態から次にどの状態になるか
	void FromThrow();// 投擲状態から次にどの状態になるか
	void FromReload();// 装填状態から次にどの状態になるか
	void FromAttack();// 攻撃状態から次にどの状態になるか

private:
	PLAYER_ANIM_STATE	state_;			//状態（ステータス）
	PLAYER_ANIM_STATE	old_state_;		//前ループ状態（ステータス）
	VECTOR				forward_;			//プレイヤーの向きベクトル格納
	bool				hit_flg_;			//別クラス当たり判定フラグ
	float				jump_time_;			//ジャンプの時間
	int					hp_;				//プレイヤーの体力
};