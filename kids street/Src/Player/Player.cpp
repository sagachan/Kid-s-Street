#include "Player.h"
#include "../Common.h"
#include <math.h>
#include "../Library/MyMath/MyMath.h"
#include "../Library/Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../Enemy/EnemyManager.h"
#include "../Item/UseItem/ItemManager.h"
#include "../Library/Animation/Animation.h"
#include "../Field/FieldManager.h"
#include "../Item/GatherItem/GatherFactory/GatherManager.h"
#include "../Item/ItemCommon.h"
#include "../UI/GameUIManager.h"

namespace
{
	//プレイヤー関連
	const VECTOR PLAYER_START_POS = VGet(5.0f, 1.0f, 250.0f);	//プレイヤーの座標
	const VECTOR PLAYER_CONTINUE_POS = VGet(-1000.0f, 1.0f, 1700.0f);	//プレイヤーの座標


	const float PLAYER_SPD = 0.2f;			//プレイヤーの移動速度
	const float PLAYER_ADDSPD = 0.8f;		//白線上プレイヤー速度
	const float PLAYER_JUMP_POWER = 0.5f;	//プレイヤーのジャンプ力
	const float PLAYER_G_POWER = 0.5;		//プレイヤーにかかる重力の強さ設定（中の数値は仮）
	const bool  HIT_INIT_FLG = false;		//プレイヤーに外部から変更可能な当たり判定フラグの初期値
	const int	PLAYER_HP = 100;			//プレイヤーの体力

	const float PLAYER_R = 2.0f;			//プレイヤーの半径

	//画面範囲関連
	const float RANGE_MAX_WIDTH = 14.0f;	//横幅の最大範囲
	const float RANGE_MIN_WIDTH = -14.0f;	//横幅の最小範囲
	const float RANGE_MAX_HEIGHT = 12.0f;	//縦幅の最大範囲
	const float RANGE_MIN_HEIGHT = -12.0f;	//縦幅の最大範囲

	//ジャンプ関連
	const float ORIGIN_POS = 0.0f;			//原点座標
	const float PLAYER_JUMP_TIME = 0.35f;	//プレイヤーの飛ぶ時間
	const float PLAYER_JUMP_VAL = 0.0f;		//ジャンプ量
	const float GRAVITY = 0.3f;				//重力
	const float JUMP_CHARGE = 10.0f;		//ジャンプ時の溜め硬直時間
	const float JUMP_LANDING = 40.0f;		//ジャンプ後の着地硬直時間

	//アニメーション関連
	const int THROW_FRM = 25;
	const int RELOAD_FRM = 10;
	const int ATTACK_FRM = 15;
	const float ATTACK_RAD = 10.0f;
	const int ATTACK_DMG = 5;
}




//コンストラクタ
CPlayer::CPlayer()
{
	Init();
}

//デストラクタ
CPlayer::~CPlayer()
{
	Fin();
}



//初期化
void CPlayer::Init()
{
	jump_time_ = 0.0f;				//ジャンプの時間
	hit_flg_ = HIT_INIT_FLG;		//当たり判定フラグ初期化
	hp_ = 0;
}



//読み込み（ロード）
void CPlayer::Load()
{
	//モデル読み込み
	hndl_ = MV1LoadModel("Data/Player/Player.x");
}



//各変数などに初期値を設定（セット）
void CPlayer::Set()
{
	pos_ = PLAYER_START_POS;
	rad_ = PLAYER_R;			//半径
	state_ = PLAYER_STAND;			//ステータス
	hp_ = PLAYER_HP;
	MV1SetupCollInfo(hndl_, -1, true);
	pos_ = RULER_POS;
}


//プレイヤーが当たり判定の影響を受ける処理
void CPlayer::HitSet()
{
	pos_.x = oldPos_.x;
	pos_.z = oldPos_.z;
}


//プレイヤーが当たり判定の影響を受けるかどうかをフラグで管理するオーバーロード
void CPlayer::HitSet(bool flg)
{
	hit_flg_ = flg;
}

void CPlayer::AddDamage(int dmg)
{
	hp_ -= dmg;
}




//毎フレーム呼ぶ処理（操作）
void CPlayer::Step()
{
	//プレイヤーの体力が0より少ないなら
	if (hp_ < 0){
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
	}

	// 現在アニメが終了したか
	end_animFlg_ = IsEndAnim();

	//プレイヤーに常に重力をかける
	pos_.y -= GRAVITY;
	//プレイヤーの移動前の座標を記録
	oldPos_ = pos_;
	
	move_ = { 0 };

	//外部に優先度が高い入力処理がある場合は通らない
	if(!CGameUIManager::GetInstance()->GetInputFlg())
		StepInput();
	
	//プレイヤーの座標ベクトル
	pos_ = CMyMath::VecAdd(pos_, move_);
	
	StatesSet();

	//外部から変更を行った当たり判定
	if (hit_flg_ == true)
	{
		HitSet();
		//使用後もとに戻す
		HitSet(HIT_INIT_FLG);
	}
}


//更新
void CPlayer::Update()
{
	//アニメーション更新
	CAnim3D::UpdateAnim();

	//プレイヤーの回転
	MV1SetRotationXYZ(hndl_, rot_);

	//プレイヤーの座標
	MV1SetPosition(hndl_, pos_);

	MV1RefreshCollInfo(hndl_, -1, true);

	oldRot_ = rot_;
}


//描画
void CPlayer::Draw()
{
	//プレイヤーの描画
	MV1DrawModel(hndl_);
	
	DrawFormatString(10, 10, GetColor(255, 255, 255),
		"pos.x = %f,pos.y = %f,pos.z = %f", pos_.x, pos_.y, pos_.z);
}


//削除
void CPlayer::Delete()
{
	//プレイヤーモデル削除
	MV1DeleteModel(hndl_);

	//削除したら0を代入しておく
	hndl_ = 0;
}


//後処理
void CPlayer::Fin()
{
	//Deleteが呼ばれていないなら
	if (hndl_ != 0)
	{
		//削除を呼んでおく
		Delete();
	}
}


//入力ステップ
void CPlayer::StepInput()
{

	CInput* input = CInput::GetInstance();
	CRoad* field = CFieldManager::GetInstance()->GetRoad();
	CItemManager* item_manager = CItemManager::GetInstance();
	//--------------------------------
	//    プレイヤーの移動処理
	//--------------------------------
	float add = PLAYER_SPD;			//プレイヤーの移動速度設定
	bool calcFlg = false;			//行列計算を行うかどうか
	bool inputFlg = false;			//同時に一つしか入力をさせない
	oldPos_ = pos_;				//処理前座標を保持

	//向きベクトルを求める
	forward_.x = sinf(rot_.y);
	forward_.z = cosf(rot_.y);

	

		
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_N))
	{
		pos_ = PLAYER_CONTINUE_POS;
	}

	//ダッシュ処理
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_LSHIFT))
	{
		add = PLAYER_ADDSPD;
	}

	//向いている方向へ移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_W) && !inputFlg)
	{
		//向きベクトルを適切な大きさ・向きに変更して座標に加算
		move_.x += forward_.x * add;
		move_.z += forward_.z * add;
		inputFlg = true;
	}
	//左移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_A) && !inputFlg)
	{
		move_.x -= PLAYER_SPD;
		calcFlg = true;
		inputFlg = true;
	}
	//右移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_D) && !inputFlg)
	{
		move_.x += PLAYER_SPD;
		calcFlg = true;
		inputFlg = true;
	}
	//向いている方向とは逆へ移動
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_S) && !inputFlg)
	{
		//向きベクトルを適切な大きさ・向きに変更して座標に加算
		move_.x -= forward_.x * add;
		move_.z -= forward_.z * add;
		inputFlg = true;
	}

	if (calcFlg)
	{
		//カメラの向いている方向に進む（水平方向の移動だけして欲しいので、Y軸回転値しか見ない）
		MATRIX translate_mat = CMyMath::GetTranslateMatrix(move_);
		MATRIX yaw_mat = CMyMath::GetYawMatrix(rot_.y);
		MATRIX result_mat = CMyMath::MatMult(yaw_mat, translate_mat);

		//行列から移動後の座標成分を取得
		move_ = VGet(result_mat.m[0][3], result_mat.m[1][3], result_mat.m[2][3]);
		move_ = CMyMath::VecNormalize(VGet(move_.x, 0.0f, move_.z));

		move_ = CMyMath::VecScale(move_, PLAYER_SPD);
	}
	
	//歩き又は待機の時だけ
	if (state_ == PLAYER_STAND || state_ == PLAYER_WALK || state_ == PLAYER_RUN)
	{
		//攻撃
			//Fキーが押されたかつアイテムを手に持っている時
		if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_F) &&
			item_manager->GetHold())
		{
			state_ = PLAYER_THROW;
		}

		//スペースキーが押されたかつプレイヤーが現在空中にいないなら
		if (CInput::GetInstance()->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT_SPACE) && field->Is_in_Air() == false)
		{
			//状態をジャンプ上昇中へ
			state_ = PLAYER_JUMP;
			jump_time_ = 0.0f;
		}

		
		//まずは自分が参照しているアイテムがまだ手に入っていない場合は装填はできないようにする
		CItemManager* itemManager = CItemManager::GetInstance();
		CGatherManager* gatherManager = CGatherManager::GetInstance();
		ITEM_KIND item = itemManager->GetItemKind();
		bool* gatherFlg = gatherManager->GetGatherItem();
		bool reloadFlg = false;
		bool attackFlg = false;

		switch (item){
		case ITEM_INIT:break;
		case ERASER:if(gatherFlg[ERASER]) { reloadFlg = true; } break;
		case PENCIL:if(gatherFlg[PENCIL]) { reloadFlg = true; } break;
		case RULER:if (gatherFlg[RULER]) { reloadFlg = true; } break;
		case GLOVE:if (gatherFlg[GLOVE]) { attackFlg = true; } break;
		default:
			break;
		}
		
		//装填
		if (reloadFlg)
		{
			//Rキーが押されたかつアイテムを手にもっていない時
			if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_R) &&
				!item_manager->GetHold())
			{
				state_ = PLAYER_RELOAD;
			}
		}

		//攻撃
		if (attackFlg)
		{
			//Fキーが押されたかつグローブを手に選んでいる時
			if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_F) &&
				!item_manager->GetHold())
			{
				state_ = PLAYER_ATTACK;
			}
		}
	}
}

//アニメーション状態遷移
void CPlayer::StatesSet()
{
	switch (state_)
	{
	case PLAYER_STAND:FromStand(); break;
	case PLAYER_WALK:FromWalk(); break;
	case PLAYER_RUN:FromRun(); break;
	case PLAYER_JUMP:FromJump(); break;
	case PLAYER_THROW:FromThrow(); break;
	case PLAYER_RELOAD:FromReload(); break;
	case PLAYER_ATTACK:FromAttack(); break;
	}
	
	//ステータスが前フレと違うならアニメーション再生フラグを初期化
	if (state_ != old_state_)
	{
		changeFlg_ = true;
		frm_int_ = 0;
	}

	//今フレ状態を格納
	old_state_ = state_;
}

void CPlayer::FromStand()
{
	if (changeFlg_ == true) {
		//アニメーション
		CAnim3D::RequestLoop(STAND, 1.0f, -1, false);
		//一度だけ読み込まれるようにするため
		changeFlg_ = false;
	}

	//前フレーム時から動いたなら
	if (pos_.x != oldPos_.x || pos_.z != oldPos_.z) {
		state_ = PLAYER_WALK;
		changeFlg_ = true;
	}
}

void CPlayer::FromWalk()
{
	//歩行状態時の状態遷移
	if (changeFlg_ == true) {
		//アニメーション
		CAnim3D::RequestLoop(WALK, 1.0f, -1, false);
		//一度だけ読み込まれるようにするため
		changeFlg_ = false;
	}

	CInput* input = CInput::GetInstance();
	if (input->IsRelease(input->INPUT_KIND_KEY, KEY_INPUT_LSHIFT))
	{
		state_ = PLAYER_RUN;
		changeFlg_ = true;
	}

	//立ち止まったなら待機に戻る
	if (pos_.x == oldPos_.x && pos_.z == oldPos_.z) {
		state_ = PLAYER_STAND;
		changeFlg_ = true;
	}
}

void CPlayer::FromRun()
{
	//走行状態時の状態遷移
	if (changeFlg_ == true) {
		//アニメーション
		CAnim3D::RequestLoop(RUN, 2.0f, -1, false);
		//一度だけ読み込まれるようにするため
		changeFlg_ = false;
	}
	CInput* input = CInput::GetInstance();
	if (input->IsKeep(input->INPUT_KIND_KEY, KEY_INPUT_LSHIFT))
	{
		state_ = PLAYER_WALK;
	}
}

void CPlayer::FromJump()
{
	if (changeFlg_ == true)
	{
		//アニメーション
		CAnim3D::RequestEndLoop(JUMP, 1.15f, -1, false);
		//一度だけ読み込まれるようにするため
		changeFlg_ = false;
	}

	//上昇
	pos_.y += PLAYER_JUMP_VAL;
	jump_time_ += 1.0f / FRAME_RATE;

	//ジャンプ時間が過ぎたら
	if (jump_time_ >= PLAYER_JUMP_TIME)
	{
		jump_time_ = 0.0f;
	}

	//ジャンプ時の初動溜め硬直とジャンプ後の着地硬直
	if (GetAnimFrm() < JUMP_CHARGE ||
		GetAnimFrm() > JUMP_LANDING)
	{
		pos_ = oldPos_;
	}
	//アニメーション終了したなら待機に戻る
	if (end_animFlg_ == true)
	{
		state_ = PLAYER_STAND;
		changeFlg_ = true;
	}
}
void CPlayer::FromReload()
{
	if (changeFlg_ == true){
		//アニメーション
		CAnim3D::RequestEndLoop(RELOAD, 1.0f, -1, false);
		//一度だけ読み込まれるようにするため
		changeFlg_ = false;
	}
	//この状態では動けない
	pos_ = oldPos_;
	frm_int_++;

	
	if (frm_int_ == RELOAD_FRM){
		CItemManager* item_manager = CItemManager::GetInstance();
		//アイテムが手につく
		item_manager->SetHold(true);
	}
	//アニメーション終了したなら待機に戻る
	if (end_animFlg_ == true){
		state_ = PLAYER_STAND;
	}
}

void CPlayer::FromThrow()
{
	if (changeFlg_ == true){
		//アニメーション
		CAnim3D::RequestEndLoop(THROW, 1.0f, -1, false);
		//一度だけ読み込まれるようにするため
		changeFlg_ = false;
	}
	//この状態では動けない
	pos_ = oldPos_;
	frm_int_++;
	
	if (frm_int_ == THROW_FRM){
		CItemManager* item_manager = CItemManager::GetInstance();
		//アイテムが手から離れる
		item_manager->SetHold(false);
		//アイテムを投げたことをアイテム管理に渡す
		item_manager->SetThrowflg(true);
	}

	//アニメーション終了したなら待機に戻る
	if (end_animFlg_ == true){
		state_ = PLAYER_STAND;
	}
}

void CPlayer::FromAttack()
{
	if (changeFlg_ == true) {
		//アニメーション
		CAnim3D::RequestEndLoop(ATTACK, 1.0f, -1, false);
		//一度だけ読み込まれるようにするため
		changeFlg_ = false;
	}
	//この状態では動けない
	pos_ = oldPos_;
	frm_int_++;

	if (frm_int_ == ATTACK_FRM)
	{
		//ボスが攻撃可能範囲内にいるか
		CBoss* boss = CEnemyManager::GetInstance()->GetBoss();
		VECTOR bossPos = boss->GetPosition();
		if (CMyMath::RadiusCheck(pos_.x, ATTACK_RAD, bossPos.x) &&
			CMyMath::RadiusCheck(pos_.z, ATTACK_RAD, bossPos.z))
		{
			boss->SetColFlg(true);
			boss->Damage(DMG_WEAK);
		}
	}
	//アニメーション終了したなら待機に戻る
	if (end_animFlg_ == true) {
		state_ = PLAYER_STAND;
	}
}