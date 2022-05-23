//DebugCamera.cpp
//デバッグ用のカメラ

#include "DebugCamera.h"
#include "CameraManager.h"
#include "../Library/MyMath/MyMath.h"
#include "../Library/Input/Input.h"


namespace
{
	const float CAMERA_MOVE_SPD = 3.0f;		//視点の速度
	const float CAMERA_LOOK_SPD = 0.2f;		//注視点の速度
	const float CAMERA_LOOK_Y_DIST = 20.0f;	//注視点の上下に動かせる距離
}

//コンストラクタ
CDebugCamera::CDebugCamera()
{
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}

//デストラクタ
CDebugCamera::~CDebugCamera()
{	
}


//初期化（引数なし）
void CDebugCamera::Init()
{
	//引数なしならすべてゼロにする
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vLook, 0, sizeof(VECTOR));
	memset(&m_vUp, 0, sizeof(VECTOR));
}


//初期化（引数あり）
void CDebugCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//引数ありなら設定する
	m_vPos = pos;
	m_vLook = look;
	m_vUp = up;
}


//ステップ
void CDebugCamera::Step()
{
	//----------------------------
	// カメラの注視点
	//----------------------------
	CInput* input = CInput::GetInstance();

	//注視点を上へ
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_UP))
		m_vLook.y += CAMERA_LOOK_SPD;
	//注視点を下へ
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_DOWN))
		m_vLook.y -= CAMERA_LOOK_SPD;
	//注視点を左へ
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_LEFT))
	{
		//視点から注視点までのベクトルを求める
		VECTOR start_vec = CMyMath::VecCreate(m_vPos, m_vLook);
		//左移動用のベクトルを求める
		VECTOR left_move = CMyMath::VecCross(start_vec, VGet(0.0f, 1.0f, 0.0f));
		//左移動用のベクトルを正規化
		left_move = CMyMath::VecNormalize(left_move);
		//ちゃんとした移動量にする（適切な数値にする）
		left_move = CMyMath::VecScale(left_move, CAMERA_LOOK_SPD);

		//注視点に加算
		m_vLook = CMyMath::VecAdd(m_vLook, left_move);
	}
	//注視点を右へ
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_RIGHT))
	{
		//視点から注視点までのベクトルを求める
		VECTOR start_vec = CMyMath::VecCreate(m_vPos, m_vLook);
		//左移動用のベクトルを求める
		VECTOR left_move = CMyMath::VecCross(start_vec, VGet(0.0f, 1.0f, 0.0f));
		//左移動用のベクトルを正規化
		left_move = CMyMath::VecNormalize(left_move);
		//ちゃんとした移動量にする（適切な数値にする）
		left_move = CMyMath::VecScale(left_move, CAMERA_LOOK_SPD);

		//左移動用なので、右移動用に変換
		VECTOR right_move = { 0 };
		right_move.x = -left_move.x;
		right_move.y = -left_move.y;
		right_move.z = -left_move.z;

		//注視点に加算
		m_vLook = CMyMath::VecAdd(m_vLook, right_move);
	}


	//注視点制限（視点から±20まで）
	if (m_vLook.y - m_vPos.y > CAMERA_LOOK_Y_DIST)
		m_vLook.y = CAMERA_LOOK_Y_DIST + m_vPos.y;
	else if (m_vLook.y - m_vPos.y < -CAMERA_LOOK_Y_DIST)
		m_vLook.y = -CAMERA_LOOK_Y_DIST + m_vPos.y;


	//----------------------------
	// カメラの視点（座標）
	//----------------------------

	//前へ移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_W))
	{
		//視点から注視点へのベクトルを求める（前移動用ベクトル）
		VECTOR front_move = CMyMath::VecCreate(m_vPos, m_vLook);
		//正規化する
		front_move = CMyMath::VecNormalize(front_move);
		//適切な大きさにする
		front_move = CMyMath::VecScale(front_move, CAMERA_MOVE_SPD);

		//視点・注視点にそれぞれ加算
		m_vPos = CMyMath::VecAdd(m_vPos, front_move);
		m_vLook = CMyMath::VecAdd(m_vLook, front_move);
	}
	//後ろへ移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_S))
	{
		//視点から注視点へのベクトルを求める（前移動用ベクトル）
		VECTOR front_move = CMyMath::VecCreate(m_vPos, m_vLook);
		//正規化する
		front_move = CMyMath::VecNormalize(front_move);
		//適切な大きさにする
		front_move = CMyMath::VecScale(front_move, CAMERA_MOVE_SPD);

		//前移動用なので、後ろ移動用に変換
		VECTOR back_move = { 0 };
		back_move.x = -front_move.x;
		back_move.y = -front_move.y;
		back_move.z = -front_move.z;

		//視点・注視点にそれぞれ加算
		m_vPos = CMyMath::VecAdd(m_vPos, back_move);
		m_vLook = CMyMath::VecAdd(m_vLook, back_move);
	}
	//左へ移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_A))
	{
		//視点から注視点までのベクトルを求める
		VECTOR start_vec = CMyMath::VecCreate(m_vPos, m_vLook);
		//左移動用のベクトルを求める
		VECTOR left_move = CMyMath::VecCross(start_vec, VGet(0.0f, 1.0f, 0.0f));
		//左移動用のベクトルを正規化
		left_move = CMyMath::VecNormalize(left_move);
		//ちゃんとした移動量にする（適切な数値にする）
		left_move = CMyMath::VecScale(left_move, CAMERA_MOVE_SPD);

		//視点・注視点にそれぞれ加算
		m_vPos = CMyMath::VecAdd(m_vPos, left_move);
		m_vLook = CMyMath::VecAdd(m_vLook, left_move);
	}
	//右へ移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_D))
	{
		//視点から注視点までのベクトルを求める
		VECTOR start_vec = CMyMath::VecCreate(m_vPos, m_vLook);
		//左移動用のベクトルを求める
		VECTOR left_move = CMyMath::VecCross(start_vec, VGet(0.0f, 1.0f, 0.0f));
		//左移動用のベクトルを正規化
		left_move = CMyMath::VecNormalize(left_move);
		//ちゃんとした移動量にする（適切な数値にする）
		left_move = CMyMath::VecScale(left_move, CAMERA_MOVE_SPD);

		//右移動用のベクトルにするため、左移動用のベクトルを反転
		VECTOR right_move = { 0 };
		right_move.x = -left_move.x;
		right_move.y = -left_move.y;
		right_move.z = -left_move.z;

		//視点・注視点にそれぞれ加算
		m_vPos = CMyMath::VecAdd(m_vPos, right_move);
		m_vLook = CMyMath::VecAdd(m_vLook, right_move);
	}
}


//反映
void CDebugCamera::Update()
{
	//カメラの視点（座標）・注視点・アップベクトル設定
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vLook, m_vUp);
}


//描画（注視点に球体を描画）
void CDebugCamera::Draw()
{
	//球体を描画
	DrawSphere3D(m_vLook, 0.5f, 5, GetColor(0, 255, 255), GetColor(0, 0, 0), false);

	//表示文字
	DrawFormatString(500, 50, GetColor(255, 255, 0), "デバッグカメラモード");
	DrawFormatString(500, 75, GetColor(255, 255, 255), 
		"Pos ：( %.1f, %.1f, %.1f )", m_vPos.x, m_vPos.y, m_vPos.z);
	DrawFormatString(500, 40, GetColor(255, 255, 255),
		"Look：( %.1f, %.1f, %.1f )", m_vLook.x, m_vLook.y, m_vLook.z);
}


//後処理
void CDebugCamera::Fin()
{
}