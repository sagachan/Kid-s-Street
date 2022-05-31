//TitleScene.cpp
//タイトルシーン

#include "TitleScene.h"
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

CTitleScene::CTitleScene()
{
	Init();
}

CTitleScene::~CTitleScene()
{
}

//初期化
void CTitleScene::Init()
{
	//UI管理生成
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//背景生成
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/openning.jpg");

	//音初期化
	CSound::InitSound();
}


//読み込み
void CTitleScene::Load()
{
	//音読み込み
	CSound::LoadBGM(CSound::BGM_TITLE);
}


//各変数などに初期値を設定（セット）
void CTitleScene::Set()
{
	//音再生
	CSound::PlayBGM(CSound::BGM_TITLE);
}


//毎フレーム呼ぶ処理
void CTitleScene::Step()
{
	CInput* input = CInput::GetInstance();

	if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//プレイシーンへ変更
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_TUTORIAL_MAIN);
	}


	//UI管理ステップ
	CGameUIManager::GetInstance()->Step();
}


//描画
void CTitleScene::Draw()
{
	//UI管理描画
	CGameUIManager::GetInstance()->Draw();
}


//後処理
void CTitleScene::Fin()
{
	//UI管理後処理
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();
}