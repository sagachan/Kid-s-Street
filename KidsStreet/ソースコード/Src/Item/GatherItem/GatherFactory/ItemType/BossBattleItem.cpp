

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


//������
void CBossBattleItem::Init(VECTOR pos)
{
	itemPos_ = pos;
}


//�ǂݍ���
void CBossBattleItem::Load(const char* file_path)
{
	handle_ = MV1LoadModel(file_path);
	MV1SetPosition(handle_, itemPos_);
	MV1SetScale(handle_, ITEM_SCALE);

	////�����Ŏ�����ID���l��
	id_ = CGatherManager::GetInstance()->CheckItemID(itemPos_);
}


//�X�e�b�v
void CBossBattleItem::Step()
{
	itemRot_.y += ITEM_ROT_SPD;
}


//�`��
void CBossBattleItem::Draw()
{
	MV1SetRotationXYZ(handle_, itemRot_);
	if(!CGatherManager::GetInstance()->GetIDFlg(id_))
 	MV1DrawModel(handle_);
}


//�폜
void CBossBattleItem::Delete()
{
	MV1DeleteModel(handle_);
	handle_ = 0;
}


//�㏈��
void CBossBattleItem::Fin()
{
	//�폜�ł��ĂȂ��Ȃ�A�폜���Ă�
	if (handle_) {
		Delete();
	}
}