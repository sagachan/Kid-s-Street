//CameraManager.h
//カメラ管理
//C***Cameraへのアクセスは必ずCCameraManagerを経由

#pragma once

#include "PlayCamera.h"
#include "DebugCamera.h"

//カメラ管理クラス
class CCameraManager
{
public:
	//カメラID
	enum CAMERA_ID
	{
		CAMERA_ID_PLAY,		//CPlayCamera
		CAMERA_ID_DEBUG,	//CDebugCamera
	};

public:
	CCameraManager();	//コンストラクタ
	~CCameraManager();	//デストラクタ

public:
	//インスタンス生成
	static void CreateInstance() { if (!instance_)instance_ = new CCameraManager; }
	//インスタンス取得
	static CCameraManager* GetInstance() { return instance_; }
	//インスタンス削除
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();	//初期化
	void Step();	//ステップ
	void Update();	//反映
	void Draw();	//描画
	void Fin();		//後処理

	//ニアクリップ・ファークリップの設定
	void SetNearFar(float near_val, float far_val);

	//引数のカメラに変更する
	void ChangeCamera(CAMERA_ID cmaeraID);

	//現在のカメラIDを取得
	CAMERA_ID GetCameraID() { return m_eCurrentCameraID; }

	//プレイカメラクラスを取得
	CPlayCamera* GetPlayCamera() { return &m_PlayCamera; }

	//デバッグカメラクラスを取得
	CDebugCamera* GetDebugCamera() { return &m_DebugCamera; }

private:
	//インスタンス
	static CCameraManager* instance_;

	//現在のカメラID
	CAMERA_ID m_eCurrentCameraID;

	//各カメラの変数
	CPlayCamera m_PlayCamera;	//プレイカメラクラス
	CDebugCamera m_DebugCamera;	//デバッグカメラクラス
};