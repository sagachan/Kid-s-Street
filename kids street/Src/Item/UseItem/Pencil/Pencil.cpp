//Pencil.cpp
//鉛筆クラス

#include "../../../Library/MyMath/MyMath.h"
#include "../../../Player/PlayerManager.h"
#include "../../../Enemy/EnemyManager.h"
#include "../ItemManager.h"
#include "../../../Enemy/EnemyBase.h"
#include "Pencil.h"
#include "../../../Library/Input/Input.h"

namespace
{
	const float SCALE = 1.0;						//大きさ
	const VECTOR POS = VGet(0.0f,0.0f,0.0f);		//位置
	const VECTOR ROT = VGet(4.71f,0.0f,0.0f);		//回転値
	const float SPEED = 1.0;						//飛ぶ速度
	const float SIMPLE_HIT_RADIUS = 1.0;			//簡易当たり判定用
	const int DMG = 15;
	
}

void CPencil::Load()
{
	//モデルハンドル読み込み
	LoadModel("Data/Item/Enpitu.x");
	id_ = ITEM_ID_PENCIL;
}


void CPencil::Set()
{

	add_pos_ = SPEED;
	rot_ = ROT;
	dmg_ = DMG;
	rad_ = SIMPLE_HIT_RADIUS;
}


void CPencil::Step()
{
	//プレイヤークラス取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	
	//持っているアイテムがプレイヤーの向いている方向を向く処理
	rot_.y = player->GetRot().y;
}


void CPencil::Draw()
{
	//モデルの回転
	MV1SetRotationXYZ(hndl_, rot_);

	//モデルの位置座標セット
	MV1SetPosition(hndl_, pos_);
	MV1SetScale(hndl_, scale_);
	//モデル描画
	MV1DrawModel(hndl_);
}

void CPencil::Fin()
{
	DeleteModel();
}