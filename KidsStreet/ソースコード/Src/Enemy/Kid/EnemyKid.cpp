//子供クラス

#include "EnemyKid.h"
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Scene/SceneManager.h"
#include "../../Player/PlayerManager.h"
#include "../../AI/KidAI/AIKid.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionCommon.h"
#include "../../Library/LibraryCommon.h"


namespace
{
	
	const VECTOR ENEMY_ROT_POS = VGet(0.0f, 3.14f, 0.0f);					//子供1の回転値

	const float		SIMPLE_MOVE = 0.5f;
	const VECTOR	KID_FRONT = VGet(0, 0, SIMPLE_MOVE);					//前に進む車の移動速度(z)
	const VECTOR	KID_BACK = VGet(0, 0, -SIMPLE_MOVE);					//奥から手前に進む車の移動速度(z)
	const VECTOR	KID_RIGHT = VGet(SIMPLE_MOVE, 0, 0);					//右に進む車の移動速度(x）
	const VECTOR	KID_LEFT = VGet(-SIMPLE_MOVE, 0, 0);					//左に進む車の移動速度(x)
	const float		KID_SPD = 0.5f;											//子供の進む速さ
	const float		KID_WALK_TIME = 10.0f;									//子供が直線を進み切る時間
	const float		KID_HIGHT = 7.0f;										//子供の高さ
	const float		KID_RADIUS = 8.0f;										//子供の当たり判定範囲
	const VECTOR	COL_RADIUS = VGet(8.0f, 12.0f, 8.0f);					//子供の当たり判定範囲(VECTOR)
	const int		KID_DMG = 5;
	const int		BIND_FRM = 150;
}

//コンストラクタ
CKid::CKid()
{
	Init();
}

//デストラクタ
CKid::~CKid()
{
	Fin();
}


//初期化
void CKid::Init()
{
	moveFlg_ = false;
}

//セット
void CKid::Set()
{
	int routeArray[INTER_MAX_NUM]
	{
		START,
		NONE,
		NONE,
		ROTATION,
		START,
		END,
		START,
		NONE,
		NONE,
		ROTATION,
		START,
		END,
		START,
		NONE,
		NONE,
		NONE,
		END
	};

	for (int route = 0; route < INTER_MAX_NUM; route++)
	{
		kidRoute_[route] = routeArray[route];
	}

	int trueNum = 0;

	int posHandle = MV1LoadModel("Data/Enemy/Kid/mapKidBone.x");
	MV1SetPosition(posHandle,VGet(-20.0f, -1.0f, 0.0f));

	for (int arrayNum = 0; arrayNum < INTER_BONE_MAX_NUM; arrayNum++)
	{
		if (arrayNum % 2)
		{
			frmPosArray_[trueNum] = MV1GetFramePosition(posHandle, arrayNum);
			trueNum++;
		}	
	}
	
	pos_ = frmPosArray_[initRouteNum_];		//子供の位置設定

	pos_.y = KID_HIGHT;			//子供が埋まらないようにする

	currentRoute_ = initRouteNum_;

	// AI状態遷移アルゴリズムを設定
	enemy_ai_ = new AIKid;
	ai_state_ = AIBase::KID_WALK;

	changeFlg_ = true;
	rad_ = KID_RADIUS;
	moveFlg_ = true;

	if (initRouteNum_ == 0 || initRouteNum_ == 6)
	{
		walkType_ = WALK_ROTATION;
	}
	else if (initRouteNum_ == 4 || initRouteNum_ == 10 || initRouteNum_ == 12)
	{
		walkType_ = WALK_START_END;
	}

	selectType_ = START_FROM_MOVE;

	//当たり判定を生成
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_.pos_ = pos_;
	colData_.cubeRad_ = COL_RADIUS;
	colData_.useFlg_ = true;
	colData_.myList_ = COL_CHECK_KID;
	colData_.type_.pawn_ = CHECK_BOX_HIT;
	colData_.type_.static_ = CHECK_BOX_NONE;
	colData_.type_.dynamic_ = CHECK_BOX_NONE;
	colData_.object_ = OBJECT_DYNAMIC;
	colData_.shapeCol_ = SHAPE_CUBE;

	colNum_ = collision->CreateCol(&colData_);
}

//読み込み（ロード）
void CKid::Load()
{
	//モデル読み込み
	hndl_ = MV1LoadModel("Data/Enemy/Kid/enemy_kid.x");
}

//毎フレーム呼ぶ処理（操作）
void CKid::Step()
{
	Hit();

	//前回の座標を格納
	oldPos_ = pos_;

	// アニメーションに使うint型のフレーム数加算
	frm_int_++;

	// 現在アニメが終了したか
	end_animFlg_ = IsEndAnim();

	// 次のAI状態を設定
	ai_state_ = enemy_ai_->GetNextState(this);

	// AI更新
	StepAI();

	// フラグがONならボスが常にプレイヤーの方を向く
	Target(findFlg_);
	
	if (walkType_ == WALK_START_END)
	{
		StartEnd();
	}
	else
	{
		Rotation();
	}
}


//更新
void CKid::Update()
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

	if(moveFlg_)
		Move(dir_);

	//座標確定
	MV1SetPosition(hndl_, pos_);
	//アニメーション更新
	CAnim3D::UpdateAnim();
	
	//当たり判定関係更新
	CCollisionManager::GetInstance()->SetUpdateColInfo(colNum_, pos_, colData_.useFlg_);
}

void CKid::Hit()
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
				findFlg_ = true;
				changeFlg_ = true;
				colData_.useFlg_ = false;
				checkFlg[COL_CHECK_PLAYER] = true;
			}
		}
	}
}


//描画
void CKid::Draw()
{
	MV1DrawModel(hndl_);
}


//削除
void CKid::Delete()
{
	MV1DeleteModel(hndl_);
}



//後処理
void CKid::Fin()
{
	//Deleteが呼ばれていないなら
	if (hndl_ != 0)
	{
		//削除を呼んでおく
		Delete();
	}
}


//クローン関数
CKid* CKid::Clone()
{
	return nullptr;
}



//移動処理
void CKid::Move(int dir)
{
	if (dir_ == FRONT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, KID_FRONT);
	}
	else if (dir_ == BACK_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, KID_BACK);
	}
	else if (dir_ == RIGHT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, KID_RIGHT);
	}
	else if (dir_ == LEFT_MOVE) {
		pos_ = CMyMath::VecAdd(pos_, KID_LEFT);
	}
}


void CKid::Rotation()
{
	
	VECTOR originVec;
	int boneNum = currentRoute_;

	if (kidRoute_[boneNum] != ROTATION)
	{
		//現在のボーンから次に進むボーンへのベクトルを取得する
		originVec = CMyMath::VecCreate(frmPosArray_[boneNum], frmPosArray_[boneNum + 1]);
	}
	else if (kidRoute_[boneNum] == ROTATION)
	{
		//ローテーションのボーンから最初のボーンへのベクトルを取得する
		originVec = CMyMath::VecCreate(frmPosArray_[boneNum], frmPosArray_[initRouteNum_]);
	}
	
	

	//2つのボーンのベクトルの差が大きい方に進みたい
	if (CMyMath::Abs(originVec.x) > CMyMath::Abs(originVec.z))
	{
		if (originVec.x > 0.0f){
			dir_ = RIGHT_MOVE;
		}
		else {
			dir_ = LEFT_MOVE;
		}
	}
	else
	{
		if (originVec.z > 0.0f){
			dir_ = FRONT_MOVE;
		}
		else{
			dir_ = BACK_MOVE;
		}
	}

	if (kidRoute_[boneNum] != ROTATION)
	{
		if (dir_ == RIGHT_MOVE){
			if (pos_.x > frmPosArray_[boneNum + 1].x){
				currentRoute_++;
			}
		}
		if (dir_ == LEFT_MOVE){
			if (pos_.x < frmPosArray_[boneNum + 1].x){
				currentRoute_++;
			}
		}
		if (dir_ == FRONT_MOVE){
			if (pos_.z > frmPosArray_[boneNum + 1].z){
				currentRoute_++;
			}
		}
		if (dir_ == BACK_MOVE){
			if (pos_.z < frmPosArray_[boneNum + 1].z){
				currentRoute_++;
			}
		}
	}

	if (kidRoute_[boneNum] == ROTATION)
	{
		if (dir_ == RIGHT_MOVE) {
			if (pos_.x > frmPosArray_[initRouteNum_].x) {
				currentRoute_ = initRouteNum_;
			}
		}
		if (dir_ == LEFT_MOVE) {
			if (pos_.x < frmPosArray_[initRouteNum_].x) {
				currentRoute_ = initRouteNum_;
			}
		}
		if (dir_ == FRONT_MOVE) {
			if (pos_.z > frmPosArray_[initRouteNum_].z) {
				currentRoute_ = initRouteNum_;
			}
		}
		if (dir_ == BACK_MOVE) {
			if (pos_.z < frmPosArray_[initRouteNum_].z) {
				currentRoute_ = initRouteNum_;
			}
		}
	}
}

void CKid::StartEnd()
{
	VECTOR nextVec = {0};
	int boneNum = currentRoute_;
	
	if (kidRoute_[boneNum] == START){
		selectType_ = START_FROM_MOVE;
	}
	else if (kidRoute_[boneNum] == END){
		selectType_ = END_FROM_MOVE;
	}
	
	if (selectType_ == START_FROM_MOVE){
		//次のボーンまでのベクトルを取得
		nextVec = CMyMath::VecCreate(frmPosArray_[boneNum], frmPosArray_[boneNum + 1]);
	}
	else if (selectType_ == END_FROM_MOVE){
		//次のボーンまでのベクトルを取得
		nextVec = CMyMath::VecCreate(frmPosArray_[boneNum], frmPosArray_[boneNum - 1]);
	}

	//2つのボーンのベクトルの差が大きい方に進みたい
	if (CMyMath::Abs(nextVec.x) > CMyMath::Abs(nextVec.z))
	{
		if (nextVec.x > 0.0f){
			dir_ = RIGHT_MOVE;
		}
		else{
			dir_ = LEFT_MOVE;
		}
	}
	else
	{
		if (nextVec.z > 0.0f){
			dir_ = FRONT_MOVE;
		}
		else{
			dir_ = BACK_MOVE;
		}
	}

	if (selectType_ == START_FROM_MOVE)
	{
		//目標のボーンを通り過ぎた時現在のボーンを目標のボーン番号に変更
		if (dir_ == RIGHT_MOVE) {
			if (pos_.x > frmPosArray_[boneNum + 1].x) {
				currentRoute_++;
			}
		}
		if (dir_ == LEFT_MOVE) {
			if (pos_.x < frmPosArray_[boneNum + 1].x) {
				currentRoute_++;
			}
		}
		if (dir_ == FRONT_MOVE) {
			if (pos_.z > frmPosArray_[boneNum + 1].z) {
				currentRoute_++;
			}
		}
		if (dir_ == BACK_MOVE) {
			if (pos_.z < frmPosArray_[boneNum + 1].z) {
				currentRoute_++;
			}
		}
	}
	else if (selectType_ == END_FROM_MOVE)
	{
		//目標のボーンを通り過ぎた時現在のボーンを目標のボーン番号に変更
		if (dir_ == RIGHT_MOVE) {
			if (pos_.x > frmPosArray_[boneNum - 1].x) {
				currentRoute_--;
			}
		}
		if (dir_ == LEFT_MOVE) {
			if (pos_.x < frmPosArray_[boneNum - 1].x) {
				currentRoute_--;
			}
		}
		if (dir_ == FRONT_MOVE) {
			if (pos_.z > frmPosArray_[boneNum - 1].z) {
				currentRoute_--;
			}
		}
		if (dir_ == BACK_MOVE) {
			if (pos_.z < frmPosArray_[boneNum - 1].z) {
				currentRoute_--;
			}
		}
	}
}


void CKid::Target(bool flg)
{
	if (flg)
	{
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//プレイヤーを向く処理
		VECTOR vec = CMyMath::VecCreate(pos_, player->GetPosition());
		vec.y = 0.0f;
		rot_.y = atan2f(vec.x, vec.z);
	}
}


//---------------ここから下がステータス関係処理--------------------------
void CKid::StepAI()
{
	// 現在の状態から各AI処理へ(関数ポインタを使うとなお良い)
	switch (ai_state_) {
	case AIBase::KID_WALK:	//歩行状態更新
		StepWalk();
		break;

	case AIBase::KID_BIND:// 捕縛状態更新
		StepBind();
		break;
	}
}

void CKid::StepWalk()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestLoop(WALK, 1.0f, (int)-1, (bool)-1);
		findFlg_ = false;
		changeFlg_ = false;
		frm_int_ = 0;
		moveFlg_ = true;
	}

	if (frm_int_ > BIND_FRM)
	{
		colData_.useFlg_ = true;
	}
}

void CKid::StepBind()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(BIND, 1.0f, (int)-1, (bool)-1);
		changeFlg_ = false;
		moveFlg_ = false;
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		player->AddDamage(KID_DMG);
		colData_.useFlg_ = false;
	}

	
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();
	VECTOR playerOldPos = player->GetOldPosition();
	//捕縛処理
	player->SetPosition(playerOldPos);
}
