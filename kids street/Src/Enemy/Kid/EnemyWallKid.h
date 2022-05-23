

#pragma once

#include "DxLib.h"
#include "../../Scene/PlayScene.h"
#include "../EnemyBase.h"
#include "../EnemyCommon.h"
#include "../../Field/FieldCommon.h"


class CWallKid : public CEnemyBase
{

private:
	enum KID_ANIM_NO
	{
		BIND,
		WALK
	};
	
public:
	CWallKid();		//コンストラクタ
	~CWallKid();		//デストラクタ

public:
	void Init(){}
	void Load();		//読み込み（ロード）
	void Set();
	void Step(){}
	void Update(){}		//更新
	void Draw();		//描画
	void Delete();		//削除
	void Fin();			//後処理
	void Hit();

public:
	void	SetPos(VECTOR pos, CEnemyBase::MOVE_DIR dir);				//初期値設定

private:
	MOVE_DIR	dir_;								//エネミー向き
};