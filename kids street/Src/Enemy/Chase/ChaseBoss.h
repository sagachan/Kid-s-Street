//ChaseBoss.h
//チェイスボスクラス

#pragma once

#include "DxLib.h"
#include "../EnemyBase.h"
#include "../../AI/AIBase.h"
#include "../EnemyCommon.h"


class CChaseBoss : public CEnemyBase
{
private:
	enum CHASE_ANIM_NO
	{
		APPEAR,
		FINISHER,
		PUNCH,
		ROLL,
		RUN,
		WALK
	};

	//見失った後プレイヤーを探すときに使う情報構造体
	struct SerchInfo
	{
		VECTOR	useInterPos_;				//索敵するために使う交差点の位置情報
		bool	flg_;					//見失っているかどうかを確認するフラグ

	};

public:
	CChaseBoss();			//コンストラクタ
	~CChaseBoss();			//デストラクタ

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
	void Hit();
	
	//----------このクラス以外で使えない関数-----------
private:
	void Target(bool flg);					//引数がtrueならプレイヤーの方を向き続ける
	bool CheckFirstTarget();				//最初に見つけるときの判定
	void CheckChase();						//追いかけている時に通る判定
	void ReturnRoute();						//あらかじめ決めておいた巡回路に戻る処理
	void LoopRoute();						//決められた順路をボスが徘徊する処理
	void SerchChase();						//プレイヤーを見失ってから一定時間索敵をする処理
	void StopStreet();						//交差点にある自分の周辺の車の移動を止めることで交通事故を防ぐ処理
	
//-----------状態遷移アニメーション管理------------
	void StepAI();
	void StepAppear();						//登場状態更新
	void StepWalk();						//歩行状態更新
	void StepRun();							//走行状態更新
	void StepRoll();						//回転状態更新
	void StepPunch();						//殴打状態更新
	void StepFinisher();					//確殺状態更新

public:
	//セッター
	void SetChangeFlg() {changeFlg_ = true;}					//状態遷移が行われたときにtrueに
	
private:
	//AI関係変数
	bool		changeFlg_;
	SerchInfo	serchInfo_;
	int			colMapHndl_;
	bool		routeFlg_;				//決められた道を現在通っているかどうかをチェックするフラグ(trueなら通っている)
	bool		attackFlg_;				//攻撃可能かどうか
	AIBase*		enemy_ai_;
};