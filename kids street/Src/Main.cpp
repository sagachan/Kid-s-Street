#include <DxLib.h>
#include <math.h>
#include "Scene/SceneManager.h"
#include "Field/FieldManager.h"
#include "Library/Input/Input.h"
#include "Common.h"
#include "Enemy/EnemyManager.h"


//-------------------------------------
// グローバル変数
//-------------------------------------

//フレームレート関連
int g_nCurrentTime = 0;				//現在の時間
int g_nLastFrameTime = 0;			//前回のフレーム実行時の時間
int g_nFrameCnt = 0;				//フレームカウント用
int g_nUpdateFrameRateTime = 0;		//フレームレートを更新した時間
float g_fFrameRate = 0.f;			//フレームレート（表示用）

//-------------------------------------
// グローバル関数
//-------------------------------------

//フレームレート計算
void CalcFrameRate();

//フレームレート表示（デバッグ用）
void DrawFrameRate();


//プログラムは WinMain から始まる
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(true);	//ウィンドウの状態を設定する

	//--------------------------------------------
	//一番最初に１回だけやる処理をここに書く

	//DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//ウィンドウサイズを変更
	SetGraphMode(WINDOW_W, WINDOW_H, 32);

	//描画するスクリーンを設定
	SetDrawScreen(DX_SCREEN_BACK);
	
	//アプリケーション名
	SetMainWindowText("Kids Street");

	//透過色を設定
	SetTransColor(0, 127, 127);



	//====================
	// シーンの処理
	//====================

	//シーン管理初期化
	CSceneManager::CreateInstance();
	CSceneManager* scene_manager = CSceneManager::GetInstance();

	//最初はプレイシーンへ
	scene_manager->StartFirstScene(CSceneManager::SCENE_ID_TITLE);


	//--------------------------------------------
	//キーボード入力初期化
	CInput::GetInstance()->Init();

	//=============================================================================
	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		Sleep(1);	//システムに処理を返す

		//現在の時間を取得
		g_nCurrentTime = GetNowCount();


		//現在の時間が、前回のフレーム時より
		// 1000/60ミリ秒（1/60秒)以上経過していたら処理を実行する
		if (g_nCurrentTime - g_nLastFrameTime >= 1000 / FRAME_RATE)
		{
			//フレーム実行時の時間を更新
			g_nLastFrameTime = g_nCurrentTime;

			//フレーム数をカウント
			g_nFrameCnt++;


			if (CInput::GetInstance()->IsPush(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_ESCAPE) == 1)
			{
				//エスケープキーが押されたら終了
				break;
			}

			//画面に表示されたものを初期化（１ループの１度だけ行う）
			ClearDrawScreen();

			//キーボード入力通常処理
			CInput::GetInstance()->Step();

			////フェードのステップ
			//CFade::StepFade();


			//====================
			// シーンの処理
			//====================

			//シーン管理のループ
			scene_manager->Loop();


			////フェードの描画
			//CFade::DrawFade();


			//フレームレート計算
			CalcFrameRate();

			//フレームレート表示（デバッグ用）
			DrawFrameRate();

			//フリップ関数（ループの終わりに１度だけ行う）
			ScreenFlip();
		}//フレームレートのif文終わり
	}//メインループの終わり

	//--------------------------------------------
	//最後に１回だけやる処理をここに書く

	//シーン管理の後処理
	scene_manager->Fin();
	CSceneManager::DeleteInstance();


	//使用したすべての画像を破棄
	InitGraph();

	//DXライブラリの後処理
	DxLib_End();

	return 0;
}//WinMain関数の終わり


//フレームレート計算
void CalcFrameRate()
{
	//前回のフレームレート更新からの経過時間を求める
	int nDifTime = g_nCurrentTime - g_nUpdateFrameRateTime;

	//前回のフレームレート更新から
	//１秒以上経過していたらフレームレートを更新する
	if (nDifTime > 1000)
	{
		//フレーム回数をミリ秒に合わせる
		//小数まで出したいのでfloatにキャスト
		float fFrameCnt = (float)(g_nFrameCnt * 1000);

		//フレームレートを求める
		//理想通りなら 60000 / 1000 で 60 となる
		g_fFrameRate = fFrameCnt / nDifTime;

		//フレームカウントをクリア
		g_nFrameCnt = 0;

		//フレームレート更新時間を更新
		g_nUpdateFrameRateTime = g_nCurrentTime;
	}
}


//フレームレート表示（デバッグ用）
void DrawFrameRate()
{
	
}