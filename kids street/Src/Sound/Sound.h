#pragma once
#include "DxLib.h"



class CSound {
public:

	//BGMの種類
	enum BGM_KIND
	{
		BGM_NONE = -1,

		BGM_TITLE = 0,  //タイトルシーンのBGM
		BGM_PLAY,   //プレイシーンのBGM
		BGM_CLEAR,   //クリアシーンのBGM
		BGM_GAMEOVER,  //ゲームオーバーシーンのBGM
		MOVE,    //移動音
		BGM_NUM,   //BGMの個数
	};

	//enum SE_KIND
	//{
	//	SE_NONE = -1,


	//	SHOT,    //発射音
	//	DEFEAT,    //撃破音
	//	DECISION,   //決定
	//	SE_NUM,
	//};

	//サウンド初期化
	static void InitSound();

	//サウンド読み込み
	static void LoadBGM(BGM_KIND kind);
	/*static void LoadSE(SE_KIND kind);*/

	//サウンド再生
	static void PlayBGM(BGM_KIND kind);
	/*static void PlaySE(SE_KIND kind);*/

	//サウンド後処理
	static void FinSound();

private:

	//BGM情報
	struct BGMInfo
	{
		BGM_KIND kind;
		int handle;
	};

	////効果音情報
	//struct SEInfo
	//{
	//	SE_KIND kind;
	//	int handle;
	//};

	static BGMInfo bgm[BGM_NUM];
	/*static SEInfo se[SE_NUM];*/

};