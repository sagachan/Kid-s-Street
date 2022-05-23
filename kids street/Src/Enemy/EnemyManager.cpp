//EnemyManager.cpp
//エネミー管理
//CEnemyへのアクセスは必ずCEnemyManagerを経由

#include "EnemyManager.h"
#include "../Library/Error/Error.h"
#include "../Field/FieldCommon.h"
#include "Boss/BossHP/BossFrameHP.h"
#include "Boss/BossHP/BossHP.h"
#include "../UI/GameUIManager.h"
#include "../Library/Sound/Sound.h"

namespace
{													
	const VECTOR	ENEMY_BOSS_APPEAR = VGet(-1520.0f, 0.0f,1700.0f);					//ボス出現ライン
	const VECTOR	ENEMY_BOSS_AREA_BACK = VGet(4.0f,6.0f,890.0f);
	const VECTOR	ENEMY_BOSS_AREA_FRONT = VGet(4.0f, 6.0f, 970.0f);
}

//CEnemyManagerの実体宣言、初期化
CEnemyManager* CEnemyManager::instance_ = nullptr;


//コンストラクタ
CEnemyManager::CEnemyManager()
{
	//CEnemyのコンストラクタは自動で呼ばれます
	Init();
}

//デストラクタ
CEnemyManager::~CEnemyManager()
{
	//CEnemyのデストラクタは自動で呼ばれます
	
}


//初期化
void CEnemyManager::Init()
{
	Sceneflg_ = true; //切り替えるとシーン変更
	pos_plus_ = { 0 };//車同士の間隔空け

	int enemyNum = 0;
	for (enemyNum = 0; enemyNum < APPEAR_CAR_NUM; enemyNum++){
		car_[enemyNum] = new CEnemy;
		carInfo_[enemyNum] = car_[enemyNum];
		enemy_[enemyNum] = car_[enemyNum];
	}
	for (int enemy_index = 0; enemy_index < APPEAR_KID_NUM; enemy_index++){
		kid_[enemy_index] = new CKid;
		kidInfo_[enemy_index] = kid_[enemy_index];
		enemy_[enemyNum] = kid_[enemy_index];
		enemyNum++;
	}

	for (int enemy_index = 0; enemy_index < APPEAR_WALL_NUM; enemy_index++) {
		wall_[enemy_index] = new CWallKid;
		wallInfo_[enemy_index] = wall_[enemy_index];
		enemy_[enemyNum] = wall_[enemy_index];
		enemyNum++;
	}

	boss_ = new CBoss;
	enemy_[enemyNum] = boss_;
	bossInfo_ = enemy_[enemyNum];
	enemyNum++;
	
	chase_ = new CChaseBoss;
	enemy_[enemyNum] = chase_;
	chaseInfo_ = enemy_[enemyNum];
	enemyNum++;

	//UI関係
	ui_[BOSS_HP] = new CBossHP;
	ui_[BOSS_FRAME_HP] = new CBossFrameHP;
	kidUI_ = new CKidUI;
	ui_[KID_ASSERT] = kidUI_;

	MinimizeCall(enemy_, APPEAR_ENEMY_MAX_NUM, VOID_INIT);
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_INIT);
}


//読み込み
void CEnemyManager::Load()
{
	MinimizeCall(enemy_, APPEAR_ENEMY_MAX_NUM, VOID_LOAD);
	
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_LOAD);
}


//セット
void CEnemyManager::Set()
{
	//車の出現座標をボーンで決める
	int carAppearFrm = 0;
	//ボーン情報読み込み
	carAppearFrm = MV1LoadModel("Data/Enemy/Car/carPosBone.x");

	//車のボーンの最大値受け取り
	int carBoneMax = MV1GetFrameNum(carAppearFrm);

	//ボーン情報から位置情報を読み取り配列に入れる
	VECTOR* carPos = (VECTOR*)malloc(sizeof(VECTOR) * APPEAR_CAR_NUM);

	//車の出現座標をボーンで管理、座標をボーンから読み取り配列に入れる
	int trueNum = 0;
	for (int frmNum = 0; frmNum < carBoneMax;frmNum++){
		if (frmNum % 2){
			carPos[trueNum] = MV1GetFramePosition(carAppearFrm, frmNum);
			trueNum++;
			if (trueNum == APPEAR_CAR_NUM)
				break;
		}
	}

	//車のテーブル
	EnemyInfo carData[APPEAR_CAR_NUM] = { 0 };

	//車の出現座標のｚだけを書き換える
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++){
		carData[carNum] = CAR_DATA[carNum];
		carData[carNum].pos_.z = carPos[carNum].z;
	}

	free(carPos);

	for (int enemy_index = 0; enemy_index < APPEAR_CAR_NUM; enemy_index++){
		//車の初期位置設定
		car_[enemy_index]->SetPos(carData[enemy_index].pos_, carData[enemy_index].dir_);
	}


	//子どもの出現座標
	for (int enemy_index = 0; enemy_index < APPEAR_KID_NUM; enemy_index++)
	{
		kid_[enemy_index]->SetRoute(KID_ROUTE_NUM[enemy_index]);
	}

	
	
	for (int enemy_index = 0; enemy_index < APPEAR_WALL_NUM; enemy_index++) {
		//初期位置設定
		wall_[enemy_index]->SetPos(WALL_DATA[enemy_index].pos_, WALL_DATA[enemy_index].dir_);
	}

	CFieldManager* fieldManager = CFieldManager::GetInstance();
	CInter* inter = fieldManager->GetInter();

	//交差点ハンドル情報格納
	int interHndl = inter->GetFrmHndl();
	VECTOR	bossInterPos = MV1GetFramePosition(interHndl, 28);
	bossInterPos.y = -1.0f;
	bossInterPos.z -= 5.0f;

	//ボス初期位置設定
	boss_->SetPosition(bossInterPos);
	bossflg_ = true;

	MinimizeCall(enemy_, APPEAR_ENEMY_MAX_NUM, VOID_SET);
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_SET);
}


//ステップ
void CEnemyManager::Step()
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	CFieldManager* fieldManager = CFieldManager::GetInstance();
	CInter* inter = fieldManager->GetInter();
	
	//交差点ハンドル情報格納
	int interHndl = inter->GetFrmHndl();
	VECTOR	bossInterPos = MV1GetFramePosition(interHndl, 28);
	VECTOR	playerPos = player->GetPosition();
	float	interRad = inter->GetInterRad() / 2;


	//ボス戦開始条件
	if (CMyMath::RadiusCheck(bossInterPos.x, interRad, playerPos.x) &&
		CMyMath::RadiusCheck(bossInterPos.z, interRad, playerPos.z) &&
		Sceneflg_ == true)
	{
		CSound::FinSound();
		CSound::LoadBGM(CSound::BGM_BOSS);
		CSound::PlayBGM(CSound::BGM_BOSS);
		Sceneflg_ = false;
	}

	//リターンを押したときにボス戦から抜けて通常ループへ戻る処理
	if (CInput::GetInstance()->IsPush(CInput::GetInstance()->INPUT_KIND_KEY, KEY_INPUT_RETURN)){
		Sceneflg_ = true;
		bossflg_ = false;
	}


	if (Sceneflg_){
		MinimizeCall(carInfo_, APPEAR_CAR_NUM, VOID_STEP);
		MinimizeCall(kidInfo_, APPEAR_KID_NUM, VOID_STEP);
		chaseInfo_->Step();
	}
	else{
		bossInfo_->Step();
		WallCage();
	}

	MinimizeCall(wallInfo_, SET_WALL_NUM, VOID_HIT);
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_STEP);
}

//反映
void CEnemyManager::Update()
{
	if (Sceneflg_){
		MinimizeCall(carInfo_, APPEAR_CAR_NUM, VOID_UPDATE);
		MinimizeCall(kidInfo_, APPEAR_KID_NUM, VOID_UPDATE);
		chaseInfo_->Update();
	}
	else{
		bossInfo_->Update();
	}
}


//描画
void CEnemyManager::Draw()
{
	if (Sceneflg_){
		MinimizeCall(carInfo_, APPEAR_CAR_NUM, VOID_DRAW);
		MinimizeCall(kidInfo_, APPEAR_KID_NUM, VOID_DRAW);
		MinimizeCall(wallInfo_, SET_WALL_NUM, VOID_DRAW);
		chaseInfo_->Draw();
	}
	else{
		bossInfo_->Draw();
		for (int enemy_index = SET_WALL_NUM; enemy_index < APPEAR_WALL_NUM; enemy_index++)
		{
			wallInfo_[enemy_index]->Draw();
		}
	}

	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_DRAW);
}


//削除
void CEnemyManager::Delete()
{
	MinimizeCall(enemy_, APPEAR_ENEMY_MAX_NUM, VOID_DELETE);
}


//後処理
void CEnemyManager::Fin()
{
	MinimizeCall(enemy_, APPEAR_ENEMY_MAX_NUM, VOID_FIN);
	
	for (int enemyNum = 0; enemyNum < APPEAR_ENEMY_MAX_NUM; enemyNum++){
		delete enemy_[enemyNum];
		enemy_[enemyNum] = nullptr;
	}
	CGameUIManager::GetInstance()->MinimizeCall(ui_, UI_MAX_NUM, VOID_FIN);

	CSound::FinSound();
}

//オーバーライドしたクラスの構造体の中身をnum番目まで回して参照、タイプによって処理を分ける
void CEnemyManager::MinimizeCall(CEnemyBase* enemy[], int maxNum, VOID_TYPE type)
{
	for (int kind = 0; kind < maxNum; kind++){
		switch (type){
		case VOID_INIT:enemy[kind]->Init(); break;
		case VOID_LOAD:enemy[kind]->Load(); break;
		case VOID_SET:enemy[kind]->Set(); break;
		case VOID_STEP:enemy[kind]->Step(); break;
		case VOID_UPDATE:enemy[kind]->Update(); break;
		case VOID_HIT:enemy[kind]->Hit(); break;
		case VOID_DRAW:enemy[kind]->Draw(); break;
		case VOID_DELETE:enemy[kind]->Delete(); break;
		case VOID_FIN:enemy[kind]->Fin(); break;

		//どれにも属さない場合
		default:CError::MinimizeVoidError();break;
		}
	}
}

void CEnemyManager::WallCage()
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPosition();

	if (WALL_X_START > playerPos.x ||
		WALL_X_END < playerPos.x ||
		WALL_Z_START > playerPos.z ||
		WALL_Z_END < playerPos.z)
	{
		player->HitSet();
	}
}