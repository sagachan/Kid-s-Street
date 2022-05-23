//子供クラス
#include "EnemyWallKid.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Item/GatherItem/GatherFactory/GatherManager.h"
#include "../../Item/ItemCommon.h"
#include "../EnemyManager.h"
#include "../EnemyCommon.h"

namespace{
	const float		KID_RADIUS = 8.0f;										//子供の当たり判定範囲
	const int		KID_DMG = 5;
	const int		BIND_TIME = 120;
}

//コンストラクタ
CWallKid::CWallKid()
	:dir_(MOVE_INIT){
	
}

//デストラクタ
CWallKid::~CWallKid(){
	Fin();
}

//セット
void CWallKid::SetPos(VECTOR pos, CEnemyBase::MOVE_DIR dir)
{
	pos_ = pos;
	dir_ = dir;

}


//セット
void CWallKid::Set()
{
	LoadModel("Data/Enemy/Kid/mapKidBone.x");
	MV1SetPosition(hndl_, pos_);

	rad_ = KID_RADIUS;

	//向きタイプによって回転
	if (dir_ == FRONT_MOVE){
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_FRONT);
	}
	if (dir_ == BACK_MOVE){
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_BACK);
	}
	if (dir_ == RIGHT_MOVE){
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_RIGHT);
	}
	if (dir_ == LEFT_MOVE){
		MV1SetRotationXYZ(hndl_, ENEMY_ROT_LEFT);
	}
}

//読み込み（ロード）
void CWallKid::Load(){
	//モデル読み込み
	LoadModel("Data/Enemy/Kid/enemy_kid.x");
	//アニメーション処理
	CAnim3D::RequestLoop(BIND, 1.0f, (int)-1, (bool)-1);
}

//描画
void CWallKid::Draw(){
	CAnim3D::UpdateAnim();
	MV1DrawModel(hndl_);
}

//削除
void CWallKid::Delete(){
	hndl_ = MV1DeleteModel(hndl_);
}

//後処理
void CWallKid::Fin(){
	//Deleteが呼ばれていないなら
	if (hndl_ != 0){
		//削除sを呼んでおく
		Delete();
	}
}

void CWallKid::Hit()
{
	//ハンドルが削除されていたら処理しない
	if (hndl_ != 0)
	{
		//アイテムが得られているならハンドルを削除する
		bool* gatherFlg = CGatherManager::GetInstance()->GetGatherItem();
		if (gatherFlg[GLOVE]) {
			Delete();
		}
		//プレイヤーがアイテムを持たずにこの子供たちよりもｚ方向に進もうとしたら前回座標に戻してUI表示
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		if (pos_.z < player->GetPosition().z)
		{
			player->HitSet();
			CEnemyManager::GetInstance()->GetKidUI()->SetKidFlg(true);
			CGameUIManager::GetInstance()->SetInputFlg(true);
		}

	}
}
