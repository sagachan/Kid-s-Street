//Navi.cpp

#include "Navi.h"
#include "DxLib.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Scene/SaveScene/SaveScene.h"

namespace
{
	const VECTOR TARGET_WALL_POS = VGet(-55.0f, 2.0f, 2250.0f);
}


CNavi::CNavi()
	:type_(0){}

CNavi::~CNavi()
{
	DeleteModel();
}

//読み込み
void CNavi::Load()
{
	LoadModel("Data/UI/Navi/arrow.x");

	CSaveScene* save = CSaveScene::GetInstance();
	if (!save->GetBossFlg()) {
		type_ = NAVI_END;
	}
}

//毎フレーム呼ぶ処理
void CNavi::Step()
{
	if (type_ == NAVI_END)
		return;

	//位置を常にプレイヤーの場所に設定する
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	pos_ = player->GetPosition();

	//naviタイプが今も正しいか確認
	CheckNaviType();
	UpdateNaviRot();

	MV1SetPosition(hndl_,pos_);
	MV1SetRotationXYZ(hndl_, rot_);
}

void CNavi::Draw()
{
	if (type_ == NAVI_END)
		return;

	MV1DrawModel(hndl_);
}

void CNavi::CheckNaviType()
{
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	switch (type_){
	case NAVI_WALL:
		//もしプレイヤーが壁の奥に到達したら目的地を変える
		if (pos_.z > TARGET_WALL_POS.z)
			type_++;
		break;

	case NAVI_HOUSE:
		//もしボス戦が始まったならナビ終了
		if (!enemyManager->GetSceneFlg())
			type_++;
		break;

	case NAVI_END:
		break;
	}
}

void CNavi::UpdateNaviRot()
{
	VECTOR targetPos = { 0.0f };
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();

	switch (type_) {
	case NAVI_WALL:
		targetPos = TARGET_WALL_POS;
		break;

	case NAVI_HOUSE:
		targetPos = enemyManager->GetBoss()->GetPosition();
		break;
	}

	//目的地を向く処理
	VECTOR vec = CMyMath::VecCreate(pos_, targetPos);
	vec.y = 0.0f;
	rot_.y = atan2f(vec.x, vec.z);
	rot_.y += 1.6f;
}