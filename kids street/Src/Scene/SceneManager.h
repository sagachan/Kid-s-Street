//SceneManager.h
//シーン管理
//各シーンへのアクセスは必ずCSceneManagerを経由

#pragma once

#include "SceneBase.h"

class CSceneManager
{
public:
	//シーン状態
	enum SCENE_STATE {
		SCENE_STATE_INIT,	//初期化
		SCENE_STATE_LOAD,	//読み込み
		SCENE_STATE_SET,	//セット
		SCENE_STATE_LOOP,	//ループ
		SCENE_STATE_FIN,	//後処理
	};

	//シーンID
	enum SCENE_ID
	{
		SCENE_ID_TITLE,				//タイトルシーン
		SCENE_ID_TUTORIAL_MAIN,		//チュートリアルメインシーン
		SCENE_ID_TUTORIAL_ITEM,		//チュートリアルアイテムシーン
		SCENE_ID_PLAY,				//プレイシーン
		SCENE_ID_GAME_OVER,			//ゲームオーバーシーン
		SCENE_ID_GAME_CLEAR,		//ゲームクリアシーン
	};

public:
	static void CreateInstance() { if (!instance_) instance_ = new CSceneManager; }
	static CSceneManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:

	CSceneManager();
	~CSceneManager();

	//初期化
	void Init();

	//ループ
	void Loop();

	//後処理
	void Fin();

	//１番最初のシーンを開始する
	void StartFirstScene(SCENE_ID sceneID);

	//引数のシーンに変更する
	void ChangeScene(SCENE_ID sceneID);

private:
	//シーンを生成する
	void CreateScene(SCENE_ID sceneID);

	//次の画面に遷移させる
	void ChangeNextScene();

private:
	//インスタンス
	static CSceneManager* instance_;

	//現在のシーンID
	SCENE_ID m_eCurrentSceneID;
	SCENE_ID m_eNextSceneID;
	SCENE_STATE m_eCurrentSceneState;

	//基底ポインタ１つで管理する
	CSceneBase* scene_;
};