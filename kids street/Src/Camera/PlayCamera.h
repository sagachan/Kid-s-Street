//PlayCamera.h
//プレイシーンでのカメラ

#pragma once

#include "DxLib.h"
#include "../Player/PlayerManager.h"

class CPlayCamera
{
	
public:
	CPlayCamera();	//コンストラクタ
	~CPlayCamera();	//デストラクタ

public:
	//初期化
	void Init(){}
	void Init(VECTOR pos, VECTOR look, VECTOR up);

	//毎フレーム呼ぶ処理（操作）
	void Step();

	//カメラ情報の更新処理
	void Update();

	//後処理
	void Fin();

public:
	void HitSet();

	
public:
	//ゲッター
	VECTOR GetPos() { return cameraInfo_.pos_; }//座標取得
	VECTOR GetLook() { return cameraInfo_.look_; }//注視点取得

private:

	//カメラ情報
	struct CameraInfo
	{
		VECTOR	pos_;		//視点
		VECTOR	look_;		//注視点
		VECTOR	up_;			//アップベクトル
		float fRotX_;		//水平角度(X軸角度)
		float fRotY_;		//垂直角度(Y軸角度)
	};
	VECTOR oldPos_;
	VECTOR oldRot_;
	VECTOR forward_;
	CameraInfo cameraInfo_;
};