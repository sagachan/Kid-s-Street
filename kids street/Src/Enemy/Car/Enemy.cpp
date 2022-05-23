#include "Enemy.h"
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Scene/SceneManager.h"
#include "../../Player/PlayerManager.h"

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
}

//セット
void CEnemy::SetPos(VECTOR pos, CEnemyBase::MOVE_DIR dir)
{
	pos_ = pos;
	dir_ = dir;
	
}

void CEnemy::Hit()
{

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
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	oldPos_ = pos_;

	//交差点の処理フラグがfalseかつまだ初期化されていないなら処理終了フラグを初期化する
	if (!interInfo_.flg_ && interInfo_.endFlg_)
	{
		interInfo_.endFlg_ = false;
	}

	//当たり判定
	CheckColCube();


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
}


//描画
void CEnemy::Draw()
{
	MV1DrawModel(hndl_);
	/*DrawCube3D(cube_pos1_, cube_pos2_, GetColor(105, 255, 255), GetColor(255, 255, 255), false);*/
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

//当たり判定計算
void CEnemy::CheckColCube()
{
	VECTOR		cube_pos1_, cube_pos2_;			//当たり判定計算用変数

	cube_pos1_ = pos_, cube_pos2_ = pos_;

	cube_pos1_.x = cube_pos1_.x + COL_CUBE1.x;
	cube_pos1_.y = cube_pos1_.y + COL_CUBE1.y;
	cube_pos1_.z = cube_pos1_.z + COL_CUBE1.z;

	cube_pos2_.x = cube_pos2_.x - COL_CUBE2.x;
	cube_pos2_.y = cube_pos2_.y - COL_CUBE2.y;
	cube_pos2_.z = cube_pos2_.z - COL_CUBE2.z;

	//プレイヤーと当たり判定ボックスが触れていることが確認された場合
	if (moveFlg_)
	{
		if (AddDamage(cube_pos1_, cube_pos2_) == true) {
			//ゲームオーバーシーンへ変更
			CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
		}
	}
}

//ダメージ処理
bool CEnemy::AddDamage(VECTOR pos1,VECTOR pos2)
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	
	if (pos1.x > player->GetPosition().x &&
		player->GetPosition().x > pos2.x &&
		pos1.y > player->GetPosition().y &&
		pos1.z > player->GetPosition().z &&
		player->GetPosition().z > pos2.z){
		return true;
	}

	return false;
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