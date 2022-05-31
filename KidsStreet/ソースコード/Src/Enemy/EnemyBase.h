//エネミー用基底クラス

#pragma once
#include "DxLib.h"
#include "../Library/Animation/Animation.h"

class CEnemyBase : public CAnim3D
{

public:
	
	//車線ごとの処理
	enum MOVE_DIR
	{
		MOVE_INIT = 0,
		FRONT_MOVE,
		BACK_MOVE,
		RIGHT_MOVE,
		LEFT_MOVE,
		MOVE_MAX_NUM
	};
	

public:
	CEnemyBase();
	virtual ~CEnemyBase();


	//初期化
	virtual void Init() = 0;
	//読み込み
	virtual void Load() = 0;
	//設定
	virtual void Set() = 0;
	//毎フレーム呼ぶ処理
	virtual void Step() = 0;
	//描画
	virtual void Draw() = 0;
	//更新
	virtual void Update() = 0;
	//削除
	virtual void Delete() = 0;
	//後処理
	virtual void Fin() = 0;

	//当たり判定渡し
	virtual void Hit() = 0;

public:
	//----------セッター--------
	
	//当たり判定処理フラグを立てる
	void SetColFlg(bool flg) { colFlg_ = flg; }
	 //ダメージ量をセットする
	void SetDmg(int dmg) { dmg_ = dmg; }


	//---------ゲッター--------
	
	//プレイヤー発見フラグを取得する
	bool GetFindFlg() { return findFlg_; }
	//向きベクトルを取得する
	VECTOR GetForwardVec() { return forward_; }
	
public:
	int GetEnemyAIState() const { return ai_state_; }

public:
	int			ai_state_;		// AI状態
	int			hp_;			//　HP　
	int			dmg_;

	float		move_;

	bool		colFlg_;		//当たり判定フラグ
	bool		findFlg_;		//プレイヤーを見つけているかどうか

	VECTOR		forward_;		//向きベクトル格納
}; 