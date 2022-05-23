//Ruler.cpp

#include "../../../Library/MyMath/MyMath.h"
#include "../ItemManager.h"
#include "../../../Enemy/EnemyBase.h"
#include "Ruler.h"

namespace
{
	const float SCALE = 1.0;						//大きさ
	const VECTOR POS = VGet(0.0f,0.0f,0.0f);		//位置
	const VECTOR ROT = VGet(4.71f,1.6f,0.0f);		//回転値
	const float ROLL_SPD = 0.5f;							//回転速度
	const float SPEED = 1.0;						//飛ぶ速度
	const float SIMPLE_HIT_RADIUS = 4.0;			//簡易当たり判定用
	const int DMG = 15;
	
}

void CRuler::Load()
{
	//モデルハンドル読み込み
	LoadModel("Data/Item/Ruler.x");
	id_ = ITEM_ID_RULER;
}


void CRuler::Set()
{

	add_pos_ = SPEED;
	dmg_ = DMG;
	rad_ = SIMPLE_HIT_RADIUS;
	rot_ = ROT;
}


void CRuler::Step()
{
	//プレイヤークラス取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//持っているアイテムがプレイヤーの向いている方向を向く処理
	rot_.y = player->GetRot().y + ROT.y;

	rot_.x = ROT.x;
}

void CRuler::Update()
{
	rot_.x = 0.0f;
	rot_.y += ROLL_SPD;
}


void CRuler::Draw()
{
	//モデルの回転
	MV1SetRotationXYZ(hndl_, rot_);

	//モデルの位置座標セット
	MV1SetPosition(hndl_, pos_);
	MV1SetScale(hndl_, scale_);
	//モデル描画
	MV1DrawModel(hndl_);
}


void CRuler::Fin()
{
	DeleteModel();
}