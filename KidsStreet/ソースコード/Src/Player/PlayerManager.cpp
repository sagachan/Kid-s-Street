//PlayerManager.cpp
//プレイヤー管理
//CPlayerへのアクセスは必ずCPlayerManagerを経由

#include "PlayerManager.h"

//CPlayerManagerの実体宣言、初期化
CPlayerManager* CPlayerManager::instance_ = nullptr;


//コンストラクタ
CPlayerManager::CPlayerManager()
{
	//CPlayerのコンストラクタは自動で呼ばれます
}

//デストラクタ
CPlayerManager::~CPlayerManager()
{
	//CPlayerのデストラクタは自動で呼ばれます
}


//初期化
void CPlayerManager::Init()
{
	ui_[PLAYER_HP] = &hp_;
	ui_[FRAME_HP] = &hpFrame_;
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_INIT);
}


//読み込み
void CPlayerManager::Load()
{
	//プレイヤーの読み込み
	player_.Load();
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_LOAD);
}


//セット
void CPlayerManager::Set()
{
	//プレイヤーのセット
	player_.Set();

	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_SET);
}


//ステップ
void CPlayerManager::Step()
{
	//プレイヤーのステップ
	player_.Step();

	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_STEP);
}


//反映
void CPlayerManager::Update()
{
	//プレイヤーの反映
	player_.Update();
}


//描画
void CPlayerManager::Draw()
{
	//プレイヤーの描画
	player_.Draw();

	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_DRAW);
}


//削除
void CPlayerManager::Delete()
{
	//プレイヤー削除
	player_.Delete();

	
}


//後処理
void CPlayerManager::Fin()
{
	//プレイヤーの後処理を呼ぶ
	player_.Fin();

	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_FIN);
}