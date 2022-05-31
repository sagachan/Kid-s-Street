//GameUIButton.cpp
//UIボタンクラス

#include "GameUIButton.h"
#include "DxLib.h"

CGameUIButton::CGameUIButton()
	:handle_(0)
{
}

CGameUIButton::~CGameUIButton()
{
}


//初期化
void CGameUIButton::Init(float posX, float posY)
{
	posX_ = posX;
	posY_ = posY;
}


//読み込み
void CGameUIButton::Load(const char* file_path)
{
	handle_ = LoadGraph(file_path);
}


//ステップ
void CGameUIButton::Step()
{
	//ボタンの更新処理
}


//描画
void CGameUIButton::Draw()
{
	if (!drawFlg_)
	{
		DrawGraph((int)posX_, (int)posY_, handle_, true);
	}
}
	


//削除
void CGameUIButton::Delete()
{
	DeleteGraph(handle_);
	handle_ = 0;
}


//後処理
void CGameUIButton::Fin()
{
	//画像が削除できてないなら、削除を呼ぶ
	if (handle_) {
		Delete();
	}
}