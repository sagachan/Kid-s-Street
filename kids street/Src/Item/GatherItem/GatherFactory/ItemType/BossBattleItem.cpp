

#include "BossBattleItem.h"
#include "DxLib.h"
#include "../../../ItemCommon.h"
#include "../GatherManager.h"

namespace
{
	const float ITEM_ROT_SPD = 0.025f;
}

CBossBattleItem::CBossBattleItem()
	:handle_(0)
	,id_(ITEM_ID_NONE)
	,itemRot_({0.0f})
{
}

CBossBattleItem::~CBossBattleItem()
{
}


//初期化
void CBossBattleItem::Init(VECTOR pos)
{
	itemPos_ = pos;
}


//読み込み
void CBossBattleItem::Load(const char* file_path)
{
	handle_ = MV1LoadModel(file_path);
	MV1SetPosition(handle_, itemPos_);
	MV1SetScale(handle_, ITEM_SCALE);

	////ここで自分のIDを獲得
	id_ = CGatherManager::GetInstance()->CheckItemID(itemPos_);
}


//ステップ
void CBossBattleItem::Step()
{
	itemRot_.y += ITEM_ROT_SPD;
}


//描画
void CBossBattleItem::Draw()
{
	MV1SetRotationXYZ(handle_, itemRot_);
	if(!CGatherManager::GetInstance()->GetIDFlg(id_))
 	MV1DrawModel(handle_);
}


//削除
void CBossBattleItem::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
}


//後処理
void CBossBattleItem::Fin()
{
	//削除できてないなら、削除を呼ぶ
	if (handle_) {
		Delete();
	}
}