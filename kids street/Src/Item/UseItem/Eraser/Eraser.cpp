//Eraser.cpp
//消しゴムクラス

#include "../../../Library/MyMath/MyMath.h"
#include "../../../Player/PlayerManager.h"
#include "../../../Enemy/EnemyManager.h"
#include "../ItemManager.h"
#include "../../../Enemy/EnemyBase.h"
#include "Eraser.h"
#include "../../../Library/Input/Input.h"
#include "../../../Library/MyMath/MyMath.h"

namespace
{
	const float SCALE = 1.0;//大きさ
	const VECTOR POS = VGet(0.0f, 0.0f, 0.0f);	//位置
	const VECTOR ROT = VGet(0.0f, 0.0f, 0.0f);	//回転値
	const float SPEED = 0.3f;		//飛ぶ速度
	const float SIMPLE_HIT_RADIUS = 2.0;			//簡易当たり判定用
	const int DMG = 10;
}

void CEraser::Load()
{
	//モデルハンドル読み込み
	LoadModel("Data/Item/BunishGom.x");
	id_ = ITEM_ID_ERASER;
}

void CEraser::Set()
{
	add_pos_ = SPEED;
	dmg_ = DMG;
	rad_ = SIMPLE_HIT_RADIUS;
	rot_ = ROT;
}

void CEraser::Draw()
{
	//モデルの回転
	MV1SetRotationXYZ(hndl_, rot_);
	//モデルの位置座標セット
	MV1SetPosition(hndl_, pos_);
	MV1SetScale(hndl_, scale_);
	//モデル描画
	MV1DrawModel(hndl_);
}

void CEraser::Fin()
{
	DeleteModel();
}

