#pragma once

#include "../Library/Collision/Collision.h"
#include "DxLib.h"
#include "../Library/LibraryCommon.h"
#include <vector>
#include "CollisionCommon.h"



//UEにある当たり判定をもとに作った当たり判定クラス
//各クラスの初期化やセットの時にCreateCol関数を呼ぶことで動的構造体配列に
//情報を保持する枠を作成
//毎週Update関数でsetUpColInfoを呼んで情報を更新すれば
//GetCollisionDataで当たり判定に判定条件を満たした何かが当たったか
//そして当たったのは何か、をbool型とenum型で確認できる

class CCollisionManager
{
public:
	

public:
	CCollisionManager();	//コンストラクタ
	~CCollisionManager();	//デストラクタ

public:
	//インスタンス生成
	static void CreateInstance() { if (!instance_) instance_ = new CCollisionManager; }
	//インスタンス取得
	static CCollisionManager* GetInstance() { return instance_; }
	//インスタンス削除
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();
	void Step();//ステップ
	void DeleteAll();//配列初期化

public:
	//当たり判定を生成する
	int CreateCol(COL_DATA* data);
	//自分の当たり判定データを各クラス内で参照するための関数
	COL_DATA GetCollisionData(int num) { return *col_vec_[num]; }
	//自分の当たり判定情報を更新する関数、毎週呼ぶ必要がある
	void SetUpdateColInfo(int num, VECTOR pos, bool use);
	//何かしらの事情で当たり判定タイプを変更したいときに呼ぶ関数
	void SetUpdateColInfo(int num, OBJECT_TYPE type) { col_vec_[num]->object_ = type; }
	//当たり判定を確認する関数
	void CollisionCheck(COL_DATA* master,COL_DATA* target);
	//当たり判定結果をvectorに格納する
	void ColHitResult(COL_DATA* master, COL_DATA* target);

private:
	static CCollisionManager*	instance_;					//インスタンス

	int vectorMax_;

	//今後、どんどんUIが増えても大丈夫なように
	//動的配列として宣言
	std::vector<COL_DATA*> col_vec_;
};