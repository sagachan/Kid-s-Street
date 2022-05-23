//PlayCamera.cpp
//プレイシーンでのカメラ

#include "PlayCamera.h"
#include <math.h>
#include "../Library/MyMath/MyMath.h"
#include "../Library/Input/Input.h"
#include "../Library/Input/Pad/Pad.h"

//カメラ関連
#define CAMERA_OFFSET_Z			(-12.0f)		//カメラの注視点からの手前オフセット値
#define CAMERA_LOOK_OFFSET_Y	(4.0f)		//カメラの注視点の高さオフセット
#define CAMERA_ROT_SPEED		(0.052f)	//カメラの回転速度

namespace
{
	//カメラの回転スピード
	const float PLAY_CAMERA_ROTATION = (2.0f * DX_PI_F / 180.0f);
	//カメラの回転値最大
	const float PLAY_CAMERA_ROTATION_MAX = (2.0f * DX_PI_F);
	//カメラのX回転値最大
	const float PLAY_CAMERA_ROTATION_MAX_X = (20.0f * 2.0f * DX_PI_F / 180.0f);
	//カメラのX回転値最小
	const float PLAY_CAMERA_ROTATION_MIN_X = (-10.0f * 2.0f * DX_PI_F / 180.0f);

	//カメラのサイズ
	const float PLAY_CAMERA_SIZE_H = 1.0f;
	const float PLAY_CAMERA_SIZE_W = 1.0f;
	const float PLAY_CAMERA_SIZE_D = 1.0f;
	const float PLAY_CAMERA_SIZE_R = 1.0f;
}

//コンストラクタ
CPlayCamera::CPlayCamera()
	:cameraInfo_({0})
	,oldPos_({ 0.0f })
	, forward_({ 0.0f })
{
	
}

//デストラクタ
CPlayCamera::~CPlayCamera()
{
}

//初期化（引数あり）
void CPlayCamera::Init(VECTOR pos, VECTOR look, VECTOR up)
{
	//引数ありなら設定する
	cameraInfo_.pos_ = pos;
	cameraInfo_.look_ = look;
	cameraInfo_.up_ = up;
}


//毎フレーム呼ぶ処理（操作）
void CPlayCamera::Step()
{
	//前回位置座標を保管
	oldPos_ = cameraInfo_.pos_;
	oldRot_.x = cameraInfo_.fRotX_;
	oldRot_.y = cameraInfo_.fRotY_;
	
	//プレイヤーの情報を取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//入力操作クラス取得
	CInput* input = CInput::GetInstance();

	VECTOR player_rot = player->GetRot();	//回転値を取得
	VECTOR player_pos = player->GetPosition();	//座標を取得

	
	//----------------------------
	// カメラの注視点
	//----------------------------
	cameraInfo_.look_ = player->GetPosition();
	cameraInfo_.look_.y = player->GetPosition().y + CAMERA_LOOK_OFFSET_Y;	//プレイヤーの少し上を見る
	

	//スティックの値を取得
	float stick_x = input->GetStickValue(RIGHT_STICK_X);
	float stick_y = input->GetStickValue(RIGHT_STICK_Y);

	// X軸回転
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_UP)) {
		cameraInfo_.fRotX_ += CAMERA_ROT_SPEED;
		if (cameraInfo_.fRotX_ > 2.0f * DX_PI_F)cameraInfo_.fRotX_ -= 2.0f * DX_PI_F;
	}
	else if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_DOWN)) {
		cameraInfo_.fRotX_ -= CAMERA_ROT_SPEED;
		if (cameraInfo_.fRotX_ < 0)cameraInfo_.fRotX_ += 2.0f * DX_PI_F;
	}

	// Y軸回転
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_LEFT)) {
		cameraInfo_.fRotY_ -= CAMERA_ROT_SPEED;
		VECTOR rot = player->GetRot();
		rot.y -= CAMERA_ROT_SPEED;
		player->SetRot(rot);

		if (cameraInfo_.fRotY_ < 0)
		{
			cameraInfo_.fRotY_ += 2.0f * DX_PI_F;
		}

	}
	else if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_RIGHT)) {

		cameraInfo_.fRotY_ += CAMERA_ROT_SPEED;
		VECTOR rot = player->GetRot();
		rot.y += CAMERA_ROT_SPEED;
		player->SetRot(rot);

		if (cameraInfo_.fRotY_ > 2.0f * DX_PI_F)
		{
			cameraInfo_.fRotY_ -= 2.0f * DX_PI_F;
			
		}
	}

	// 注視点を原点に平行移動する行列を作成
	MATRIX origin_look_mat =
		CMyMath::GetTranslateMatrix(VGet(-cameraInfo_.look_.x, -cameraInfo_.look_.y, -cameraInfo_.look_.z));

	//カメラを注視点より手前に移動させる平行移動行列を作成
	MATRIX fore_look_mat =
		CMyMath::GetTranslateMatrix(VGet(0.0f, 0.0f, CAMERA_OFFSET_Z));

	//カメラのX軸回転行列を作成
	MATRIX pitch_mat = CMyMath::GetPitchMatrix(cameraInfo_.fRotX_);

	//カメラのY軸回転行列を作成
	MATRIX yaw_mat = CMyMath::GetYawMatrix(cameraInfo_.fRotY_);

	// 注視点を元の位置に平行移動する行列を作成
	MATRIX default_look_mat = CMyMath::GetTranslateMatrix(cameraInfo_.look_);

	//各行列を合成（掛け算の順番に注意！！）
	MATRIX mult_mat = CMyMath::MatMult(default_look_mat, yaw_mat);
	mult_mat = CMyMath::MatMult(mult_mat, pitch_mat);
	mult_mat = CMyMath::MatMult(mult_mat, fore_look_mat);
	mult_mat = CMyMath::MatMult(mult_mat, origin_look_mat);

	//注視点に行列を掛けてカメラの座標を算出
	cameraInfo_.pos_ = CMyMath::MatTransform(mult_mat, cameraInfo_.look_);

	//前の座標から今の座標への向きベクトルを求める
	VECTOR rot = CMyMath::GetRot(oldPos_, cameraInfo_.pos_);
	//向きベクトルを求める
	forward_.x = sinf(rot.y);
	forward_.z = cosf(rot.y);
	
}


//カメラ情報の更新処理
void CPlayCamera::Update()
{
	//カメラの視点（座標）・注視点・アップベクトル設定
	SetCameraPositionAndTargetAndUpVec(cameraInfo_.pos_, cameraInfo_.look_, cameraInfo_.up_);
}


//後処理
void CPlayCamera::Fin()
{
}

void CPlayCamera::HitSet()
{
	cameraInfo_.pos_ = oldPos_;
	cameraInfo_.fRotX_ = oldRot_.x;
	cameraInfo_.fRotY_ = oldRot_.y;

	//プレイヤーの情報を取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	player->SetRot(player->GetOldRotation());
}