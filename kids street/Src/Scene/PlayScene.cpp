//PlayScene.cpp
//プレイシーン

#include "PlayScene.h"
#include "SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Player/PlayerManager.h"
#include "../Field/FieldManager.h"
#include "../Library/Input/Input.h"
#include "../Fade/Fade.h"
#include "../Library/Sound/Sound.h"
#include "../Enemy/EnemyManager.h"
#include "../Library/MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Item/UseItem/ItemManager.h"
#include "../Item/GatherItem/GatherFactory/GatherManager.h"
#include "../Common.h"
#include "../Library/SagaLibrary.h"

CPlayScene::CPlayScene()
{
	map_handle = 0;
	map_pos = { 0 };
	
}

CPlayScene::~CPlayScene()
{
}




//初期化
void CPlayScene::Init()
{
	//ライブラリ生成
	CSagaLibrary::CreateInstance();

	//プレイヤー管理初期化
	//マネージャーインスタンス生成
	CPlayerManager::CreateInstance();
	//生成したインスタンスを取得
	CPlayerManager* player_manager = CPlayerManager::GetInstance();
	//マネージャー初期化
	player_manager->Init();

	//アイテム管理初期化
	//マネージャーインスタンス生成
	CItemManager::CreateInstance();
	//生成したインスタンスを取得
	CItemManager* item_manager = CItemManager::GetInstance();
	//マネージャー初期化
	item_manager->Init();

	//エネミー管理初期化
	//マネージャーインスタンス生成
	CEnemyManager::CreateInstance();
	//生成したインスタンスを取得
	CEnemyManager* enemy_manager = CEnemyManager::GetInstance();
	//マネージャー初期化
	enemy_manager->Init();
	

	////アニメーション初期化
	//CAnim3D::Init;


	//フィールド管理初期化
	CFieldManager::CreateInstance();
	CFieldManager* field_manager = CFieldManager::GetInstance();
	field_manager->Init();


	//カメラ管理初期化
	CCameraManager::CreateInstance();
	CCameraManager* camera_manager = CCameraManager::GetInstance();
	camera_manager->Init();
	camera_manager->SetNearFar(2.0f, 1500.0f);	//ニアファー設定

	//プレイカメラに変更
	camera_manager->ChangeCamera(CCameraManager::CAMERA_ID_PLAY);

	////フェードアウトの開始処理
	//CFade::StartFade(CFade::FADE_OUT, CFade::FADE_COLOR_WHITE);

	//音初期化
	CSound::InitSound();

	//当たり判定モデル読み込み
	map_handle = MV1LoadModel("Data/Model/Field/done/Field.x");

	//当たり判定用モデルのポリゴン情報をセットアップ
	MV1SetupReferenceMesh(map_handle, -1, TRUE);
	map_pos = { 0.0f, -2.0f, 0.0f };

	//マップの回転
	MV1SetPosition(map_handle, map_pos);

	//当たり判定用モデルのポリゴン情報をセットアップ
	MV1RefreshReferenceMesh(map_handle, -1, TRUE);

	//当たり判定管理初期化
	CCollisionManager::CreateInstance();

	//UI管理生成
	CGameUIManager::CreateInstance();

	////フォグを有効にする
	//SetFogEnable(TRUE);
	//SetFogColor(255, 255, 255);
	//SetFogStartEnd(400.0f, 600.0f);
}


//読み込み
void CPlayScene::Load()
{
	//プレイヤー管理読み込み
	CPlayerManager::GetInstance()->Load();

	//アイテム管理読み込み
	CItemManager::GetInstance()->Load();

	//エネミー管理読み込み
	CEnemyManager::GetInstance()->Load();

	////弾管理読み込み
	//CBulletManager::GetInstance()->Load();

	//フィールド管理読み込み
	CFieldManager::GetInstance()->Load();

	//音読み込み
	CSound::LoadBGM(CSound::BGM_PLAY);
	CSound::LoadBGM(CSound::BGM_MAIN);
}


//各変数などの初期値を設定
void CPlayScene::Set()
{
	//プレイヤー管理セット
	CPlayerManager::GetInstance()->Set();
	
	//アイテム管理セット
	CItemManager::GetInstance()->Set();

	//エネミー管理セット
	CEnemyManager::GetInstance()->Set();

	//フィールド管理セット
	CFieldManager::GetInstance()->Set();

	//音再生
	CSound::PlayBGM(CSound::BGM_PLAY);
	CSound::PlayBGM(CSound::BGM_MAIN);
}


//毎フレーム呼ぶ処理
void CPlayScene::Step()
{
	CCameraManager* camera_manager = CCameraManager::GetInstance();

	//====================
	//オブジェクト関連
	//====================

	//ステップ
	//プレイカメラ中なら（デバッグカメラ中は、プレイヤーは動かせない）
	if (camera_manager->GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
	{
		//プレイヤー管理ステップ
		CPlayerManager::GetInstance()->Step();
	}

	//アイテム管理ステップ
	CItemManager::GetInstance()->Step();
	CGatherManager::GetInstance()->Step();

	//エネミー管理ステップ
	CEnemyManager::GetInstance()->Step();


	//フィールド管理ステップ
	CFieldManager::GetInstance()->Step();

	//当たり判定管理ステップ
	CCollisionManager::GetInstance()->Step();

	
	//更新
	//プレイヤー管理の更新
	CPlayerManager::GetInstance()->Update();

	CItemManager::GetInstance()->Update();

	//エネミー管理の更新
	CEnemyManager::GetInstance()->Update();

	////弾管理の更新
	//CBulletManager::GetInstance()->Update();

	//フィールド管理の更新
	CFieldManager::GetInstance()->Update();


	//====================
	//カメラ関連
	//====================

	//カメラ視点・注視点の操作
	camera_manager->Step();

	//カメラ視点・注視点の反映
	camera_manager->Update();

	//各カメラの起動処理
	if (CInput::GetInstance()->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT_C))
	{
		//現在のカメラIDによって、処理を振り分ける
		switch (camera_manager->GetCameraID())
		{
		case CCameraManager::CAMERA_ID_PLAY:
			camera_manager->ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
			//デバッグカメラに、プレイカメラの座標を代入
			VECTOR play_camera_pos = camera_manager->GetPlayCamera()->GetPos();
			VECTOR play_camera_look = camera_manager->GetPlayCamera()->GetLook();
			camera_manager->GetDebugCamera()->Init(play_camera_pos, play_camera_look, VGet(0.0f, 1.0f, 0.0f));
			break;
		case CCameraManager::CAMERA_ID_DEBUG:
			camera_manager->ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
			break;
		}
	}

	
	//-------------------------------
	//		シーン切り替え
	//-------------------------------

	//プレイヤーが死んだらゲームオーバーシーンへ
	if (CInput::GetInstance()->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT_BACK))
	{
		//ゲームオーバーシーンへ変更
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
	}

	////プレイヤーがEnemyを全部倒したら
	//if (CPlayerManager::GetInstance()->GetPlayer()->GetKill_Count() == ENEMY_MAX_NUM)
	//{
	//		//ゲームクリアシーン変更
	//		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_CLEAR);
	//	
	//	
	//}


	//UI管理ステップ
	CGameUIManager::GetInstance()->Step();
}


//描画
void CPlayScene::Draw()
{
	//フィールド管理描画
	CFieldManager::GetInstance()->Draw();

	

	//アイテム管理描画
	CItemManager::GetInstance()->Draw();
	CGatherManager::GetInstance()->Draw();

	//プレイヤー管理描画
	CPlayerManager::GetInstance()->Draw();

	//エネミー管理描画
	CEnemyManager::GetInstance()->Draw();

	//カメラ管理描画
	CCameraManager::GetInstance()->Draw();

	//UI管理描画
	CGameUIManager::GetInstance()->Draw();
}


//後処理
void CPlayScene::Fin()
{
	//プレイヤー管理の後処理
	//プレイヤー管理取得
	CPlayerManager* player_manager = CPlayerManager::GetInstance();
	player_manager->Delete();	//明示的に削除を呼ぶ
	player_manager->Fin();		//後処理
	//マネージャーインスタンス削除
	CPlayerManager::DeleteInstance();

	//アイテム管理の後処理
	//アイテム管理取得
	CItemManager* item_manager = CItemManager::GetInstance();
	item_manager->Delete();		//明示的に削除を呼ぶ
	item_manager->Fin();		//後処理
	//マネージャーインスタンス削除
	CItemManager::DeleteInstance();

	//エネミー管理の後処理
	//エネミー管理取得
	CEnemyManager* enemy_manager = CEnemyManager::GetInstance();
	enemy_manager->Delete();	//明示的に削除を呼ぶ
	enemy_manager->Fin();		//後処理
	//マネージャーインスタンス削除
	CEnemyManager::DeleteInstance();

	//
	////弾管理の後処理
	//CBulletManager* bullet_manager = CBulletManager::GetInstance();
	//bullet_manager->Delete();
	//bullet_manager->Fin();
	//CBulletManager::DeleteInstance();


	//フィールド管理の後処理
	CFieldManager* field_manager = CFieldManager::GetInstance();
	field_manager->Delete();
	field_manager->Fin();
	CFieldManager::DeleteInstance();


	//カメラの後処理
	CCameraManager* camera_manager = CCameraManager::GetInstance();
	camera_manager->Fin();
	//マネージャーインスタンス削除
	CCameraManager::DeleteInstance();

	//音後処理
	CSound::FinSound();
}