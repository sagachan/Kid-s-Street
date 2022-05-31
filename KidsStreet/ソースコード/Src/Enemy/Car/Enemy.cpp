#include "Enemy.h"
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Scene/SceneManager.h"
#include "../../Player/PlayerManager.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionCommon.h"
#include "../../Library/LibraryCommon.h"

namespace
{
	const float		SIMPLE_MOVE = 3.0f;
	const VECTOR	CAR_FRONT = VGet(0, 0, SIMPLE_MOVE);									//前に進む車の移動速度(z)
	const VECTOR	CAR_BACK = VGet(0, 0, -SIMPLE_MOVE);									//奥から手前に進む車の移動速度(z)
	const VECTOR	CAR_RIGHT = VGet(SIMPLE_MOVE, 0, 0);									//右に進む車の移動速度(x）
	const VECTOR	CAR_LEFT = VGet(-SIMPLE_MOVE, 0, 0);									
	//左に進む車の移動速度(x)

	const float		RADIUS = 7.0;

	const VECTOR	COL_CUBE1 = VGet(4.0, 7.0, 7.0);
	const VECTOR	COL_CUBE2 = VGet(4.0, 4.0, 9.0);
	const VECTOR	COL_RADIUS = VGet(10.0f, 10.0f, 10.0f);
	const VECTOR	SCALE = VGet(1.0, 1.0, 1.0);
}

//コンストラクタ
CEnemy::CEnemy()
{
	Init();
}

//デストラクタ
CEnemy::~CEnemy()
{
	Fin();
}


//初期化
void CEnemy::Init()
{
	moveFlg_ = false;						
	interInfo_ = { 0 };	
	dir_ = MOVE_INIT;
}

void CEnemy::Set()
{
	moveFlg_ = true;
	//当たり判定を生成
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_.pos_ = pos_;
	colData_.cubeRad_ = COL_RADIUS;
	colData_.useFlg_ = true;
	colData_.myList_ = COL_CHECK_CAR;
	colData_.type_.pawn_ = CHECK_BOX_HIT;
	colData_.type_.static_ = CHECK_BOX_NONE;
	colData_.type_.dynamic_ = CHECK_BOX_NONE;
	colData_.object_ = OBJECT_DYNAMIC;
	colData_.shapeCol_ = SHAPE_CUBE;

	colNum_ = collision->CreateCol(&colData_);
}

//セット
void CEnemy::SetPos(VECTOR pos, CEnemyBase::MOVE_DIR dir)
{
	pos_ = pos;
	dir_ = dir;
	
}

//読み込み（ロード）
void CEnemy::Load()
{
	//車モデル読み込み
	hndl_ = MV1LoadModel("Data/Enemy/Car/enemy_car_model.x");
}

//毎フレーム呼ぶ処理（操作）
void CEnemy::Step()
{
	Hit();

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	oldPos_ = pos_;

	//交差点の処理フラグがfalseかつまだ初期化されていないなら処理終了フラグを初期化する
	if (!interInfo_.flg_ && interInfo_.endFlg_)
	{
		interInfo_.endFlg_ = false;
	}

	if (interInfo_.flg_ && !interInfo_.endFlg_){
		//交差点移動処理
		InterMove();
	}

	//移動を可能にするフラグが立っているかどうか
	if(moveFlg_)
	Move(dir_);
}


//更新
void CEnemy::Update()
{
	//普通車線のみ回転
	if (dir_ == FRONT_MOVE)
	{
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_FRONT);
	}
	if (dir_ == BACK_MOVE)
	{
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_BACK);
	}
	if (dir_ == RIGHT_MOVE)
	{
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_RIGHT);
	}
	if (dir_ == LEFT_MOVE)
	{
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_LEFT);
	}

	//座標確定
	MV1SetPosition(hndl_, pos_);

	//当たり判定関係更新
	CCollisionManager::GetInstance()->SetUpdateColInfo(colNum_, pos_, colData_.useFlg_);
}

void CEnemy::Hit()
{
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_ = collision->GetCollisionData(colNum_);
	//複数の当たり判定listに同じオブジェクトが触れていた場合に処理を複数回繰り返してしまわないようにする
	//処理を行ったリストのタイプの元enum番号のフラグを立てる
	bool checkFlg[COL_CHECK_MAX] = { false };

	if (colData_.hitFlg_)
	{
		for (int checkNum = 0; checkNum < COL_CHECK_MAX; checkNum++)
		{
			//当たっていたのがプレイヤーの時
			if (colData_.list_[checkNum] == COL_CHECK_PLAYER && !checkFlg[COL_CHECK_PLAYER])
			{
				//ゲームオーバーシーンへ変更
				CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
				checkFlg[COL_CHECK_PLAYER] = true;
			}
		}
	}
}

//描画
void CEnemy::Draw()
{
	MV1DrawModel(hndl_);
}


//削除
void CEnemy::Delete()
{
	MV1DeleteModel(hndl_);
}



//後処理
void CEnemy::Fin()
{
	//Deleteが呼ばれていないなら
	if (hndl_ != 0){
		//削除を呼んでおく
		Delete();
	}
}



//クローン関数
CEnemy* CEnemy::Clone()
{
	return nullptr;
}

//車移動処理
void CEnemy::Move(int dir)
{
	if (dir_ == FRONT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, CAR_FRONT);
	}
	else if (dir_ == BACK_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, CAR_BACK);
	}
	else if (dir_ == RIGHT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, CAR_RIGHT);
	}
	else if (dir_ == LEFT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, CAR_LEFT);
	}
}

//交差点を移動する処理、交差点クラスにて通るか通らないかが決定される
void CEnemy::InterMove()
{
	//---------ここでしたいこと-----------
	//		交差点を曲がるための移動処理
	//		セットされた交差点変数の中身をもとにどちらに曲がるかをチェックし
	//		その方向に曲がるための処理を行う
	// 		あらかじめ決めておいたラインまで行くとそこで決めた角度に直角に曲がる
	//-------------------------------------

	CInter* inter = CFieldManager::GetInstance()->GetInter();

	//交差点として認められている範囲
	float interRad = inter->GetInterRad();
	//交差点の曲がり角をまがる時に使う指定位置情報
	float nearInter = interRad / 3, farInter = nearInter + interRad;


	//曲がる角度と現在の方向をチェック
	//前方向から曲がる時
	if (interInfo_.just_ == FRONT) {
		if (interInfo_.check_ == BACK) {
			interInfo_.endFlg_ = true;
		}
		else if (interInfo_.check_ == RIGHT) {
			if (pos_.z < interInfo_.pos_.z + nearInter) {
				dir_ = RIGHT_MOVE;
			}
		}
		else if (interInfo_.check_ == LEFT) {
			if (pos_.z < interInfo_.pos_.z - nearInter) {
				dir_ = LEFT_MOVE;
			}
		}
	}
	//後ろ方向から曲がる時
	if (interInfo_.just_ == BACK) {
		if (interInfo_.check_ == FRONT) {
			interInfo_.endFlg_ = true;
		}
		else if (interInfo_.check_ == RIGHT) {
			if (pos_.z > interInfo_.pos_.z + nearInter) {
				dir_ = RIGHT_MOVE;
			}
		}
		else if (interInfo_.check_ == LEFT) {
			if (pos_.z > interInfo_.pos_.z - nearInter) {
				dir_ = LEFT_MOVE;
			}
		}
	}
	//右方向から曲がる時
	if (interInfo_.just_ == RIGHT) {
		if (interInfo_.check_ == FRONT) {
			if (pos_.x < interInfo_.pos_.x - nearInter) {
				dir_ = FRONT_MOVE;
			}
		}
		else if (interInfo_.check_ == BACK) {
			if (pos_.x < interInfo_.pos_.x + nearInter) {
				dir_ = BACK_MOVE;
			}
			else if (interInfo_.check_ == LEFT) {
				interInfo_.endFlg_ = true;
			}
		}
	}
		//左方向から曲がる時
	if (interInfo_.just_ == LEFT) {
		if (interInfo_.check_ == FRONT) {
			if (pos_.x > interInfo_.pos_.x - nearInter) {
				dir_ = FRONT_MOVE;
			}
		}

		else if (interInfo_.check_ == BACK) {
			if (pos_.x > interInfo_.pos_.x + nearInter) {
				dir_ = BACK_MOVE;
			}
		}
		else if (interInfo_.check_ == RIGHT) {
			interInfo_.endFlg_ = true;
		}

	}
}