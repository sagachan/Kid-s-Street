
#include "CollisionManager.h"
#include "../Library/MyMath/MyMath.h"
#include "ColField/ColField.h"

//CEnemyManagerの実体宣言、初期化
CCollisionManager* CCollisionManager::instance_ = nullptr;

CCollisionManager::CCollisionManager()
{
	Init();
}

CCollisionManager::~CCollisionManager()
{
	DeleteAll();
}

void CCollisionManager::Init()
{
	vectorMax_ = 0;
}
void CCollisionManager::Step()
{
	//マップとの当たり判定関係更新
	CColField::CheckColField();

	//まずは前回の判定結果の初期化
	for (auto itr = col_vec_.begin(); itr != col_vec_.end(); itr++) {
		(*itr)->hitFlg_ = false;
		for (int num = 0; num < COL_CHECK_MAX; num++){
			(*itr)->list_[num] = COL_NONE;
		}

	}
	//ここで全てを参照してタイプごとに処理を分ける
	for (auto masterItr = col_vec_.begin(); masterItr != col_vec_.end(); masterItr++) {
		for (auto targetItr = col_vec_.begin(); targetItr != col_vec_.end(); targetItr++) {
			//ターゲットの当たり判定タイプを格納
			OBJECT_TYPE object = (*targetItr)->object_;
			bool checkFlg = false;
			//両方の使用フラグが立っているなら通る
			if ((*masterItr)->useFlg_ && (*targetItr)->useFlg_){
				//お互いのタイプが違うなら通る
				if ((*masterItr)->myList_ != (*targetItr)->myList_)
				{
					//ターゲットの当たり判定タイプに対する元の当たり判定の
					//チェックボックスがNONE以外を選んでいるなら
					if (object == OBJECT_PAWN && (*masterItr)->type_.pawn_ != CHECK_BOX_NONE) {
						checkFlg = true;
					}
					if (object == OBJECT_STATIC && (*masterItr)->type_.static_ != CHECK_BOX_NONE) {
						checkFlg = true;
					}
					if (object == OBJECT_DYNAMIC && (*masterItr)->type_.dynamic_ != CHECK_BOX_NONE) {
						checkFlg = true;
					}
				}
				if (checkFlg)
					CollisionCheck((*masterItr), (*targetItr));
			}
		}
	}
}

void CCollisionManager::CollisionCheck(COL_DATA* master, COL_DATA* target)
{
	for (int num = 0; num < COL_CHECK_MAX; num++){
		//別のタイミングですでに同リストのオブジェクトと触れている場合は終わる
		//先頭から情報を入れていくので空が見つかった時点で終わる
		if (master->list_[num] == target->myList_) {
			return;
		}
	}
	
	//当たり判定の形に依った処理を行う
	//両方ボックス
	if (master->shapeCol_ == SHAPE_CUBE && target->shapeCol_ == SHAPE_CUBE){
		if (CCollision::IsHitRect
			(master->pos_, master->cubeRad_.x, master->cubeRad_.y, master->cubeRad_.z,
			target->pos_, target->cubeRad_.x, target->cubeRad_.y, target->cubeRad_.z)){
			ColHitResult(master, target);
		}	
	}

	//masterが箱でtargetが球
	else if (master->shapeCol_ == SHAPE_CUBE && target->shapeCol_ == SHAPE_SPHERE){
		if(CCollision::IsHitSphereCube
			(master->pos_,master->cubeRad_.x, master->cubeRad_.y,master->cubeRad_.z, 
			target->pos_,target->sphereRad_)){
			ColHitResult(master, target);
		}
	}

	//masterが球でtargetが箱
	else if (master->shapeCol_ == SHAPE_SPHERE && target->shapeCol_ == SHAPE_CUBE){
		if (CCollision::IsHitSphereCube
			(target->pos_,target->cubeRad_.x, target->cubeRad_.y, target->cubeRad_.z,
			master->pos_, master->sphereRad_)){
			ColHitResult(master, target);
		}

	}

	//両方球
	else if (master->shapeCol_ == SHAPE_SPHERE && target->shapeCol_ == SHAPE_SPHERE){
		if (CCollision::IsHitSphere
			(master->pos_, master->sphereRad_, target->pos_, target->sphereRad_)){
			ColHitResult(master, target);
		}
	}

	
}

void CCollisionManager::ColHitResult(COL_DATA* master, COL_DATA* target)
{
	master->hitFlg_ = true;
	for (int num = 0; num < COL_CHECK_MAX; num++) {
		//先頭から順に参照して、中身がまだ入っていないものにいれる
		if (master->list_[num] == COL_NONE) {
			master->list_[num] = target->myList_;
			break;
		}
	}
}

void CCollisionManager::SetUpdateColInfo(int num, VECTOR pos, bool use)
{
	col_vec_[num]->pos_ = pos;
	col_vec_[num]->useFlg_ = use;
}

int CCollisionManager::CreateCol(COL_DATA* data)
{
	//現在の配列番号をローカル変数に入れて保持する
	//これを最後にリターンして各クラスに自分の当たり判定番号を持たせる
	int result = vectorMax_;

	//当たり判定構造体配列に情報を追加
	col_vec_.push_back(data); 

	//ベクター配列の中身を何かしらの事情で入れ替えることがあった時のために
	//配列番号を構造体でも管理しておく
	col_vec_[vectorMax_]->colNum_ = vectorMax_;
	vectorMax_++; 
	return result; 
}

//削除（vector内の当たり判定をすべて削除）
void CCollisionManager::DeleteAll()
{
	
	//配列を削除する
	col_vec_.clear();
	col_vec_.shrink_to_fit();
}