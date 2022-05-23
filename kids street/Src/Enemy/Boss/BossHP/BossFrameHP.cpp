//BossFrameHP.cpp

#include "BossFrameHP.h"
#include "DxLib.h"
#include "../../../UI/GameUIManager.h"


namespace
{

}


CBossFrameHP::CBossFrameHP()
{
	Init();
}

CBossFrameHP::~CBossFrameHP()
{

}

//初期化
void CBossFrameHP::Init()
{
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//生成
	CGameUI* hp = ui_manager->CreateUI(CGameUIManager::UI_TYPE_BUTTON);
	hp->Init(10.0f, 20.0f);
	hp->Load("Data/UI/HP/FrameHP.png");
}

//読み込み
void CBossFrameHP::Load()
{

}

//各変数などに初期値を設定（セット）
void CBossFrameHP::Set()
{

}

//毎フレーム呼ぶ処理
void CBossFrameHP::Step()
{

	//UI管理ステップ
	CGameUIManager::GetInstance()->Step();
}


//描画
void CBossFrameHP::Draw()
{
	
}


//後処理
void CBossFrameHP::Fin()
{
	//UI管理後処理
	CGameUIManager::GetInstance()->DeleteAll();

}