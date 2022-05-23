//TutorialItemScene.cpp
//タイトルシーン

#include "TutorialItemScene.h"
#include "../SceneManager.h"
#include "../../Library/Input/Input.h"
#include "DxLib.h"
#include <math.h>
#include "../../Common.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../UI/GameUIManager.h"
#include "../../Library/Sound/Sound.h"

namespace
{
	
}

CTutorialItemScene::CTutorialItemScene()
{
	Init();
}

CTutorialItemScene::~CTutorialItemScene()
{
}

//初期化
void CTutorialItemScene::Init()
{
	//UI管理生成
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//背景生成
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/TutorialItem.png");
}


//読み込み
void CTutorialItemScene::Load()
{


}


//各変数などに初期値を設定（セット）
void CTutorialItemScene::Set()
{
	
}


//毎フレーム呼ぶ処理
void CTutorialItemScene::Step()
{
	CInput* input = CInput::GetInstance();

	if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//プレイシーンへ変更
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_PLAY);
	}

	//UI管理ステップ
	CGameUIManager::GetInstance()->Step();

}


//描画
void CTutorialItemScene::Draw()
{
	//UI管理描画
	CGameUIManager::GetInstance()->Draw();
}


//後処理
void CTutorialItemScene::Fin()
{
	//UI管理後処理
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();

	//音後処理
	CSound::FinSound();
}