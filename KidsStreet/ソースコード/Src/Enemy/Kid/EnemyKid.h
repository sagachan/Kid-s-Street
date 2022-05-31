//Enemy.h
//エネミークラス

#pragma once

#include "DxLib.h"
#include "../../Scene/PlayScene.h"
#include "../EnemyBase.h"
#include "../EnemyCommon.h"
#include "../../Field/FieldCommon.h"
#include "../../AI/AIBase.h"


class CKid : public CEnemyBase
{

private:
	enum KID_ANIM_NO
	{
		BIND,
		WALK
	};
	
public:
	CKid();		//コンストラクタ
	~CKid();		//デストラクタ

public:
	void Init();			//初期化
	void Load();			//読み込み（ロード）
	void Set();
	void Step();			//毎フレーム呼ぶ処理（操作）
	void Update();			//更新
	void Draw();			//描画
	void Delete();			//削除
	void Fin();				//後処理
	CKid* Clone();			//クローン
	void Hit();


public:
	void Move(int dir);											//敵の移動処理
	void RouteSelect();

public:
	//セッター
	void SetRoute(int boneNum) { initRouteNum_ = boneNum; }		//子供の初期出現座標
	void SetKidNum(int enemyNum) { kidNum_ = enemyNum; }		//子供番号を設定

	//ゲッター
	

private:
	void Rotation();									//1周回る処理
	void StartEnd();									//STARTからENDまでKIDが行く処理
	void Target(bool flg);								//trueならプレイヤーの方を常に向く
	//-----------状態遷移アニメーション管理------------
	void StepAI();
	void StepWalk();				//歩行状態更新
	void StepBind();				//捕縛状態更新
	
private:

	enum
	{
		NONE = 0,
		START,
		END,
		ROTATION
	};

	enum WALK_TYPE
	{
		WALK_START_END,
		WALK_ROTATION
	};

	enum SELECT_TYPE
	{
		START_FROM_MOVE,							//STARTから始まった道選択
		END_FROM_MOVE								//ENDから始まった道選択
	};

	MOVE_DIR	dir_;								//エネミー向き
	int			kidRoute_[INTER_MAX_NUM];		//子供が通るときに使う道
	int			initRouteNum_;						//この子供クラスの初期ルート番号
	int			currentRoute_;						//現在のボーンの番号
	SELECT_TYPE	selectType_;							//道選択方法
	WALK_TYPE walkType_;						//子供の歩くタイプ選択
	VECTOR      frmPosArray_[INTER_MAX_NUM];	//ボーンの位置
	float       enemySpd_;						//敵の移動速度		
	int			kidNum_;						//自分の構造体番号を確保
	bool		moveFlg_;
	AIBase*		enemy_ai_;
};