#pragma once
#include "DxLib.h"



class CSound {
public:

	//BGMの種類
	enum BGM_KIND
	{
		BGM_NONE = -1,

		BGM_TITLE = 0,  //タイトルシーンのBGM
		BGM_PLAY,   //プレイシーンのBGM(環境音)
		BGM_CLEAR,   //クリアシーンのBGM
		BGM_GAMEOVER,  //ゲームオーバーシーンのBGM
		BGM_ESCAPE,  //エネミーに追われた時のBGM
		BGM_MAIN, //プレイシーンのメインBGM
		BGM_BOSS, //ボスバトル時のBGM
		MOVE,    //移動音
		BGM_NUM,   //BGMの個数
	};

	enum SE_KIND
	{
		SE_NONE = -1,


		SE_FOOT,    //足音
		SE_GET,		//アイテム獲得
		SE_NICE,	//何かしらの成功音
		SE_IMPACT,	//衝撃音　
		SE_DMG,		//ダメージ音
		SE_SWING,	//スイング音
		SE_NUM,
	};

	//サウンド初期化
	static void InitSound();

	//サウンド読み込み
	static void LoadBGM(BGM_KIND kind);
	static void LoadSE(SE_KIND kind);

	//サウンド再生
	static void PlayBGM(BGM_KIND kind);
	static void PlaySE(SE_KIND kind);

	//サウンド終了
	static void StopBGM(BGM_KIND kind);

	//サウンド後処理
	static void FinSound();

	static void FinBGMSound();

	static void FinSESound();

private:

	//BGM情報
	struct BGMInfo
	{
		BGM_KIND kind;
		int handle;
	};

	//効果音情報
	struct SEInfo
	{
		SE_KIND kind;
		int handle;
	};

	static BGMInfo bgm[BGM_NUM];
	static SEInfo se[SE_NUM];

};