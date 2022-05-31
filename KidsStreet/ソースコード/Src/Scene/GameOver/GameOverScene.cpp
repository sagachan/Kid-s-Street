//GameOverScene.cpp
//ゲームオーバーシーン

#include "GameOverScene.h"
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


CGameOverScene::CGameOverScene()
{
	Init();
}

CGameOverScene::~CGameOverScene()
{
}

//初期化
void CGameOverScene::Init()
{
	//UI管理生成
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//背景生成
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/GameOver_BG.jpg");

	//音初期化
	CSound::InitSound();
}

//読み込み
void CGameOverScene::Load()
{
	//音読み込み
	CSound::LoadBGM(CSound::BGM_GAMEOVER);
}

//各変数などに初期値を設定（セット）
void CGameOverScene::Set()
{
	//音再生
	CSound::PlayBGM(CSound::BGM_GAMEOVER);
}

//毎フレーム呼ぶ処理
void CGameOverScene::Step()
{
	//Enterキーを押されたらタイトルシーンへ
	if (CInput::GetInstance()->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//タイトルシーンへ変更
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_TITLE);
	}

	//UI管理ステップ
	CGameUIManager::GetInstance()->Step();
}


//描画
void CGameOverScene::Draw()
{
	//UI管理描画
	CGameUIManager::GetInstance()->Draw();
}


//後処理
void CGameOverScene::Fin()
{
	//UI管理後処理
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();

	//音後処理
	CSound::FinSound();
}