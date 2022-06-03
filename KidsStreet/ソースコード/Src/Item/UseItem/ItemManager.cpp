//ItemManager.cpp
//アイテム管理
//CItemへのアクセスは必ずCItemManagerを経由

#include "ItemManager.h"
#include "../../Library/Error/Error.h"
#include "../../Library/SagaLibrary.h"
#include "../../Library/Sound/Sound.h"
#include "../../Enemy/EnemyManager.h"
#include "../../UI/GameUIManager.h"

#include "../GatherItem/GatherFactory/GatherManager.h"
#include "../GatherItem/ItemProduct/GatherEraser/GatherEraser.h"
#include "../GatherItem/ItemProduct/GatherPencil/GatherPencil.h"
#include "../GatherItem/ItemProduct/ItemBox/ItemBox.h"
#include "../GatherItem/ItemProduct/GatherRuler/GatherRuler.h"
#include "../GatherItem/ItemProduct/GatherGlove/GatherGlove.h"

#include "Eraser/Eraser.h"
#include "Pencil/Pencil.h"
#include "Ruler/Ruler.h"
#include "Glove/Glove.h"

namespace
{
	const float BOSS_ITEM_SCALE = 5.0f;
}


//CItemManagerの実体宣言、初期化
CItemManager* CItemManager::instance_ = nullptr;

//オーバーライドしたアイテムの構造体の中身をnum番目まで回して参照、タイプによって処理を分ける
void CItemManager::MinimizeCall(CItemBase* item[], int maxNum, VOID_TYPE type)
{
	//-------------ここでやりたいこと----------------
	//  毎回for文を書いて関数を呼ばないといけないものはもうまとめて呼べるように関数作ってしまおう
	// ---------------------------------------------- 

	for (int kind = 0; kind < maxNum; kind++){
		switch (type){
		case VOID_INIT:item[kind]->Init(); break;
		case VOID_LOAD:item[kind]->Load(); break;
		case VOID_SET:item[kind]->Set(); break;
		case VOID_STEP:item[kind]->Step(); break;
		case VOID_UPDATE:item[kind]->Update(); break;
		case VOID_DRAW:item[kind]->Draw(); break;
		case VOID_DELETE:item[kind]->Delete(); break;
		case VOID_FIN:item[kind]->Fin(); break;

			//どれにも属さない場合
		default:
			CError::MinimizeVoidError();
			break;
		}
	}
}

//オーバーライドしたアイテムの構造体の中身をnum番目まで回して参照、タイプによって処理を分ける
void CItemManager::MinimizeCall(CGatherBase* item[], int maxNum, VOID_TYPE type)
{
	for (int kind = 0; kind < maxNum; kind++) {
		switch (type) {
		case VOID_INIT:item[kind]->Init(); break;
		case VOID_LOAD:item[kind]->Load(); break;
		case VOID_SET:item[kind]->Set(); break;
		case VOID_STEP:item[kind]->Step(); break;
		case VOID_UPDATE:item[kind]->Update(); break;
		case VOID_DRAW:item[kind]->Draw(); break;
		case VOID_FIN:item[kind]->Fin(); break;

			//どれにも属さない場合
		default:
			CError::MinimizeVoidError();
			break;
		}
	}
}


//コンストラクタ
CItemManager::CItemManager()
{
	//CItemのコンストラクタは自動で呼ばれます
	//変数初期化
	itemKind_ = ITEM_INIT;
	itemHoldflg_ = true;
	useNum_ = 0;
	activate_ = false;
	itemHoldflg_ = false;
	throwFlg_ = false;
	bossItem_.kind_ = ITEM_INIT;
	bossItem_.num_ = 0;
}

//デストラクタ
CItemManager::~CItemManager()
{
	//CItemのデストラクタは自動で呼ばれます

}


//初期化
void CItemManager::Init()
{
	//アイテム収集管理クラス生成
	CGatherManager::CreateInstance();

	int itemNum = 0;

	//消しゴムクラスオーバーライド
	for (itemNum = 0; itemNum < MAX_ERASER; itemNum++){
		 
		useItem_[itemNum] = new CEraser;
	}

	//鉛筆クラスオーバーライド
	for (int kind = 0; kind < MAX_PENCIL; kind++){
		useItem_[itemNum] = new CPencil;
		itemNum++;
	}

	//定規クラスオーバーライド
	for (int kind = 0; kind < MAX_RULER; kind++) {
		useItem_[itemNum] = new CRuler;
		itemNum++;
	}
	
	for (int kind = 0; kind < MAX_GLOVE; kind++){
		useItem_[itemNum] = new CGlove;
		itemNum++;
	}
	for (itemNum = 0; itemNum < MAX_ITEM_NUM; itemNum++)
	{
		useItem_[itemNum]->SetItemNum(itemNum);
	}

	//まとめて初期化
	MinimizeCall(useItem_, MAX_ITEM_NUM, VOID_INIT);

	//UI関係クラスオーバーライド
	gatherItem_[ITEM_ID_BOX] = new CItemBox;
	gatherItem_[ITEM_ID_ERASER] = new CGatherEraser;
	gatherItem_[ITEM_ID_PENCIL] = new CGatherPencil;
	gatherItem_[ITEM_ID_RULER] = new CGatherRuler;
	gatherItem_[ITEM_ID_GLOVE] = new CGatherGlove;
	
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_INIT);
}


//読み込み
void CItemManager::Load()
{
	MinimizeCall(useItem_, MAX_ITEM_NUM, VOID_LOAD);
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_LOAD);

	CSound::LoadSE(CSound::SE_GET);
}


//セット
void CItemManager::Set()
{
	MinimizeCall(useItem_, MAX_ITEM_NUM, VOID_SET);
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_SET);
}


//ステップ
void CItemManager::Step()
{
	//プレイヤークラス取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();

	//入力関係(アイテムを選ぶ)
	StepInput();

	//アイテムを手にもてるなら　
	if (itemHoldflg_ == true) {
		//毎週初期化
		activate_ = false;

		//手にもてるアイテムを探す
		SerchItem(useItem_, itemKind_);
	}

	//アイテムが投げられた時に、新しく投げられたアイテムが何かを確認して
	//そのアイテムのまだ使用されていないフラグの使用フラグを立てる処理
	if (throwFlg_ == true) {
		//選ばれている使用フラグを立てる
		useItem_[useNum_]->SetUseFlg(true);
		//一度だけ通ればいいからフラグを折る
		throwFlg_ = false;
		activate_ = false;
	}

	//アイテムの移動処理
	StepMove();
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_STEP);
}



//反映
void CItemManager::Update()
{
	//手に持っているアイテムを反映するか
	if (activate_ == true){
		useItem_[useNum_]->Step();
	}

	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_UPDATE);
}


//描画
void CItemManager::Draw()
{
	//--------------手に持っているアイテムの描画処理------------
		//手に持っているアイテムを描画するか
	if (activate_ == true){
		useItem_[useNum_]->Draw();
	}
	
	//-------------投げられているアイテムの描画処理-----------
	for (int itemNum = 0; itemNum < MAX_ITEM_NUM; itemNum++) {
		//使用フラグが立っているかつそれが処理終了していないなら
		if (useItem_[itemNum]->GetMoveFlg()) {
			useItem_[useNum_]->Update();
			useItem_[itemNum]->Draw();
		}
	}
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_DRAW);
}

//削除
void CItemManager::Delete()
{
	//アイテム削除
	MinimizeCall(useItem_, MAX_ITEM_NUM, VOID_DELETE);
	MinimizeCall(gatherItem_, ITEM_ID_MAX, VOID_DELETE);
}

//後処理
void CItemManager::Fin()
{
	//アイテム使用クラスメモリ開放
	for (int itemNum = 0; itemNum < MAX_ITEM_NUM; itemNum++){
		delete useItem_[itemNum];
		useItem_[itemNum] = nullptr;
	}

	//収集クラスメモリ開放
	for (int kind = 0; kind < ITEM_MAX_KIND; kind++) {
		delete gatherItem_[kind];
		gatherItem_[kind] = nullptr;
	}

	CGatherManager::GetInstance()->DeleteAll();
	CGatherManager::DeleteInstance();
}

//入力関係処理
void CItemManager::StepInput()
{
	//入力クラス取得
	CInput* input = CInput::GetInstance();
	ITEM_KIND oldKind = itemKind_;
	//まだ選ばれておらず1が押されたときは消しゴムを選ぶ
	if (itemKind_ != ERASER){
		if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_1)) {
			itemKind_ = ERASER;
		}
	}
	//2が押されたときは鉛筆を選ぶ
	if (itemKind_ != PENCIL) {
		if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_2)) {
			itemKind_ = PENCIL;
		}
	}
	//3が押されたときは三角定規を選ぶ
	if (itemKind_ != RULER) {
		if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_3)) {
			itemKind_ = RULER;
		}
	}
	//4が押されたときは三角定規を選ぶ
	if (itemKind_ != GLOVE) {
		if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_4)) {
			itemKind_ = GLOVE;
		}
	}


	//現在のアイテムが処理開始時に読み込んでいたものから変わっているなら
	if (oldKind != itemKind_){
		itemHoldflg_ = false;
		activate_ = false;
	}
}

//移動処理
void CItemManager::StepMove()
{
	for (int itemNum = 0; itemNum < MAX_ITEM_NUM; itemNum++){
		//使用フラグが立っているかつそれが処理終了していないなら
		if (useItem_[itemNum]->GetMoveFlg()) {
			useItem_[itemNum]->Move();
		}
	}
}

//全体の基底ポインタ配列の参照開始番号と終了番号を手に入れる
CItemManager::ClassNumInfo CItemManager::CheckItem(ITEM_KIND kind)
{
	//アイテム使用クラスを参照する場合に自分が見たいアイテムタイプの番号を
	//引数として入力することで、アイテムが全体の基底クラスポインタ配列の中の
	//何番目から何番目に入っているのかをチェックできる
	
	//参照番号の宣言
	ClassNumInfo numInfo = {0};
	numInfo.maxNum_ = MAX_ERASER;
	if (kind == ERASER) { return numInfo; }
	numInfo.initNum_ = MAX_ERASER; numInfo.maxNum_ += MAX_PENCIL;
	if (kind == PENCIL) { return numInfo; }
	numInfo.initNum_ += MAX_PENCIL; numInfo.maxNum_ += MAX_RULER;
	if (kind == RULER) { return numInfo; }
	numInfo.initNum_ += MAX_RULER; numInfo.maxNum_ += MAX_GLOVE;
	if(kind == GLOVE) { return numInfo; }
	numInfo = { 0 };
	return numInfo;
}

//手にもてるアイテムを探す
void CItemManager::SerchItem(CItemBase* item[], ITEM_KIND kind)
{
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	ClassNumInfo numInfo = CheckItem(kind);
	for (numInfo.initNum_; numInfo.initNum_ < numInfo.maxNum_; numInfo.initNum_++)
	{
		//使用済みじゃないアイテムを見つける
		if (item[numInfo.initNum_]->GetUseFlg() == false)
		{
			//アイテムを手に持つ処理
			item[numInfo.initNum_]->SetPosition(player->GetPlayerHandPos());
			//ステップ処理は手に持っているアイテムしか通る必要がない
			item[numInfo.initNum_]->Step();
			//今回手に持ってる配列番号を格納
			useNum_ = numInfo.initNum_;
			//今手にアイテムを持てているかどうか
			activate_ = true;
			break;
		}
	}
}

////当たり判定更新
//void CItemManager::HitUpdate()
//{
//	//-------------ここでやりたいこと----------------
//	//  当たり判定チェックするために必要な情報を当たり判定管理クラスに渡してる
//	// ----------------------------------------------
//	CCollisionManager::ITEM_DATA* itemData =
//		(CCollisionManager::ITEM_DATA*)malloc(sizeof(CCollisionManager::ITEM_DATA) * MAX_ITEM_NUM);
//
//	//現在の状態に構造体の中身を更新する
//	//(直接引数として使えないので構造体に入れてポインタとして渡すために必要)
//	for (int itemNum = 0; itemNum < MAX_ITEM_NUM; itemNum++)
//	{
//		itemData[itemNum].pos_ = useItem_[itemNum]->GetPosition();
//		itemData[itemNum].useflg_ = useItem_[itemNum]->GetMoveFlg();
//		itemData[itemNum].rad_ = useItem_[itemNum]->GetRad();
//	}
//	//当たり判定クラスに必要な情報を渡す
//	CCollisionManager::GetInstance()->SetItemCollision(itemData);
//	free(itemData);
//


//当たり判定処理（アイテムマネージャーによって行われた条件を通過したときに実行される
void CItemManager::DamageVanish(int num)
{
	//-------------ここでやりたいこと----------------
	//  当たったアイテムを消して、当たったアイテムに設定されている分のダメージをボスに与える
	// ---------------------------------------------- 

	//受け取った引数のint型の数番目のアイテムのエンドフラグを立てることで使用終了する
	//ボスにダメージを与えるダメージ量を決める関数に今参照されているアイテムのダメージ数値を渡す
	useItem_[num]->SetEndFlg(true);
	CEnemyManager::GetInstance()->GetBoss()->Damage(useItem_[num]->GetDmg());
	
}

//ボスのキャッチ時に起こるアイテム側の処理
void CItemManager::SetBossItemInfo(int num)
{
	//-------------ここでやりたいこと----------------
	//  ボスが手にしたアイテムのボス取得フラグをtrueへ、
	//	ボスの持つアイテムの番号を構造体へ格納
	// ---------------------------------------------- 
	useItem_[num]->SetBossFlg(true);
	bossItem_.num_ = num;
}

//ボスにアイテムをとられたときに通る処理
void CItemManager::SetBossItemPos(VECTOR pos)
{
	//-------------ここでやりたいこと----------------
	//  ボスのものになったアイテムの位置情報更新
	// 引数で受け取った座標をボスアイテム情報構造体の格納情報と一致するアイテムに適用する
	// ---------------------------------------------- 
	useItem_[bossItem_.num_]->SetPosition(pos);
}

//ボスがアイテムを投げた時に通る処理
void CItemManager::SetBossItemThrow()
{
	//-------------ここでやりたいこと----------------
	//  ボスが投げたアイテムがボスアイテムとしての挙動を行うために必要なフラグをオンにする
	// ---------------------------------------------- 
	useItem_[bossItem_.num_]->SetBossThrowFlg(true);
	useItem_[bossItem_.num_]->SetScale(BOSS_ITEM_SCALE);
}
	
bool CItemManager::IDFromKind(ITEM_ID id)
{
	switch (id){
	case ITEM_ID_ERASER:if(itemKind_ == ERASER)return true;break;
	case ITEM_ID_PENCIL:if (itemKind_ == PENCIL)return true; break;
	case ITEM_ID_RULER:if (itemKind_ == RULER)return true;break;
	case ITEM_ID_GLOVE:if (itemKind_ == GLOVE)return true; break;
	}

	return false;
}
	
