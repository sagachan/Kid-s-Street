//GameClearScene.cpp
//ゲームクリアシーン

#include "GameClearScene.h"
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


CGameClearScene::CGameClearScene()
{
	Init();
}

CGameClearScene::~CGameClearScene()
{
}

//初期化
void CGameClearScene::Init()
{
	//UI管理生成
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//背景生成
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/GameClear.jpg");

	//音初期化
	CSound::InitSound();
}

//読み込み
void CGameClearScene::Load()
{
	//音読み込み
	CSound::LoadBGM(CSound::BGM_CLEAR);
}

//各変数などに初期値を設定（セット）
void CGameClearScene::Set()
{
	//音再生
	CSound::PlayBGM(CSound::BGM_CLEAR);
}

//毎フレーム呼ぶ処理
void CGameClearScene::Step()
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
void CGameClearScene::Draw()
{
	//UI管理描画
	CGameUIManager::GetInstance()->Draw();
}


//後処理
void CGameClearScene::Fin()
{
	//UI管理後処理
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();

	//音後処理
	CSound::FinSound();
}