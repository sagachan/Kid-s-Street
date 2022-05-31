//PlayScene.h
//プレイシーン

#pragma once

#include "DxLib.h"
#include "SceneBase.h"

#define WAIT_MAX_TIME 30


//プレイシーンクラス
class CPlayScene :public CSceneBase
{
public:
	CPlayScene();
	~CPlayScene();

	//初期化
	void Init() override;

	//読み込み
	void Load() override;

	//各変数などに値をセット
	void Set() override;

	//毎フレーム呼ぶ処理
	void Step() override;

	

	//描画
	void Draw() override;

	//後処理
	void Fin() override;


	
	VECTOR map_pos; //当たり判定用マップ座標
	int map_handle; //当たり判定モデル読み込み



};
