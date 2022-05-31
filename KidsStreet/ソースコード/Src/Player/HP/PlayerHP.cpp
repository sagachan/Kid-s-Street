//PlayerHP.cpp

#include "PlayerHP.h"
#include "DxLib.h"
#include "../../UI/GameUIManager.h"
#include "../PlayerManager.h"
#include "../PlayerCommon.h"


namespace
{
	
}


CPlayerHP::CPlayerHP()
{
	Init();
}

CPlayerHP::~CPlayerHP()
{

}

//初期化
void CPlayerHP::Init()
{
	//UI管理生成
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//生成
	hp_ = ui_manager->CreateUI(CGameUIManager::UI_TYPE_HP);
	hp_->Init(PLAYER_HP_POS.x, PLAYER_HP_POS.y);
	hp_->Load("Data/UI/HP/HP.png");
	hp_->SetEndPos(ORIGIN_HP_POS);
}

//読み込み
void CPlayerHP::Load()
{

}

//各変数などに初期値を設定（セット）
void CPlayerHP::Set()
{
	
}

//毎フレーム呼ぶ処理
void CPlayerHP::Step()
{
	

	//毎週プレイヤーのHPをUIに渡す
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	hp_->SetSize(player->GetHP());
}


//描画
void CPlayerHP::Draw()
{
	
}


//後処理
void CPlayerHP::Fin()
{
	//UI管理後処理
	CGameUIManager::GetInstance()->DeleteAll();
}