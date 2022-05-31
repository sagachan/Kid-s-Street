//CameraManager.cpp
//カメラ管理
//C***Cameraへのアクセスは必ずCCameraManagerを経由

#include "CameraManager.h"

//CCameraManagerの実体宣言、初期化
CCameraManager* CCameraManager::instance_ = nullptr;

//コンストラクタ
CCameraManager::CCameraManager()
	:m_eCurrentCameraID(CAMERA_ID_PLAY)
{
	//CPlayCameraのコンストラクタは自動で呼ばれます
	//CDebugCameraのコンストラクタは自動で呼ばれます
}

//デストラクタ
CCameraManager::~CCameraManager()
{
	//CPlayCameraのデストラクタは自動で呼ばれます
	//CDebugCameraのデストラクタは自動で呼ばれます
}


//初期化
void CCameraManager::Init()
{
	//各カメラの初期化
	m_PlayCamera.Init(VGet(0.0f, 4.0f, -28.0f), CPlayerManager::GetInstance()->GetPlayer()->GetPosition(), VGet(0.0f, 1.0f, 0.0f));
	m_DebugCamera.Init(VGet(0.0f, 8.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));
}


//ステップ
void CCameraManager::Step()
{
	//現在のカメラIDによって処理を振り分ける
	switch (m_eCurrentCameraID)
	{
	case CAMERA_ID_PLAY:
		m_PlayCamera.Step();
		break;
	case CAMERA_ID_DEBUG:
		m_DebugCamera.Step();
		break;
	}
}


//反映
void CCameraManager::Update()
{
	//現在のカメラIDによって処理を振り分ける
	switch (m_eCurrentCameraID)
	{
	case CAMERA_ID_PLAY:
		m_PlayCamera.Update();
		break;
	case CAMERA_ID_DEBUG:
		m_DebugCamera.Update();
		break;
	}
}


//描画
void CCameraManager::Draw()
{
	//現在のカメラIDによって処理を振り分ける
	switch (m_eCurrentCameraID)
	{
	case CAMERA_ID_DEBUG:
		m_DebugCamera.Draw();
		break;
	}
}


//後処理
void CCameraManager::Fin()
{
	//各カメラのあと処理
	m_PlayCamera.Fin();
	m_DebugCamera.Fin();
}


//ニアクリップ・ファークリップの設定
void CCameraManager::SetNearFar(float near_val, float far_val)
{
	SetCameraNearFar(near_val, far_val);
}


//引数のカメラに変更する
void CCameraManager::ChangeCamera(CAMERA_ID cameraID)
{
	m_eCurrentCameraID = cameraID;
}