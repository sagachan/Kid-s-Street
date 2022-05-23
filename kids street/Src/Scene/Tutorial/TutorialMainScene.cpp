//TutorialScene.cpp
//タイトルシーン

#include "TutorialMainScene.h"
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
	const float TEXT_MAX_SIZE = 1.0f;	//文字の最大サイズ
	const float TEXT_ADD_SIZE = 0.01f;	//文字の加算されるサイズ量
	const float TEXT_MOVE_Y = 30.0f;	//文字のY座標移動量
	
	//波形の角度の変わるの速さ（５秒で一周）
	const float WAVE_ANGLE_SPD = (DX_TWO_PI_F / FRAME_RATE) / 5.0f;
}

CTutorialMainScene::CTutorialMainScene()
{
	Init();
}

CTutorialMainScene::~CTutorialMainScene()
{
}

//初期化
void CTutorialMainScene::Init()
{
	//UI管理生成
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//背景生成
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/TutorialMain.png");
}


//読み込み
void CTutorialMainScene::Load()
{


}


//各変数などに初期値を設定（セット）
void CTutorialMainScene::Set()
{
	
}


//毎フレーム呼ぶ処理
void CTutorialMainScene::Step()
{
	CInput* input = CInput::GetInstance();

	if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//プレイシーンへ変更
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_TUTORIAL_ITEM);
	}

	//UI管理ステップ
	CGameUIManager::GetInstance()->Step();
}


//描画
void CTutorialMainScene::Draw()
{
	//UI管理描画
	CGameUIManager::GetInstance()->Draw();
}


//後処理
void CTutorialMainScene::Fin()
{
	//UI管理後処理
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();
}