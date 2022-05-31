//GameUIAssert.cpp

#include "GameUIAssert.h"
#include "DxLib.h"
#include "../../Player/PlayerCommon.h"

namespace
{
}

CGameUIAssert::CGameUIAssert()
	:handle_(0)
{
}

CGameUIAssert::~CGameUIAssert()
{
}


//初期化
void CGameUIAssert::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//読み込み
void CGameUIAssert::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
}


//ステップ
void CGameUIAssert::Step()
{
	
}

//描画
void CGameUIAssert::Draw()
{
	if(drawFlg_)
	DrawGraph((int)posX_, (int)posY_, handle_, true);
}

//削除
void CGameUIAssert::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//後処理
void CGameUIAssert::Fin()
{
	//画像が削除できてないなら、削除を呼ぶ
	if (handle_) {
		Delete();
	}
}