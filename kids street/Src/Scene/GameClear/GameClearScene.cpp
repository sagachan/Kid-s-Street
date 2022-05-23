//GameClearScene.cpp
//ゲームクリアシーン

#include "GameClearScene.h"
#include "../SceneManager.h"
#include "../../Library/Input/Input.h"
#include "DxLib.h"
#include <math.h>
#include "../../Common.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Fade/Fade.h"
#include "../../UI/GameUIManager.h"
#include "../../Library/Sound/Sound.h"


namespace
{
	const float TEXT_MAX_SIZE = 1.0f;	//文字の最大サイズ
	const float TEXT_ADD_SIZE = 0.01f;	//文字の加算されるサイズ量
	const float TEXT_MOVE_Y = 30.0f;	//文字のY座標移動量

	//波形の角度の変わるの速さ（５秒で一周）
	const float WAVE_ANGLE_SPD = (DX_TWO_PI_F / FRAME_RATE) / 5.0f;
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
	//テキスト画像関連初期化
	text_info_.handle = 0;
	text_info_.posX = 0.0f;
	text_info_.posY = 0.0f;
	text_info_.base_posY = 0.0f;
	text_info_.size = 0.0f;
	text_info_.wave_angle = 0.0f;


	//UI管理生成
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//背景生成
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Graph/GameClear_BG.png");

	//音初期化
	CSound::InitSound();
}

//読み込み
void CGameClearScene::Load()
{
	//ゲームクリアシーンの画像読み込み
	text_info_.handle = LoadGraph("Data/Graph/GameClear_Logo.png");

	//音読み込み
	CSound::LoadBGM(CSound::BGM_CLEAR);
}

//各変数などに初期値を設定（セット）
void CGameClearScene::Set()
{
	text_info_.posX = WINDOW_W / 3 * 2;
	text_info_.posY = WINDOW_H;
	text_info_.base_posY = WINDOW_H;

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


	////文字のサイズを規定値まで拡大
	//if (text_info_.size < TEXT_MAX_SIZE)
	//{
	//	text_info_.size += TEXT_ADD_SIZE;
	//}

	////文字のサイズが規定値に達したら
	////sinカーブを利用して、文字を上下に動かす
	//if (text_info_.size >= TEXT_MAX_SIZE)
	//{
	//	//適切な移動量にして、座標に代入
	//	text_info_.posY = text_info_.base_posY + sinf(text_info_.wave_angle) * TEXT_MOVE_Y;

	//	//角度を加算（5秒ごとに基点に戻る）
	//	text_info_.wave_angle += WAVE_ANGLE_SPD;

	//	//角度が０～２πの値の範囲外になった場合、
	//	//０～２πの範囲に戻す
	//	if (text_info_.wave_angle < 0.0f)
	//		text_info_.wave_angle = CMyMath::RadianNormalize(text_info_.wave_angle);
	//	else if (text_info_.wave_angle > DX_TWO_PI_F)
	//		text_info_.wave_angle = CMyMath::RadianNormalize(text_info_.wave_angle);
	//}
}


//描画
void CGameClearScene::Draw()
{
	//UI管理描画
	CGameUIManager::GetInstance()->Draw();

	//文字画像
	DrawRotaGraph((int)text_info_.posX, (int)text_info_.posY,
		text_info_.size, 0.0f, text_info_.handle, true);

	//文字列描画
	DrawString(10, 10, "タイトル画面", GetColor(255, 255, 255));
	DrawString(10, 30, "Enter押したらPlayへ", GetColor(255, 255, 0));
}


//後処理
void CGameClearScene::Fin()
{
	//UI管理後処理
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();

	DeleteGraph(text_info_.handle);
	text_info_.handle = 0;

	//音後処理
	CSound::FinSound();
}