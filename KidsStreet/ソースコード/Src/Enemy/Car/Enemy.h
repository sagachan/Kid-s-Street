//Enemy.h
//エネミークラス

#pragma once

#include "DxLib.h"
#include "../../Scene/PlayScene.h"
#include "../EnemyBase.h"
#include "../EnemyCommon.h"
#include "../../Field/FieldManager.h"


class CEnemy : public CEnemyBase
{

public:
	CEnemy();				//コンストラクタ
	~CEnemy();				//デストラクタ

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

public:
	void InterMove();		//交差点に入ったときに通る動作処理
	void CheckColCube();
	CEnemy* Clone();		//クローン

public:
	void	Move(int dir);																			//敵の移動処理
	bool	AddDamage(VECTOR pos1, VECTOR pos2);													//ダメージ判定処理
	
	
public:
	//ゲッター
	bool	GetInterFlg()	{ return interInfo_.flg_; }												//交差点処理開始フラグ取得
	int		GetInterNum()	{ return interInfo_.interNum_; }
	bool	GetMoveFlg()	{ return moveFlg_; }

public:
	//セッター
	void	SetInterFlg(bool flg) { interInfo_.flg_ = flg; }										//交差点開始処理フラグセット
	void	SetInterDir(int num, VECTOR pos) { interInfo_.check_ = num; interInfo_.pos_ = pos; }	//引数として交差点の方向番号を受け取り、車の進む方向をセットする
	void	SetPos(VECTOR pos, CEnemyBase::MOVE_DIR dir);				//初期値設定
	void	SetInterInfo(int interDir, VECTOR pos) { interInfo_.check_ = interDir; interInfo_.pos_ = pos; }									//交差点変数セット
	void	SetJustInter(int justNum) { interInfo_.just_ = justNum; }
	void	SetInterNum(int num) { interInfo_.interNum_ = num; }
	void	SetEndInter(bool flg) { interInfo_.endFlg_ = flg; }
	void	SetMoveFlg(bool flg) { moveFlg_ = flg; }

public:
	struct InterInfo
	{
		bool		flg_;						//交差点での処理が開始されているか
		bool		endFlg_;					//交差点処理が終了している場合にtrue
		int			interNum_;					//曲がるときは交差点番号を車ごとに保存する
		int			check_;						//この数値をもとに進む方向を決める
		int			just_;						//今現在どの角度から交差点に入っているか(0から3までの数値で判断
		VECTOR		pos_;						//交差点位置情報

	};

private:
	
	bool		moveFlg_;						//trueなら移動可能
	InterInfo	interInfo_;						//交差点処理情報
	MOVE_DIR	dir_;							//エネミー向き


public:
	//エラーチェックしたいもの
	InterInfo GetInterInfo() { return interInfo_; }
};