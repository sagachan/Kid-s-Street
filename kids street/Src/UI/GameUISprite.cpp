//GameUISprite.cpp
//UIスプライトクラス

#include "GameUISprite.h"
#include "DxLib.h"

CGameUISprite::CGameUISprite()
	:handle_(0)
{
}

CGameUISprite::~CGameUISprite()
{
}


//初期化
void CGameUISprite::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//読み込み
void CGameUISprite::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
}


//ステップ
void CGameUISprite::Step()
{
	//スプライトの更新処理
}


//描画
void CGameUISprite::Draw()
{
	DrawGraph((int)posX_, (int)posY_, handle_, true);
}


//削除
void CGameUISprite::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//後処理
void CGameUISprite::Fin()
{
	//画像が削除できてないなら、削除を呼ぶ
	if (handle_) {
		Delete();
	}
}