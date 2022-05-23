

#include "GameUIItemBox.h"
#include "../../Item/UseItem/ItemManager.h"
#include "../../Item/GatherItem/GatherFactory/GatherManager.h"

namespace
{
	
}


CGameUIItemBox::CGameUIItemBox()
	:handle_(0)
	,id_(ITEM_ID_NONE)
{
}

CGameUIItemBox::~CGameUIItemBox()
{
}


//初期化
void CGameUIItemBox::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//読み込み
void CGameUIItemBox::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
	//ここで今読み込まれているアイテムの位置情報を
	//位置情報から確認してIDを取得
	id_ = CGatherManager::GetInstance()->CheckItemID(posX_);
}


//ステップ
void CGameUIItemBox::Step()
{
	
}


//描画
void CGameUIItemBox::Draw()
{
	//IDを使って今描画していいのかを確認する
	if(CItemManager::GetInstance()->IDFromKind(id_))
		DrawGraph((int)posX_, (int)posY_, handle_, true);
}


//削除
void CGameUIItemBox::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//後処理
void CGameUIItemBox::Fin()
{
	//画像が削除できてないなら、削除を呼ぶ
	if (handle_) {
		Delete();
	}
}