
#include <math.h>
#include "../../Library/MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Library/Animation/Animation.h"
#include "../../AI/ChaseAI/AIChaseBoss.h"
#include "ChaseBoss.h"
#include "../../Library/Error/Error.h"
#include "../../Field/FieldCommon.h"
#include "../../Collision/CollisionManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Library/Sound/Sound.h"
#include "../../Field/FieldManager.h"
#include "../EnemyManager.h"

namespace
{
	const VECTOR	CHASE_ROT_POS = VGet(0.0f, 1.6f, 0.0f);		//回転値
	const VECTOR	FRAME_HIT_RADIUS = VGet(5.0, 5.0, 5.0);		//ボーンの当たり判定の範囲
	const float		CHASE_SET = -50.0f;
	const int		FRAME_HAND = 13;							//手のボーンの番号
	const float		FIND_AREA = 500.0f;							//プレイヤーを見つけることができる警戒エリアの半径
	const float		BOSS_ATTACK_AREA = 10.0f;					//ボスの攻撃範囲
	const int		BOSS_LOOP_START = 0;
	const int		BOSS_LOOP_END = 16;
	const int		ROUTE_NUM = 4;								//通るルートに存在するボーンの数
	const int		BOSS_ROUTE[ROUTE_NUM] = { BOSS_LOOP_START,6,10,BOSS_LOOP_END };
	const int		BOSS_ARRIVAL = 7;							//ボスが遠距離でプレイヤーを追いかけるときにプレイヤーに追いつくまでの時間
	const int		BOSS_SERCH_TIME = 4;						//ボスがプレイヤーを見失ってから索敵にかける時間
	const float		BOSS_RETURN_SPD = 0.5f;						//ボスが追いかけるのをやめて元の順路に戻るときの移動速度
	const float		BOSS_SPD = 0.8f;							//ボスの移動速度
	const float		BOSS_RETURN_AREA = 3.0f;					//目標の交差点に到着したことを確認するときに使う
	const VECTOR	BOSS_APPEAR = VGet(0.0f, 0.0f, 0.0f);
	const VECTOR	BOSS_MAP_POS = VGet(-20.0f, -10.0f, 0.0f);
	const int		BOSS_PUNCH_FRM = 33;						//ボスのパンチのダメージ発生フレーム
	const int		BOSS_PUNCH_DMG = 30;						//ボスのパンチのダメージ
	const int		BOSS_FINISHER_FRM = 8;						//プレイヤーつか身が発生するフレーム
}



//コンストラクタ
CChaseBoss::CChaseBoss()
{
	Init();
}

//デストラクタ
CChaseBoss::~CChaseBoss()
{
	Fin();
}


//初期化
void CChaseBoss::Init()
{
	
	forward_ = { 0 };
	serchInfo_ = { 0 };
	routeFlg_ = false;
	// AI状態遷移アルゴリズムを設定
	enemy_ai_ = new AIChaseBoss;
	changeFlg_ = false;
	routeFlg_ = false;
	colMapHndl_ = 0;
	CSound::InitSound();
}

void CChaseBoss::Set()
{
	//攻撃範囲設定
	rad_ = BOSS_ATTACK_AREA;
	move_ = BOSS_SPD;

	//初期位置情報設定
	CInter* inter = CFieldManager::GetInstance()->GetInter();
	pos_ = MV1GetFramePosition(inter->GetFrmHndl(), 0);
	pos_.y = -1.0f;
	changeFlg_ = true;

	/////////移動処理に使うマップの当たり判定情報をセット
	MV1SetupCollInfo(hndl_, -1, true);

	//索敵処理に必要なマップのモデルを読み込み、位置情報を設定する
	colMapHndl_ = MV1LoadModel("Data/Map/Field/map.x");
	MV1SetPosition(colMapHndl_, BOSS_MAP_POS);

	//初期ステータス設定
	ai_state_ = AIBase::CHASE_APPEAR;
}

//読み込み（ロード）
void CChaseBoss::Load()
{
	//モデル読み込み
	hndl_ = MV1LoadModel("Data/Enemy/Boss/enemyBossInit.x");

	/*rot_ = CHASE_ROT_POS;*/

	MV1SetRotationXYZ(hndl_, rot_);

	
	//アニメーション処理
	CAnim3D::RequestEndLoop(APPEAR, 0.5f, (int)-1, (bool)-1);

	CSound::LoadBGM(CSound::BGM_ESCAPE);
	CSound::LoadSE(CSound::SE_DMG);
}

//毎フレーム呼ぶ処理（操作）
void CChaseBoss::Step()
{
	//前回の座標を格納
	oldPos_ = pos_;

	// 現在アニメが終了したか
	end_animFlg_ = IsEndAnim();

	// 次のAI状態を設定
	ai_state_ = enemy_ai_->GetNextState(this);

	// AI更新
	StepAI();
	// フラグがONならボスが常にプレイヤーの方を向く
	Target(findFlg_);
	
}


//更新
void CChaseBoss::Update()
{
	//アニメーション更新
	CAnim3D::UpdateAnim();

	//ボスの周辺の車を止める
	StopStreet();
	

	MV1RefreshCollInfo(hndl_, -1, true);
}

//描画
void CChaseBoss::Draw()
{
	//モデルの回転
	MV1SetRotationXYZ(hndl_, rot_);

	//モデルの位置座標セット
	MV1SetPosition(hndl_, pos_);

	//モデル描画
	MV1DrawModel(hndl_);
}


//削除
void CChaseBoss::Delete()
{

	DeleteModel();
}



//後処理
void CChaseBoss::Fin()
{
	//Deleteが呼ばれていないなら
	if (hndl_ != 0)
	{
		//削除を呼んでおく
		Delete();
	}

	enemy_ai_ = nullptr;
	CSound::FinSound();
}




//---------------------ここから下が各自作関数------------------------------
// 
// 
// 


void CChaseBoss::StepAI()
{
	// 現在の状態から各AI処理へ
	switch (ai_state_) {
	case AIBase::CHASE_APPEAR:		//登場状態更新
		StepAppear();
		break;

	case AIBase::CHASE_WALK:		//歩行状態更新
		StepWalk();
		break;

	case AIBase::CHASE_RUN:			//標的状態更新
		StepRun();
		break;

	case AIBase::CHASE_ROLL:		//通常攻撃状態更新
		StepRoll();
		break;

	case AIBase::CHASE_PUNCH:		//キャッチ状態更新
		StepPunch();
		break;

	case AIBase::CHASE_FINISHER:	//投擲状態更新
		StepFinisher();
		break;
	}
}

// 登場状態更新
void CChaseBoss::StepAppear()
{

}

// 歩行状態更新
void CChaseBoss::StepWalk()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestLoop(WALK, 1.0f, (int)-1, (bool)-1);
		findFlg_ = false;
		changeFlg_ = false;
		routeFlg_ = false;
	}

	//ルート通りに動く処理
	if (routeFlg_)
		LoopRoute();
	else
		//既定のルートに戻る処理
		ReturnRoute();

	
	
	//進んでいる方向を向く処理
	VECTOR vec = CMyMath::VecCreate(oldPos_, pos_);
	vec.y = 0.0f;
	rot_.y = atan2f(vec.x, vec.z);
}

// 走行状態更新
void CChaseBoss::StepRun()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestLoop(RUN, 1.0f, (int)-1, (bool)-1);
		frm_int_ = 0;
		changeFlg_ = false;
		CSound::StopBGM(CSound::BGM_ESCAPE);
		CSound::PlayBGM(CSound::BGM_ESCAPE);
		CSound::StopBGM(CSound::BGM_MAIN);
	}
	
	//二つのどちらでも通るたびに加算する必要のある変数なのでここで加算、
	//なおこの下の関数の読み込みが切り替わるときに初期化される
	frm_int_++;

	//視界内判定関数を呼び、視界内にプレイヤーがいなくなったら
	//フラグを折り、歩きに変更する
	if (!serchInfo_.flg_) {
		CheckChase();
	}
	else
	{
		SerchChase();

		//進んでいる方向を向く処理
		VECTOR vec = CMyMath::VecCreate(oldPos_, pos_);
		vec.y = 0.0f;
		rot_.y = atan2f(vec.x, vec.z);
	}
}

// 回転状態更新
void CChaseBoss::StepRoll()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(ROLL, 1.0f, (int)-1, (bool)-1);	
	}

	//１フレーム目で向いていた方向を保存しておき、その方向に
	//値を加算し続ける

}

//　攻撃状態更新
void CChaseBoss::StepPunch()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(PUNCH, 1.0f, (int)-1, (bool)-1);
		changeFlg_ = false;
		frm_int_ = 0;

		CSound::StopBGM(CSound::BGM_MAIN);
		CSound::StopBGM(CSound::BGM_PLAY);
		CSound::PlayBGM(CSound::BGM_MAIN);
		CSound::PlayBGM(CSound::BGM_PLAY);
		CSound::StopBGM(CSound::BGM_ESCAPE);
	}

	frm_int_++;

	//フレーム番号があらかじめ決めておいた値になったら、ダメージをプレイヤーに加える
	if (frm_int_ == BOSS_PUNCH_FRM)
	{
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

		player->AddDamage(BOSS_PUNCH_DMG);
		CSound::PlaySE(CSound::SE_DMG);
	}
}

void CChaseBoss::StepFinisher()
{
	if (changeFlg_)
	{
		//アニメーション処理
		CAnim3D::RequestEndLoop(FINISHER, 1.0f, (int)-1, (bool)-1);
		frm_int_ = 0;
		changeFlg_ = false;
		findFlg_ = false;
	}

	frm_int_++;

	//プレイヤーがボスの手にとらえられ続ける処理
	//ボスのボーンの掌の位置にプレイヤーの位置情報をセットし続けて
	//離れないようにする
	if (frm_int_ > BOSS_FINISHER_FRM)
	{
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		VECTOR bindPos = MV1GetFramePosition(hndl_, HAND_FRAME_NUM);
		bindPos.y -= player->GetRad();
		player->SetPosition(bindPos);
	}
}



//----------ここまでがステータス関係----------


void CChaseBoss::Target(bool flg)
{
	if (flg)
	{
		CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
		//プレイヤーを向く処理
		VECTOR vec = CMyMath::VecCreate(pos_, player->GetPosition());
		vec.y = 0.0f;
		rot_.y = atan2f(vec.x, vec.z);
	}
}



void CChaseBoss::Hit()
{
	
}

bool CChaseBoss::CheckFirstTarget()
{
	//ちょっと複雑になるから関数コメントない代わりに詳しくコメントアウトする
	
	//---------プレイヤーの位置情報を取得-----------
	CPlayerManager* playerManager = CPlayerManager::GetInstance();
	CPlayer* player = playerManager->GetPlayer();
	VECTOR playerPos = player->GetPosition();
	
	//---------プレイヤーまでの距離が離れすぎているならそもそも見つけられないようにする
	//まずは距離を取得
	float dis = CMyMath::GetDistance(playerPos, pos_);

	//見つけられるエリア外なら処理を終了
	if (dis > FIND_AREA)
	{
		return false;
	}
	
	//---------マップの当たり判定に使うためハンドルも取得------
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	
	
	//線分の当たり判定を使って、プレイヤーとボスの間に障害物がないかどうかを判定
	//判定して大丈夫ならボスがプレイヤーを追いかける処理に使っているフラグをオンにする
	MV1_COLL_RESULT_POLY colInfo = MV1CollCheck_Line(colMapHndl_, -1, pos_, playerPos);

	//障害物がないなら
	if (!colInfo.HitFlag)
	{
		return true;
	}
	else
		return false;
}

//プレイヤーを追いかける処理
void CChaseBoss::CheckChase()
{
	//---------ここでしたいこと----------
	//プレイヤーをボスが追いかける、プレイヤーを見失かったかどうかの判定
	//-----------------------------------------

	//---------プレイヤーの位置情報を取得-----------
	CPlayerManager* playerManager = CPlayerManager::GetInstance();
	CPlayer* player = playerManager->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	//---------マップの当たり判定に使うためハンドルも取得------
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	CInter* inter = CFieldManager::GetInstance()->GetInter();
	

	//現在見失っていないかどうかのチェック
	
	//線分の当たり判定を使って、プレイヤーとボスの間に障害物がないかどうかを判定
	//判定して大丈夫ならボスがプレイヤーを追いかける処理に使っているフラグをオンにする
	MV1_COLL_RESULT_POLY colInfo;
	colInfo = MV1CollCheck_Line(colMapHndl_, -1, pos_, playerPos);


	//障害物があるならプレイヤーを追いかけるのはやめる
	if (colInfo.HitFlag)
	{
		//ボスがプレイヤーを探すようにする
		serchInfo_.flg_ = true;

		//-----------索敵に必要な情報をここで入力しておく-------

		//一時的に値を保持しておく変数
		float interDis = 0.0f;
		VECTOR targetPos = { 0.0f };

		//一番近い交差点位置座標を見つける
		for (int interNum = 0; interNum < INTER_BONE_MAX_NUM; interNum++)
		{
			if (interNum % INTER_BW)
			{
				//参照する交差点の位置座標を手に入れる
				VECTOR interPos = MV1GetFramePosition(inter->GetFrmHndl(), interNum);
				float calcDis = 0.0f;

				//現在地から参照している交差点までの距離を格納
				calcDis = CMyMath::GetDistance(pos_, interPos);

				//絶対値で比べてより値が小さいほうが交差点に近い、
				//情報がまだ入ってない場合は先に情報を格納する必要があるので通る
				if (interDis == 0.0f ||
					CMyMath::Abs(interDis) > CMyMath::Abs(calcDis)) {

					//ここまで通ったということは一番近い交差点座標であることは間違いないため更新
					targetPos = interPos;
					interDis = calcDis;
				}
			}
		}
		
		//一番近い交差点位置情報渡し
		serchInfo_.useInterPos_ = targetPos;

		//フレーム単位の時間計算に使用した変数の初期化
		frm_int_ = 0;
		
		
		return;
	}

	
	

	//ボスがプレイヤーを追いかける判定
	VECTOR move = { 0 };

	//移動量計算
	move = CMyMath::VecCreate(pos_, playerPos);

	//6秒後にプレイヤーのもとにたどり着く計算式に使う
	int calcNum = BOSS_ARRIVAL * FRAME_RATE;

	//徐々に近づく
	calcNum -= frm_int_;

	//ベクトルの割り算を行う
	move.x /= calcNum;
	move.z /= calcNum;

	//ベクトルを現在座標に加算
	pos_ = CMyMath::VecAdd(pos_, move);

	
}

//プレイヤーを見失ってから一定時間索敵をする処理
void CChaseBoss::SerchChase()
{
	//---------ここでしたいこと----------
	//ここを規定時間以上通ったのに見つけられなかったら歩き状態に戻り、
	// 元の決められたルートに戻るようにする
	//プレイヤーを見つけるため索敵を行う
	//-----------------------------------------

	//---------プレイヤーの位置情報を取得-----------
	CPlayerManager* playerManager = CPlayerManager::GetInstance();
	CPlayer* player = playerManager->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	//---------マップの当たり判定に使うためハンドルも取得------
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	CInter* inter = CFieldManager::GetInstance()->GetInter();
	
	//現在見失っていないかどうかのチェック

	//線分の当たり判定を使って、プレイヤーとボスの間に障害物がないかどうかを判定
	//判定して大丈夫ならボスがプレイヤーを追いかける処理に使っているフラグをオンにする
	MV1_COLL_RESULT_POLY colInfo = MV1CollCheck_Line(colMapHndl_, -1, pos_, playerPos);

	//障害物がないなら見つけているので、追跡開始
	if (!colInfo.HitFlag)
	{
		//ボスがプレイヤーを探すようにする
		serchInfo_.flg_ = false;
		frm_int_ = 0;
		//ここで処理を終了する
		return;
	}

	//-----------------プレイヤー索敵処理------------------
	//現在プレイヤーを視認できる可能性が最も高い交差点ボーン上に向かう
	VECTOR move = { 0 };

	//移動量計算
	move = CMyMath::VecCreate(pos_, serchInfo_.useInterPos_);
	move.y = BOSS_APPEAR.y;

	//規定時間後に目的地にたどり着く計算式に使う
	int calcNum = BOSS_SERCH_TIME * FRAME_RATE;

	//ベクトルの割り算を行う
	move.x /= calcNum;
	move.z /= calcNum;

	//ベクトルを現在座標に加算
	pos_ = CMyMath::VecAdd(pos_, move);

	//もしボスがプレイヤーを捜索する規定時間が過ぎてもプレイヤーが見つけられていない場合
	//プレイヤーを見つけるのをあきらめて、元のルートに戻る

	//最後に一度だけ探す
	if (frm_int_ > BOSS_SERCH_TIME * FRAME_RATE)
	{
		//プレイヤーを見つける処理
		if (CheckFirstTarget())
		{
			//見つけているフラグをtrue
			findFlg_ = true;
			//ステータス変更フラグをtrue
			changeFlg_ = true;
			//規定ルートを通ているかフラグをfalse
			routeFlg_ = false;

			return;
		}

		//ここを通るなら歩きに戻る
		findFlg_ = false;

		CSound::StopBGM(CSound::BGM_MAIN);
		CSound::StopBGM(CSound::BGM_PLAY);
		CSound::PlayBGM(CSound::BGM_MAIN);
		CSound::PlayBGM(CSound::BGM_PLAY);
		CSound::StopBGM(CSound::BGM_ESCAPE);
		changeFlg_ = true;
	}
}

//ボスが決まった順路を徘徊する処理
void CChaseBoss::LoopRoute()
{
	//---------ここでしたいこと----------
	// ボスがルート上にいることを前提として
	// ボスが次のボーンに向かって進み続ける処理
	//-----------------------------------------

	int boneStart = BOSS_LOOP_START;
	int boneEnd = BOSS_LOOP_END;

	CInter* inter = CFieldManager::GetInstance()->GetInter();
	int frmHndl = inter->GetFrmHndl();

	//移動量の加算
	pos_.z += move_;

	//移動量がz座標において＋ならEND参照、-ならSTART参照
	if (move_ > 0){
		if (pos_.z > MV1GetFramePosition(frmHndl, BOSS_LOOP_END).z){
			move_ *= -1.0f;
		}
	}
	else if (move_ < 0){
		if (pos_.z < MV1GetFramePosition(frmHndl, BOSS_LOOP_START).z){
			move_ *= -1.0f;
		}
	}

	//プレイヤーを見つける処理
	if (CheckFirstTarget())
	{
		//見つけているフラグをtrue
		findFlg_ = true;
		//ステータス変更フラグをtrue
		changeFlg_ = true;
		//規定ルートを通ているかフラグをfalse
		routeFlg_ = false;
	}
}

//元の道に戻る処理
void CChaseBoss::ReturnRoute()
{
	//---------ここでしたいこと----------
	// ボスが一番近いボーン番号の位置座標に向けて目指す
	// 目指していたボーン座標に到着したとき
	//-----------------------------------------

	//---------マップの当たり判定に使うためハンドルも取得------
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	CInter* inter = CFieldManager::GetInstance()->GetInter();
	

	//交差点ボーン情報
	int frmHndl = inter->GetFrmHndl();

	//----どこが現在位置から一番近い交差点かを取得し、その方向に進む処理----
	
	//指定の条件に合った一番近い交差点を探す処理
	//一時的に値を保持しておく変数
	float interDis = 0.0f;
	VECTOR targetPos = { 0.0f };

	//一番近い交差点位置座標を見つける
	for (int interNum = 0; interNum < ROUTE_NUM; interNum++)
	{
		//参照する交差点の位置座標を手に入れる
		VECTOR interPos = MV1GetFramePosition(inter->GetFrmHndl(), BOSS_ROUTE[interNum]);
		float calcDis = 0.0f;

		//現在地から参照している交差点までの距離を格納
		calcDis = CMyMath::GetDistance(pos_, interPos);

		//絶対値で比べてより値が小さいほうが交差点に近い、
		//情報がまだ入ってない場合は先に情報を格納する必要があるので通る
		if (interDis == 0.0f ||
			CMyMath::Abs(interDis) > CMyMath::Abs(calcDis)) {

			//ここまで通ったということは一番近い交差点座標であることは間違いないため更新
			targetPos = interPos;
			interDis = calcDis;
		}
	}

	//-----交差点は見つけたので、そこに進むための処理-------
	//まずは障害物判定

	VECTOR calcPos = { 0 };
	calcPos.x = pos_.x - targetPos.x;
	calcPos.z = pos_.z - targetPos.z;
	//0より小さいと比べられないので
	calcPos.x = CMyMath::Abs(calcPos.x);
	calcPos.z = CMyMath::Abs(calcPos.z);

	//到着しているならフラグを立ててここで処理を終了
	if (calcPos.x < BOSS_RETURN_AREA && calcPos.z < BOSS_RETURN_AREA)
	{
		routeFlg_ = true;
		return;
	}

	//この処理に通る場合は索敵モードに入って見つからなかった時なので
	//交差点は横に並んでいる又はすでに該当の交差点かのどちらか
	if (calcPos.x > BOSS_RETURN_AREA)
	{
		if (pos_.x < targetPos.x)
		{
			pos_.x += BOSS_RETURN_SPD;
		}
		else
			pos_.x -= BOSS_RETURN_SPD;
	}
	if (calcPos.z > BOSS_RETURN_AREA)
	{
		if (pos_.z < targetPos.z)
		{
			pos_.z += BOSS_RETURN_SPD;
		}
		else
			pos_.z -= BOSS_RETURN_SPD;
	}
}

//ボスの周辺の車を止める
void CChaseBoss::StopStreet()
{
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		CEnemy* enemy = CEnemyManager::GetInstance()->GetEnemy(carNum);

		//ボスから決められた一定範囲
		if (CMyMath::RadiusCheck(pos_, SAFETY_CAR, enemy->GetPosition()))
		{
			enemy->SetMoveFlg(false);
		}
		else
			enemy->SetMoveFlg(true);
	}

	//車が止まっている車と激突しないようにする処理
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		CEnemy* enemy = CEnemyManager::GetInstance()->GetEnemy(carNum);

		if (!enemy->GetMoveFlg())
		{
			for (int checkNum = 0; checkNum < APPEAR_CAR_NUM; checkNum++)
			{
				CEnemy* checkEnemy = CEnemyManager::GetInstance()->GetEnemy(checkNum);

				if (checkNum != carNum)
				{
					//ボスから決められた一定範囲
					if (CMyMath::RadiusCheck(checkEnemy->GetPosition(), SAFETY_CAR, enemy->GetPosition()))
					{
						checkEnemy->SetMoveFlg(false);
					}
				}
			}
		}	
	}

	
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		CEnemy* enemy = CEnemyManager::GetInstance()->GetEnemy(carNum);

		if (!enemy->GetMoveFlg())
		{
			for (int checkNum = 0; checkNum < APPEAR_CAR_NUM; checkNum++)
			{
				CEnemy* checkEnemy = CEnemyManager::GetInstance()->GetEnemy(checkNum);

				if (checkNum != carNum)
				{
					//ボスから決められた一定範囲
					if (CMyMath::RadiusCheck(checkEnemy->GetPosition(), SAFETY_CAR, enemy->GetPosition()))
					{
						checkEnemy->SetMoveFlg(false);
					}
				}
			}
		}
	}
}