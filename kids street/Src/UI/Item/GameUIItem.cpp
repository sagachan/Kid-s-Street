

#include "GameUIItem.h"
#include "DxLib.h"

namespace
{
	
}

CGameUIItem::CGameUIItem()
	:handle_(0)
	,id_(ITEM_ID_NONE)
{
}

CGameUIItem::~CGameUIItem()
{
}


//初期化
void CGameUIItem::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//読み込み
void CGameUIItem::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
	//ここで今読み込まれているアイテムの位置情報を
	//位置情報から確認してIDを取得
	id_ = CGatherManager::GetInstance()->CheckItemID(posX_);
}

//ステップ
void CGameUIItem::Step()
{
	
}


//描画
void CGameUIItem::Draw()
{
	//IDを使って今描画していいのかを確認する
	if(CGatherManager::GetInstance()->GetIDFlg(id_))
		DrawGraph((int)posX_, (int)posY_, handle_, true);
}


//削除
void CGameUIItem::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//後処理
void CGameUIItem::Fin()
{
	//画像が削除できてないなら、削除を呼ぶ
	if (handle_) {
		Delete();
	}
}