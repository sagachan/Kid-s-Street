//FrameHP.cpp

#include "FrameHP.h"
#include "DxLib.h"
#include "../../UI/GameUIManager.h"


namespace
{

}


CFrameHP::CFrameHP()
{
	Init();
}

CFrameHP::~CFrameHP()
{

}

//初期化
void CFrameHP::Init()
{
	//UI管理生成
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//生成
	CGameUI* frame = ui_manager->CreateUI(CGameUIManager::UI_TYPE_BUTTON);
	frame->Init(700.0f, 650.0f);
	frame->Load("Data/UI/HP/FrameHP.png");
	
}

//読み込み
void CFrameHP::Load()
{

}

//各変数などに初期値を設定（セット）
void CFrameHP::Set()
{

}

//毎フレーム呼ぶ処理
void CFrameHP::Step()
{

	//UI管理ステップ
	CGameUIManager::GetInstance()->Step();
}


//描画
void CFrameHP::Draw()
{
	
}


//後処理
void CFrameHP::Fin()
{
	//UI管理後処理
	CGameUIManager::GetInstance()->DeleteAll();

}