
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/Input/Input.h"
#include "../../Player/PlayerManager.h"
#include "../../Library/Animation/Animation.h"
#include "../../AI/BossAI/AIAttackBoss.h"
#include "../../Item/UseItem/ItemManager.h"
#include "../../Item/UseItem/ItemBase.h"
#include "EnemyBoss.h"

namespace
{
	const VECTOR BOSS_SET = VGet(-12.0f, -5.0f, 150.0f);
	const VECTOR BOSS_ROT_POS = VGet(0.0f, 1.6f, 0.0f);			//回転値
	const int ORIGIN = 0;											//初期化値
	const float BACK_MOVE = -1.0f;										//戻る
	const VECTOR FRAME_HIT_RADIUS = VGet(5.0, 5.0, 5.0);			//ボーンの当たり判定の範囲
	const int FRAME_OUT = 0;										//例外ボーン指定
	const int FRAME_HAND = 13;										//手のボーンの番号
	const int THROW_TIME = 90;								//投げアニメーションが始まって手からアイテムが離れるフレーム数
	const int JUMP_FRM_TIME = 30;
	const int JUMP_CALC_Z = 90;								
	const int JUMP_CALC_X = 60;
	const VECTOR COL_CUBE1 = VGet(1.0, 1.0, 1.0);
	const VECTOR COL_CUBE2 = VGet(1.0, 1.0, 1.0);
	const float RADIUS = 2.0f;										//当たり判定用、正方形一辺ごとの長さ
	const int	MAXHP = 100;										//体力の最大値

	//アクションごとにかかる準備時間
	const int TARGET_TIME = 3000;
	//攻撃にかかる時間
	const int ATTACK_TIME = 3000;
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
	pos_ = { 0 };
	is_roop_ = false;
	old_distance_ = 0;
	distance_ = 0;
	end_animFlg_ = 0;
	findFlg_ = false;
	time_ = 0;
	radius_ = 0.0f;
	forward_ = { 0 };
	counterFlg_ = false;
	// AI状態遷移アルゴリズムを設定
	enemy_ai_ = new AIAttackBoss;
	static_cast<AIAttackBoss*>(enemy_ai_)->SetTargetTime(TARGET_TIME, ATTACK_TIME);

}

void CBoss::Set()
{
	//当たり判定範囲設定
	radius_ = RADIUS;
	hp_ = MAXHP;

	
	VECTOR framePos[FRAME_MAX];

	//当たり判定処理のセット
	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		//フレームの数だけ格納
		framePos[frameNum] = MV1GetFramePosition(hndl_,frameNum);
	}
	
	CCollisionManager::GetInstance()->SetBossCollision(framePos, RADIUS);
}



//読み込み（ロード）
void CBoss::Load()
{
	//モデル読み込み
	hndl_= MV1LoadModel("Data/Enemy/Boss/enemyBoss_anime.x");

	rot_ = BOSS_ROT_POS;

	MV1SetRotationXYZ(hndl_, rot_);

	

	//アニメーション処理
	CAnim3D::RequestEndLoop(APPEAR, 0.5f, (int)-1, (bool)-1);
}

//毎フレーム呼ぶ処理（操作）
void CBoss::Step()
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	CItemManager* item_manager = CItemManager::GetInstance();

	/*if (doTwice_ == false)
	{
		item_manager->SetAppear(true);
		doTwice_ = true;
	}*/

	//向きベクトルを常に更新
	forward_.x = sinf(rot_.y);
	forward_.z = cosf(rot_.y);

	//現在アニメが終了したか
	end_animFlg_ = IsEndAnim();

	// 次のAI状態を設定
	ai_state_ = enemy_ai_->GetNextState(this);

	// AI更新
	StepAI();

	//フラグがONならボスが常にプレイヤーの方を向く
	Target(findFlg_);

	//ダメージ処理
	Damage(dmg_);
}


//更新
void CBoss::Update()
{
	//アニメーション更新
	CAnim3D::UpdateAnim();
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
	if (hndl_!= 0)
	{
		//削除を呼んでおく
		Delete();
	}

	enemy_ai_ = nullptr;
}




//---------------------ここから下が各自作関数------------------------------
// 
// 
// 
//最初に読み込んだ時の時間を格納
void CBoss::GetCount()
{
	//次にフラグがfalseにされるまでは通らない
	if (get_timeflg_ == false)
	{
		//読み込み開始時間を変数に格納
		time_ = (float)GetNowCount();
		get_timeflg_ = true;
	}
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

	//case AIBase::BOSS_MOTION_ATTACK:	// 構え状態更新
	//	StepMotion();
	//	break;

	//case AIBase::BOSS_RARE_ATTACK:	// 特殊攻撃状態更新
	//	StepRareAttack();
	//	break;
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
	if (end_animFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(STAND, 0.5f, (int)-1, (bool)-1);
		//状態ごとの変数初期化
		norm_attack_flg_ = false;
		doOnce_ = false;
		frame_num_ = 0;
		counterFlg_ = true;
	}
}

// 標的状態更新
void CBoss::StepTarget()
{
	if (end_animFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(TARGET, 0.5f, (int)-1, (bool)-1);
		counterFlg_ = true;
		findFlg_ = true;
		get_timeflg_ = false;
		counterFlg_ = true;
	}
}

// 通常攻撃状態更新
void CBoss::StepNormAttack()		
{
	//クラス取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	counterFlg_ = false;

	if (end_animFlg_)
	{
		
		//アニメーション処理
		CAnim3D::RequestEndLoop(ATTACK, 1.5f, (int)-1, (bool)-1);
		counterFlg_ = false;
		get_timeflg_ = false;
		norm_attack_flg_ = true;
	}

	//アニメーション再生が開始されているなら
	if (norm_attack_flg_)
	{ 
		

		//一度だけ通る処理
		if (frame_num_ == JUMP_FRM_TIME && !doOnce_)
		{
			//ジャンプ開始時のプレイヤーの位置座標を取得
			VECTOR pos = player->GetPosition();
			VECTOR vec = CMyMath::VecCreate(pos_, pos);
			//プレイヤーの現在地までのフレームごとの移動量を計算
			add_pos_ = VGet(vec.x / JUMP_CALC_X, vec.y, vec.z / JUMP_CALC_Z);
			doOnce_ = true;
			//ジャンプ時の座標格納
			jump_pos_ = pos_;
			jump_dis_ = CMyMath::GetDistance(pos_, player->GetPosition());
		}
		
		//フレーム数管理、プレイヤーのほうに向かう処理
		if (frame_num_ > JUMP_FRM_TIME)
		{
			pos_.x += add_pos_.x;
			pos_.z += add_pos_.z;

			if (jump_dis_ > CMyMath::GetDistance(jump_pos_, player->GetPosition()))
			{
				frame_num_ = JUMP_FRM_TIME;
			}
		}
		//現在のフレーム数
		frame_num_++;
	}
}

void CBoss::StepCatch()
{
	//形式上通る、アニメーション再生が必要ない
	findFlg_ = true;
	CItemManager* itemManager = CItemManager::GetInstance();

	//キャッチしてる間はボスの中心にアイテムが来る
	itemManager->SetBossItemPos(pos_);
}

void CBoss::StepThrow()
{
	if (!doOnce_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(THROW, 1.0f, (int)-1, (bool)-1);
		doOnce_ = true;
	}
	//この処理が始まってから何フレーム目なのかを格納するために通るごとに加算
	frame_num_++;

	CItemManager* itemManager = CItemManager::GetInstance();

	if (frame_num_ == THROW_TIME)
	{
		//アイテムクラスのボス用投げフラグをオンにする
		itemManager->SetBossItemThrow();
	}
	else if (frame_num_ < THROW_TIME)
	{
		//ボスの手にアイテムが来る
		itemManager->SetBossItemPos(MV1GetFramePosition(hndl_, FRAME_HAND));
	}

}

void CBoss::StepRage()
{
	if (end_animFlg_ == true)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(RAGE, 0.5f, (int)-1, (bool)-1);

	}
	frame_num_++;

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//プレイヤーがジャンプしてないなら
	if (!player->GetIsInAir())
	{
		doOnce_ = false;
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
	//当たり判定処理管理クラスに渡す引数の中身を更新
	for (int frameNum = 0; frameNum < FRAME_MAX; frameNum++)
	{
		//フレームの数だけ格納
		framePos[frameNum] = MV1GetFramePosition(hndl_, frameNum);
	}

	CCollisionManager::GetInstance()->SetBossCollision(framePos, RADIUS);
}

void CBoss::Damage(int dmg)
{ 
	//当たり判定フラグがオンになっていないなら何もしない
	if (colFlg_ == false)
	{
		return;
	}
	colFlg_ = false;

	//ダメージ処理
	hp_ -= dmg;
	
	//体力がなくなったら
	if (hp_ < 0)
	{
		//ゲームクリアシーンへ変更
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_CLEAR);
	}
}

void CBoss::DrawHitCube(VECTOR pos)
{
	cube_pos1_ = pos, cube_pos2_ = pos;

	cube_pos1_.x = cube_pos1_.x + COL_CUBE1.x;
	cube_pos1_.y = cube_pos1_.y + COL_CUBE1.y;
	cube_pos1_.z = cube_pos1_.z + COL_CUBE1.z;

	cube_pos2_.x = cube_pos2_.x - COL_CUBE2.x;
	cube_pos2_.y = cube_pos2_.y - COL_CUBE2.y;
	cube_pos2_.z = cube_pos2_.z - COL_CUBE2.z;
}

//当たり判定クラスによってボスの抵抗が可能だと判断されたときに使われる
void CBoss::SetBossAIFlg(bool flg)
{
	static_cast<AIAttackBoss*>(enemy_ai_)->SetCounterFlg(flg);
}

