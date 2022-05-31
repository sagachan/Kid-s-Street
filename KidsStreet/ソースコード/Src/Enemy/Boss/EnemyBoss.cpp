
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Player/PlayerManager.h"
#include "../../Library/Animation/Animation.h"
#include "../../AI/BossAI/AIAttackBoss.h"
#include "../../Item/UseItem/ItemManager.h"
#include "../../Item/UseItem/ItemBase.h"
#include "EnemyBoss.h"
#include "../../Library/Sound/Sound.h"
#include "../../Field/FieldManager.h"
#include "../../Collision/CollisionCommon.h"
#include "../../Library/LibraryCommon.h"

namespace
{
	const VECTOR	BOSS_SET			= VGet(-12.0f, -5.0f, 150.0f);
	const VECTOR	BOSS_ROT_POS		= VGet(0.0f, 1.6f, 0.0f);		//回転値
	const VECTOR	FRAME_HIT_RADIUS	= VGet(5.0, 3.0, 5.0);			//ボーンの当たり判定の範囲
	const int		FRAME_HAND			= 12;							//手のボーンの番号
	const int		THROW_TIME			= 90;							//投げアニメーションが始まって手からアイテムが離れるフレーム数
	const int		JUMP_FRM_TIME		= 30;							//ボスのジャンプ時間
	const int		JUMP_CALC_Z			= 60;							
	const int		JUMP_CALC_X			= 60;
	const int		PUNCH_ATTRACT		= 20;
	const float		RADIUS				= 2.0f;							//当たり判定用、正方形一辺ごとの長さ
	const int		BOSS_STAND_END		= 60;							//ボスのスタンドモーションが終わるフレーム
	const int		BOSS_TARGET_FRM		= 60;							//ボスがターゲットを始めるフレーム
	const float		BOSS_PUNCH_AREA		= 20.0f;						//ボスのパンチ可能エリア
	const int		BOSS_PUNCH_FIRST	= 120;
	const int		BOSS_PUNCH_SECOND	= 140;
	const int		BOSS_PUNCH_THIRD	= 160;
	const int		BOSS_GET_POLE		= 20;							//ボスが電柱を持つタイミング
	const int		BOSS_SLASH_START	= 50;							//ボスが薙ぎ払い始める
	const int		SLASH_SOUND_FRM		= 65;							//薙ぎ払い音を流すタイミング
	const int		ATTRACT_FRM_START	= 15;
	const int		ATTRACT_FRM_END		= 90;
	//アクションごとにかかる準備時間
	const int		TARGET_TIME = 3000;
	//攻撃にかかる時間
	const int		ATTACK_TIME = 3000;
}

//コンストラクタ
CBoss::CBoss()
{
	Init();
}

//デストラクタ
CBoss::~CBoss()
{
	Fin();
}


//初期化
void CBoss::Init()
{
	doonce_ = false;
	time_ = 0;
	counterFlg_ = false;
	// AI状態遷移アルゴリズムを設定
	enemy_ai_ = new AIAttackBoss;
	static_cast<AIAttackBoss*>(enemy_ai_)->SetTargetTime(TARGET_TIME, ATTACK_TIME);
}

void CBoss::Set()
{
	//当たり判定範囲設定
	rad_ = RADIUS;
	hp_ = BOSS_MAX_HP;

	
	VECTOR framePos[FRAME_MAX];

	//当たり判定処理のセット
	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		//フレームの数だけ格納
		framePos[frameNum] = MV1GetFramePosition(hndl_,frameNum);
	}
	
	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		//当たり判定を生成
		CCollisionManager* collision = CCollisionManager::GetInstance();
		colFrmData_[frameNum].pos_ = MV1GetFramePosition(hndl_, frameNum);
		colFrmData_[frameNum].cubeRad_ = FRAME_HIT_RADIUS;
		colFrmData_[frameNum].useFlg_ = true;
		colFrmData_[frameNum].myList_ = COL_CHECK_BOSS;
		colFrmData_[frameNum].type_.pawn_ = CHECK_BOX_HIT;
		colFrmData_[frameNum].type_.static_ = CHECK_BOX_NONE;
		colFrmData_[frameNum].type_.dynamic_ = CHECK_BOX_NONE;
		colFrmData_[frameNum].object_ = OBJECT_PAWN;
		colFrmData_[frameNum].shapeCol_ = SHAPE_CUBE;

		colFrmData_[frameNum].colNum_ = collision->CreateCol(&colFrmData_[frameNum]);
	}
}



//読み込み（ロード）
void CBoss::Load()
{
	//モデル読み込み
	hndl_= MV1LoadModel("Data/Enemy/Boss/BOSS.x");

	//enemyBoss_anime
	rot_ = BOSS_ROT_POS;

	MV1SetRotationXYZ(hndl_, rot_);

	//アニメーション処理
	CAnim3D::RequestEndLoop(APPEAR, 0.5f, (int)-1, (bool)-1);

	//SEの読み込み
	CSound::LoadSE(CSound::SE_IMPACT);
	CSound::LoadSE(CSound::SE_NICE);
	CSound::LoadSE(CSound::SE_SWING);
}

//毎フレーム呼ぶ処理（操作）
void CBoss::Step()
{
	//当たり判定処理
	Hit();

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	CItemManager* item_manager = CItemManager::GetInstance();


	//向きベクトルを常に更新
	forward_.x = sinf(rot_.y);
	forward_.z = cosf(rot_.y);

	//現在アニメが終了したか
	end_animFlg_ = IsEndAnim();

	//前回ステータスを保存
	int old_ai = ai_state_;
	// 次のAI状態を設定
	ai_state_ = enemy_ai_->GetNextState(this);

	if (ai_state_ != old_ai)
	{
		changeFlg_ = true;
		frm_int_ = 0;
		counterFlg_ = true;
	}

	// AI更新
	StepAI();

	//フラグがONならボスが常にプレイヤーの方を向く
	Target(findFlg_);

	//この処理が始まってから何フレーム目なのかを格納するために通るごとに加算
	frm_int_++;
}


//更新
void CBoss::Update()
{
	//アニメーション更新
	CAnim3D::UpdateAnim();

	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++) {
		//当たり判定関係更新
		CCollisionManager::GetInstance()->
			SetUpdateColInfo(colFrmData_[frameNum].colNum_, MV1GetFramePosition(hndl_, frameNum), colFrmData_[frameNum].useFlg_);
	}
}

//描画
void CBoss::Draw()
{
	//モデルの回転
	MV1SetRotationXYZ(hndl_, rot_);
	//モデルの位置座標セット
	MV1SetPosition(hndl_, pos_);
	//モデル描画
	MV1DrawModel(hndl_);
}


//削除
void CBoss::Delete()
{
	MV1DeleteModel(hndl_);
}



//後処理
void CBoss::Fin()
{
	//Deleteが呼ばれていないなら
	if (hndl_!= 0){
		//削除を呼んでおく
		Delete();
	}

	enemy_ai_ = nullptr;
}





void CBoss::StepAI()
{
	// 現在の状態から各AI処理へ(関数ポインタを使うとなお良い)
	switch (ai_state_) {
	case AIBase::BOSS_APPEAR:	// 待機状態更新
		StepAppear();
		break;

	case AIBase::BOSS_STAND:// 警戒状態更新
		StepStand();
		break;

	case AIBase::BOSS_TARGET:	// 標的状態更新
		StepTarget();
		break;

	case AIBase::BOSS_NORMAL_ATTACK:	// 通常攻撃状態更新
		StepNormAttack();
		break;

	case AIBase::BOSS_CATCH:			//キャッチ状態更新
		StepCatch();
		break;

	case AIBase::BOSS_THROW:			//投擲状態更新
		StepThrow();
		break;

	case AIBase::BOSS_RAGE:				//暴れ状態更新
		StepRage();
		break;

	case AIBase::BOSS_SLASH:				//薙ぎ払い状態更新
		StepSlash();
		break;



	case AIBase::BOSS_MOTION_ATTACK:	// 構え状態更新
		StepMotion();
		break;

	case AIBase::BOSS_RARE_ATTACK:	// 特殊攻撃状態更新
		StepRareAttack();
		break;
	}
}

// 登場状態更新
void CBoss::StepAppear()
{
	
	counterFlg_ = true;
}

// 待機状態更新
void CBoss::StepStand()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestLoop(STAND, 0.5f, (int)-1, (bool)-1);
		changeFlg_ = false;
		counterFlg_ = false;
		doonce_ = false;
	}
	
	if (frm_int_ > BOSS_STAND_END)
	{
		counterFlg_ = true;
	}
}

// 標的状態更新
void CBoss::StepTarget()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(TARGET, 1.0f, (int)-1, (bool)-1);
		counterFlg_ = true;
		changeFlg_ = false;
	}

	if (frm_int_ > BOSS_TARGET_FRM)
	{
		findFlg_ = true;
	}
}

// 通常攻撃状態更新
void CBoss::StepNormAttack()		
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(ATTACK, 1.5f, (int)-1, (bool)-1);
		counterFlg_ = false;
		changeFlg_ = false;
	}

	//クラス取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	//一度だけ通る処理
	if (frm_int_ == JUMP_FRM_TIME && !doonce_)
	{
		//ジャンプ開始時のプレイヤーの位置座標を取得
		VECTOR pos = player->GetPosition();
		VECTOR vec = CMyMath::VecCreate(pos_, pos);
		//プレイヤーの現在地までのフレームごとの移動量を計算
		add_pos_ = VGet(vec.x / JUMP_CALC_X, vec.y, vec.z / JUMP_CALC_Z);
		//ジャンプ時の座標格納
		jump_pos_ = pos_;
		jump_dis_ = CMyMath::GetDistance(pos_, player->GetPosition());
		doonce_ = true;
	}
		
		//フレーム数管理、プレイヤーのほうに向かう処理
	if (frm_int_ > JUMP_FRM_TIME)
	{
		pos_.x += add_pos_.x;
		pos_.z += add_pos_.z;

		if (jump_dis_ > CMyMath::GetDistance(jump_pos_, player->GetPosition()))
		{
			frm_int_ = JUMP_FRM_TIME;
		}
	}
	
}

void CBoss::StepCatch()
{
	//形式上通る、アニメーション再生が必要ない
	findFlg_ = true;
	CItemManager* itemManager = CItemManager::GetInstance();

	//キャッチしてる間はボスの中心にアイテムが来る
	itemManager->SetBossItemPos(pos_);
	frm_int_ = 0;
}

void CBoss::StepThrow()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(THROW, 1.0f, (int)-1, (bool)-1);
		changeFlg_ = false;
		counterFlg_ = false;
	}
	

	CItemManager* itemManager = CItemManager::GetInstance();

	if (frm_int_ == THROW_TIME)
	{
		//アイテムクラスのボス用投げフラグをオンにする
		itemManager->SetBossItemThrow();
		//クラス取得
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		player->AddDamage(DMG_NORMAL);

		CSound::PlaySE(CSound::SE_DMG);
	}
	else if (frm_int_ < THROW_TIME)
	{
		//ボスの手にアイテムが来る
		itemManager->SetBossItemPos(GetBossHand());
		
	}

}

void CBoss::StepRage()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(RAGE, 0.5f, (int)-1, (bool)-1);
		counterFlg_ = false;
		changeFlg_ = false;
	}
	
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	if (frm_int_ == BOSS_PUNCH_FIRST || 
		frm_int_ == BOSS_PUNCH_SECOND || 
		frm_int_ == BOSS_PUNCH_THIRD)
	{
		CSound::PlaySE(CSound::SE_IMPACT);

		//プレイヤーがジャンプしてないなら
		if (!player->GetIsInAir())
		{
			player->AddDamage(DMG_STRONG);
			CSound::PlaySE(CSound::SE_DMG);
		}
		else
			CSound::PlaySE(CSound::SE_NICE);
	}
}

void CBoss::StepMotion()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(STAND_ATTACK_MOTION, 1.0f, (int)-1, (bool)-1);
		changeFlg_ = false;
		counterFlg_ = false;
	}
}

void CBoss::StepRareAttack()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(RARE_ATTACK, 1.0f, (int)-1, (bool)-1);
		changeFlg_ = false;
		counterFlg_ = false;
	}

	if (frm_int_ > ATTRACT_FRM_START &&
		frm_int_ < ATTRACT_FRM_END)
	{
		//クラス取得
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//プレイヤーの位置座標を取得
		VECTOR pos = player->GetPosition();
		VECTOR vec = CMyMath::VecCreate(pos, pos_);
		//プレイヤーの現在地までのフレームごとの移動量を計算
		add_pos_ = VGet(vec.x / (float)PUNCH_ATTRACT, vec.y, vec.z / (float)PUNCH_ATTRACT);
		add_pos_.x += pos.x;
		add_pos_.z += pos.z;
		add_pos_.y = pos.y;
		player->SetPosition(add_pos_);
	}

	if (frm_int_ == BOSS_PUNCH_FIRST)
	{
		//クラス取得
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//プレイヤーの位置座標を取得
		VECTOR pos = player->GetPosition();
		float dis = CMyMath::GetDistance(pos_, pos);

		//ボスの攻撃可能範囲にプレイヤーがいるなら
		if (dis < BOSS_PUNCH_AREA){
			player->AddDamage(DMG_NORMAL);
			CSound::PlaySE(CSound::SE_DMG);
		}
		else
			CSound::PlaySE(CSound::SE_NICE);
	}
}

void CBoss::StepSlash()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(SLASH, 1.5f, (int)-1, (bool)-1);
		changeFlg_ = false;
		counterFlg_ = false;
	}

	if (frm_int_ == BOSS_GET_POLE)
	{
		CPole* pole = CFieldManager::GetInstance()->GetPole();
		pole->SetRot(VGet(1.6f, rot_.y - 0.8f, 0.0f));
		pole->SetPosition(MV1GetFramePosition(hndl_, FRAME_HAND));
		findFlg_ = false;
	}
	
	if (frm_int_ > BOSS_GET_POLE)
	{
		CPole* pole = CFieldManager::GetInstance()->GetPole();
		pole->SetPosition(MV1GetFramePosition(hndl_, FRAME_HAND));
	}
	
	if (frm_int_ > BOSS_SLASH_START)
	{
		CPole* pole = CFieldManager::GetInstance()->GetPole();
		VECTOR poleRot = pole->GetRot();
		poleRot.y += 0.03f;
		pole->SetRot(poleRot);
	}

	if (frm_int_ == SLASH_SOUND_FRM)
	{
		CSound::PlaySE(CSound::SE_SWING);
	}

	if (!doonce_)
	{
		//クラス取得
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//プレイヤーのモデルハンドルを取得
		int playerHndl = player->GetHandle();

		CPole* pole = CFieldManager::GetInstance()->GetPole();
		VECTOR startHndlPos = MV1GetFramePosition(pole->GetHandle(), POLE_BONE_START);
		VECTOR endHndlPos = MV1GetFramePosition(pole->GetHandle(), POLE_BONE_END);
		MV1_COLL_RESULT_POLY result = MV1CollCheck_Line(playerHndl, -1, startHndlPos, endHndlPos);

		if (result.HitFlag)
		{
			player->AddDamage(DMG_STRONG);
			CSound::PlaySE(CSound::SE_DMG);
			doonce_ = true;
		}
	}
}

//----------ここまでがステータス関係----------
void CBoss::Target(bool flg)
{
	if (flg == true)
	{
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//敵がプレイヤーを向く処理
		VECTOR vec = CMyMath::VecCreate(pos_, player->GetPosition());
		vec.y = 0.0f;
		rot_.y = atan2f(vec.x, vec.z);
	}
}

void CBoss::Hit()
{
	CCollisionManager* collision = CCollisionManager::GetInstance();

	//当たり判定結果取得
	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		colFrmData_[frameNum] = collision->GetCollisionData(colFrmData_[frameNum].colNum_);
	}

	//複数の当たり判定に同じオブジェクトが触れていた場合に処理を複数回繰り返してしまわないようにする
	//処理を行ったリストのタイプの元enum番号のフラグを立てる
	bool checkFlg[COL_CHECK_MAX] = { false };

	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		//当たり判定を行うかどうか
		if (colFrmData_[frameNum].hitFlg_)
		{
			//リストの中身を全て確認して判定処理を行うものを見つける
			for (int checkNum = 0; checkNum < COL_CHECK_MAX; checkNum++)
			{
				//当たっていたのがプレイヤーの時
				if (colFrmData_[frameNum].list_[checkNum] == COL_CHECK_PLAYER && !checkFlg[COL_CHECK_PLAYER])
				{
					//当たった時に起きる処理
					CPlayerManager::GetInstance()->GetPlayer()->AddDamage(1);
					checkFlg[COL_CHECK_PLAYER] = true;
				}
			}
		}
	}
}

void CBoss::Damage(int dmg)
{ 
	//ダメージ処理
	hp_ -= dmg;
	
	//体力がなくなったら
	if (hp_ < 0 && !doonce_)
	{

		
		CFieldManager::GetInstance()->GetUmbrella()->CutinMovie();
		doonce_ = true;
	}
}

//当たり判定クラスによってボスの抵抗が可能だと判断されたときに使われる
void CBoss::SetBossAIFlg(bool flg)
{
	static_cast<AIAttackBoss*>(enemy_ai_)->SetCounterFlg(flg);
}

VECTOR CBoss::GetBossHand()
{
	return MV1GetFramePosition(hndl_, FRAME_HAND);
}