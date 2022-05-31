//Pole.cpp
//フィールドクラス
//当たり判定や特別な処理を持たないオブジェクト関係

#include "Pole.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"

//フィールド関連
namespace
{
	VECTOR FIELD_POS = VGet(-1550.0f, 1.0f, 1750.0f);	//フィールドの座標
	VECTOR POLE_ROT = VGet(0.0f, 0.0f, 0.0f);
}

CPole::CPole()
	:posFlg_(true)
{
	
}

//デストラクタ
CPole::~CPole()
{
	Fin();
}

void CPole::Set()
{
	MV1SetPosition(hndl_, FIELD_POS);
}

void CPole::Load()
{
	LoadModel("Data/Map/Field/UtilityPole.x");
}


void CPole::Update()
{
	//ボスがこの電柱をつかうかどうか
	CBoss* boss = CEnemyManager::GetInstance()->GetBoss();
	if (boss->ai_state_ == AIBase::BOSS_SLASH)
		posFlg_ = false;
	else
		posFlg_ = true;

	//使われてないなら初期位置、初期回転値に戻す
	if (posFlg_){
		pos_ = FIELD_POS;
		rot_ = POLE_ROT;
	}
	

	MV1SetPosition(hndl_, pos_);
	MV1SetRotationXYZ(hndl_, rot_);
}


void CPole::Draw()
{
	MV1DrawModel(hndl_);
}


void CPole::Delete()
{
	DeleteModel();
}


void CPole::Fin()
{
	if (hndl_ != 0){
		//Deleteを呼んでおく
		Delete();
	}
}

