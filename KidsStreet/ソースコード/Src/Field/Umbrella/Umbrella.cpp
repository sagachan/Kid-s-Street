//Pole.cpp
//フィールドクラス


#include "Umbrella.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Camera/PlayCamera.h"
#include "../../Camera/CameraManager.h"
#include "../../Library/Sound/Sound.h"
#include "../../UI/GameUIManager.h"

//フィールド関連
namespace
{
	const char*		MOVIE_PATH = "Data/Movie/CutIn.mp4";
	const float		CAMERA_NEAR = 2.0f;			//カメラのnear設定
	const float		CAMERA_FAR = 1500.0f;		//カメラのfar設定
	const int		MOVIE_SIZE_RATE = 2;			//ムービーのサイズレート
}

void CUmbrella::CutinMovie() 
{
	CSound::StopBGM(CSound::BGM_BOSS);
	CSound::StopBGM(CSound::BGM_MAIN);
	CSound::StopBGM(CSound::BGM_PLAY);
	PlayMovie(MOVIE_PATH, MOVIE_SIZE_RATE, DX_MOVIEPLAYTYPE_NORMAL);
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();
	enemyManager->SetSceneFlg(true);
	CPlayCamera* camera = CCameraManager::GetInstance()->GetPlayCamera();
	CCameraManager* cameraManager = CCameraManager::GetInstance();
	cameraManager->SetNearFar(CAMERA_NEAR, CAMERA_FAR);
	CSound::PlayBGM(CSound::BGM_MAIN);
	CSound::PlayBGM(CSound::BGM_PLAY);
	CGameUIManager* uiManager = CGameUIManager::GetInstance();
	uiManager->SetBossFlg(true);
}
