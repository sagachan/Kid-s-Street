//EnemyManager.h
//エネミー管理
//CEnemyへのアクセスは必ずCEnemyManagerを経由

#pragma once

#include "EnemyBase.h"
#include "Car/Enemy.h"
#include "Kid/EnemyKid.h"
#include "Boss/EnemyBoss.h"
#include "DxLib.h"
#include "../Scene/PlayScene.h"
#include "EnemyBase.h"
#include "../Scene/PlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Library/Input/Input.h"
#include "../Collision/CollisionManager.h"
#include "Chase/ChaseBoss.h"
#include "../Library/LibraryCommon.h"
#include "../UI/UIBase.h"
#include "Kid/EnemyWallKid.h"
#include "Kid/KidUI/KidUI.h"


class CEnemyManager
{
public:

	CEnemyManager();	//コンストラクタ
	~CEnemyManager();	//デストラクタ

public:
	//インスタンス生成
	static void CreateInstance() { if (!instance_) instance_ = new CEnemyManager; }
	//インスタンス取得
	static CEnemyManager* GetInstance() { return instance_; }
	//インスタンス削除
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();					//初期化
	void Load();					//読み込み
	void Set();
	void Step();					//ステップ
	void Update();					//反映
	void Draw();					//描画
	void Delete();					//削除
	void Fin();						//後処理

public:
	CEnemy* GetEnemy(int enemyNum) { return car_[enemyNum]; }			//エネミークラスを取得
	CBoss* GetBoss() { return boss_; }									//ボスクラスを取得
	CKid* GetKid(int enemyNum) { return kid_[enemyNum]; }
	CKidUI* GetKidUI() { return kidUI_; }
	bool GetSceneFlg() { return Sceneflg_; }
	void SetSceneFlg(bool flg) { Sceneflg_ = flg; }

private:
	void MinimizeCall(CEnemyBase* enemy[], int maxNum, VOID_TYPE type);//構造体参照処理短縮
	void WallCage();

private:
	static CEnemyManager* instance_;			//インスタンス

	//クラス関係変数
	CEnemyBase* enemy_[APPEAR_ENEMY_MAX_NUM];
	

	CEnemyBase* carInfo_[APPEAR_CAR_NUM];
	CEnemy* car_[APPEAR_CAR_NUM];

	CEnemyBase* kidInfo_[APPEAR_KID_NUM];
	CKid* kid_[APPEAR_KID_NUM];

	CEnemyBase* wallInfo_[APPEAR_WALL_NUM];
	CWallKid* wall_[APPEAR_WALL_NUM];

	CEnemyBase* bossInfo_;
	CBoss* boss_;

	CEnemyBase* chaseInfo_;
	CChaseBoss* chase_;

	
	//UI関係クラス
	CUIBase* ui_[UI_MAX_NUM];
	CKidUI* kidUI_;



	//通常変数
	VECTOR pos_plus_;							//車同士の間隔空け
	bool Sceneflg_;								//シーン分け

	

	bool bossflg_;
};
