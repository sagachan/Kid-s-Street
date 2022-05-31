//DebugCamera.h
//デバッグ用のカメラ

#pragma once

#include "DxLib.h"

//デバッグカメラクラス
class CDebugCamera
{
public:
	CDebugCamera();		//コンストラクタ
	~CDebugCamera();	//デストラクタ

public:
	void Init();									//初期化（引数なし）
	void Init(VECTOR pos, VECTOR look, VECTOR up);	//初期化（引数あり）
	void Step();									//ステップ
	void Update();									//反映
	void Draw();									//描画（注視点に球体を描画）
	void Fin();										//後処理

private:
	VECTOR m_vPos;		//視点
	VECTOR m_vLook;		//注視点
	VECTOR m_vUp;		//アップベクトル
	VECTOR m_angle;		//角度（アングル）
};