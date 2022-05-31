//SceneManager.cpp
//シーン管理
//各シーンへのアクセスは必ずCSceneManagerを経由

#include "SceneManager.h"
#include "PlayScene.h"
#include "Title/TitleScene.h"
#include "GameClear/GameClearScene.h"
#include "GameOver/GameOverScene.h"
#include "Tutorial/TutorialMainScene.h"
#include "Tutorial/TutorialItemScene.h"
#include "../Scene/SaveScene/SaveScene.h"

//CSceneManagerの実体宣言、初期化
CSceneManager* CSceneManager::instance_ = nullptr;

CSceneManager::CSceneManager()
:scene_(nullptr)
, m_eCurrentSceneState(SCENE_STATE_INIT)
{
	Init();
}

CSceneManager::~CSceneManager()
{
	Fin();
}


//初期化
void CSceneManager::Init()
{
	//ここはシーン管理の初期化であって、
	//各シーンの初期化ではない
	CSaveScene::CreateInstance();
}


//ループ
void CSceneManager::Loop()
{
	//現在のシーンの状態によって、処理を振り分ける
	switch (m_eCurrentSceneState)
	{

	//シーン初期化
	case SCENE_STATE_INIT:
		scene_->Init();
		m_eCurrentSceneState = SCENE_STATE_LOAD;
		break;

	//シーン読み込み
	case SCENE_STATE_LOAD:
		scene_->Load();
		m_eCurrentSceneState = SCENE_STATE_SET;
		break;

	//シーンセット
	case SCENE_STATE_SET:
		scene_->Set();
		m_eCurrentSceneState = SCENE_STATE_LOOP;

	//シーン繰り返し
	case SCENE_STATE_LOOP:
		scene_->Step();
		scene_->Draw();	//描画はステップの後に呼ぶ
		break;

	//シーン後処理
	case SCENE_STATE_FIN:
		scene_->Fin();
		ChangeNextScene();
		break;
	}
}


//後処理
void CSceneManager::Fin()
{
	CSaveScene::DeleteInstance();
}


//１番最初のシーンを開始する
void CSceneManager::StartFirstScene(SCENE_ID sceneID)
{
	//既に何かシーンが動いてるのであれば即終了
	if (scene_)return;

	//シーンを生成して初期化から開始する
	CreateScene(sceneID);
	m_eCurrentSceneID = sceneID;
	m_eCurrentSceneState = SCENE_STATE_INIT;
}


//引数のシーンに変更する
void CSceneManager::ChangeScene(SCENE_ID sceneID)
{
	//次に遷移するシーンを覚えておいて終了処理へ
	m_eNextSceneID = sceneID;
	m_eCurrentSceneState = SCENE_STATE_FIN;
}


//シーンを生成する
void CSceneManager::CreateScene(SCENE_ID sceneID)
{
	//シーンを生成
	switch (sceneID) 
	{
	case SCENE_ID_TITLE: scene_ = new CTitleScene; break;
	case SCENE_ID_TUTORIAL_MAIN:scene_ = new CTutorialMainScene; break;
	case SCENE_ID_TUTORIAL_ITEM:scene_ = new CTutorialItemScene; break;
	case SCENE_ID_PLAY: scene_ = new CPlayScene; break;
	case SCENE_ID_GAME_OVER: scene_ = new CGameOverScene; break;
	case SCENE_ID_GAME_CLEAR: scene_ = new CGameClearScene; break;
	}
}


//次のシーンに遷移
void CSceneManager::ChangeNextScene()
{
	//終了したシーンを削除
	delete scene_;
	//次のシーンを生成
	CreateScene(m_eNextSceneID);
	//現在のシーンID設定
	m_eCurrentSceneID = m_eNextSceneID;
	//状態を初期化に戻す
	m_eCurrentSceneState = SCENE_STATE_INIT;
}