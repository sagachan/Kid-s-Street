//GameUIHP.cpp

#include "GameUIHP.h"
#include "DxLib.h"
#include "../../Player/PlayerCommon.h"

namespace
{
	const int ORIGIN_LENGTH = 100;
}

CGameUIHP::CGameUIHP()
	:handle_(0)
{
}

CGameUIHP::~CGameUIHP()
{
}


//初期化
void CGameUIHP::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//読み込み
void CGameUIHP::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
}


//ステップ
void CGameUIHP::Step()
{
	//HPを確認してそれに応じてバーの拡縮率を下げることで
	//HPバーとして見せる
}

//描画
void CGameUIHP::Draw()
{
	float endPosX_ = endPos_.x * size_ / 100 + posX_;
	DrawExtendGraph((int)posX_, (int)posY_,
		(int)endPosX_, (int)endPos_.y, handle_,true);
}

//削除
void CGameUIHP::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//後処理
void CGameUIHP::Fin()
{
	//画像が削除できてないなら、削除を呼ぶ
	if (handle_) {
		Delete();
	}
}