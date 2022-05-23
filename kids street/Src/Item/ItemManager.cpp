//ItemManager.cpp
//アイテム管理
//CItemへのアクセスは必ずCItemManagerを経由

#include "ItemManager.h"
#include "../Error/Error.h"

//CItemManagerの実体宣言、初期化
CItemManager* CItemManager::instance_ = nullptr;

namespace
{
	const float BOSS_ITEM_SCALE = 5.0f;
}
//コンストラクタ
CItemManager::CItemManager()
{
	//CItemのコンストラクタは自動で呼ばれます
	//変数初期化
	appearFlg_ = false;
	itemKind_ = INIT;
	itemHoldflg_ = true;
	useNum_ = 0;
	activate_ = false;
	dmg_ = 0;
	itemHoldflg_ = false;
	throwFlg_ = false;
	maxNum_ = 0;
	bossItem_.kind_ = INIT;
	bossItem_.num_ = 0;
	for(int kindNum = 0; kindNum < MAX_ITEM_KIND;kindNum++)
	{
		pr_itemFlg_[kindNum] = false;;
	}
}

//デストラクタ
CItemManager::~CItemManager()
{
	//CItemのデストラクタは自動で呼ばれます

}


//初期化
void CItemManager::Init()
{
	
	//消しゴムクラスオーバーライドと初期化
	for (int kind = 0; kind < MAX_ERASER; kind++)
	{
		itemEraser_[kind] = new CEraser;
		itemEraser_[kind]->Init();
	}

	//鉛筆クラスオーバーライドと初期化
	for (int kind = 0; kind < MAX_PENCIL; kind++)
	{
		itemPencil_[kind] = new CPencil;
		itemPencil_[kind]->Init();
	}

	//変数初期化
	for (int kind = 0; kind < MAX_ITEM_KIND; kind++)
	{
		pr_itemFlg_[kind] = false;
	}
}


//読み込み
void CItemManager::Load()
{
	//消しゴム
	MinimizeCall(itemEraser_, MAX_ERASER, VOID_LOAD);

	//鉛筆
	MinimizeCall(itemPencil_, MAX_PENCIL, VOID_LOAD);
}


//セット
void CItemManager::Set()
{
	//最初は消しゴムから始まる
	itemKind_ = ERASER;

	//消しゴム
	MinimizeCall(itemEraser_, MAX_ERASER, VOID_SET);

	//鉛筆
	MinimizeCall(itemPencil_, MAX_PENCIL, VOID_SET);
}


//ステップ
void CItemManager::Step()
{
	//プレイヤークラス取得
	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	
	//アイテムを使えるのかどうか
	if (appearFlg_ == true)
	{
		//入力関係(アイテムを選ぶ)
		StepInput();

		//アイテムを手にもてるなら　
		if (itemHoldflg_ == true)
		{
			

			//毎週初期化
			activate_ = false;

			//どのアイテムが選ばれているか
			switch (itemKind_)
			{
			case ERASER:
				for (int kind = 0; kind < MAX_ERASER; kind++)
				{
					//使用済みじゃないアイテムを見つける
					if (itemEraser_[kind]->GetUseFlg() == false)
					{
						//アイテムを手に持つ処理
						itemEraser_[kind]->SetPosition(player->GetPlayerHandPos());
						//ステップ処理は手に持っているアイテムしか通る必要がない
						itemEraser_[kind]->Step();
						 //今回手に持ってる配列番号を格納
						useNum_ = kind;
						//今手にアイテムを持てているかどうか
						activate_ = true;
						break;
					}
				}
				break;

			case PENCIL:
				for (int kind = 0; kind < MAX_PENCIL; kind++)
				{
					//使用済みじゃないアイテムを見つける
					if (itemPencil_[kind]->GetUseFlg() == false)
					{
						//アイテムを手に持つ処理
						itemPencil_[kind]->SetPosition(player->GetPlayerHandPos());
						//ステップ処理は手に持っているアイテムしか通る必要がない
						itemPencil_[kind]->Step();
						useNum_ = kind;
						activate_ = true;
						break;
					}
				}
				break;

			default:
				break;

			}//switch
		}//if

		////消しゴム
		//MinimizeCall(itemEraser_, MAX_ERASER, VOID_STEP);
		////鉛筆
		//MinimizeCall(itemPencil_, MAX_PENCIL, VOID_STEP);
	}

	//アイテムが投げられた時に、新しく投げられたアイテムが何かを確認して
	//そのアイテムのまだ使用されていないフラグの使用フラグを立てる処理
	if (throwFlg_ == true)
	{
		//どのアイテムが選ばれているか
		switch (itemKind_)
		{
		case ERASER:
			itemEraser_[useNum_]->SetUseFlg(true);	//使用フラグを立てる
			break;

		case PENCIL:
			itemPencil_[useNum_]->SetUseFlg(true);	//使用フラグを立てる
			break;

		default:
			break;
		}

		//一度だけ通ればいいからフラグを折る
		throwFlg_ = false;
		activate_ = false;
	}

	//アイテムの移動処理
	StepMove();
}



//反映
void CItemManager::Update()
{
	//手に持っているアイテムを反映するか
	if (activate_ == true)
	{
		switch (itemKind_)
		{
		case ERASER:

			itemEraser_[useNum_]->Update();
			break;

		case PENCIL:
			itemPencil_[useNum_]->Update();
			break;

		default:
			break;

		}
	}
}


//描画
void CItemManager::Draw()
{


	//アイテムを使えるか
	if (appearFlg_ == true)
	{
		//--------------手に持っているアイテムの描画処理------------
		//手に持っているアイテムを描画するか
		if (activate_ == true)
		{
			switch (itemKind_)
			{
			case ERASER:
				itemEraser_[useNum_]->Draw();
				break;
			
			case PENCIL:
				itemPencil_[useNum_]->Draw();
				break;
			default:
				break;

			}
		}
		//-----------------------------------------------------------

		//-------------投げられているアイテムの描画処理-----------
		// 処理速度を上げるため
		// 可能性があるときしかチェックしない
		if (pr_itemFlg_[FLG_ERASER])
		{
			for (int kind = 0; kind < MAX_ERASER; kind++)
			{
				//使用フラグが立っているかつそれが処理終了していないなら
				if (itemEraser_[kind]->GetMoveFlg())
				{
					//消しゴム描画
					itemEraser_[kind]->Draw();
				}
			}
		}
		//処理速度
		if (pr_itemFlg_[FLG_PENCIL])
		{
			for (int kind = 0; kind < MAX_PENCIL; kind++)
			{
				//使用フラグが立っているかつそれが処理終了していないなら
				if (itemPencil_[kind]->GetMoveFlg())
				{
					itemPencil_[kind]->Draw();
				}
			}
		}
		//------------------------------------------------------------------


	}
}

//削除
void CItemManager::Delete()
{
	//アイテム削除
	//消しゴムのステップ
	MinimizeCall(itemEraser_, MAX_ERASER, VOID_DELETE);

	//鉛筆のステップ
	MinimizeCall(itemPencil_, MAX_PENCIL, VOID_DELETE);
}

//後処理
void CItemManager::Fin()
{
	//アイテムの後処理を呼ぶ
	//消しゴム
	MinimizeCall(itemEraser_, MAX_ERASER, VOID_FIN);

	//消しゴムクラスメモリ開放
	for (int kind = 0; kind < MAX_ERASER; kind++)
	{
		delete itemEraser_[kind];
		itemEraser_[kind] = nullptr;
	}

	//鉛筆
	MinimizeCall(itemPencil_, MAX_PENCIL, VOID_FIN);

	//鉛筆クラスメモリ開放
	for (int kind = 0; kind < MAX_PENCIL; kind++)
	{
		delete itemPencil_[kind];
		itemPencil_[kind] = nullptr;
	}

}

//入力関係処理
void CItemManager::StepInput()
{
	//入力クラス取得
	CInput* input = CInput::GetInstance();

	//１が押されたときは消しゴムを選ぶ
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_1))
	{
		itemKind_ = ERASER;
	}
	//２が押されたときは鉛筆を選ぶ
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_2))
	{
		itemKind_ = PENCIL;
	}
}

//移動処理
void CItemManager::StepMove()
{
	for (int kind = 0; kind < MAX_ITEM_KIND; kind++)
	{
		//アイテムの種類分の処理速度向上のためのフラグ初期化
		pr_itemFlg_[kind] = false;
	}
	
	//消しゴム
	for (int kind = 0; kind < MAX_ERASER; kind++)
	{
		//移動するか
		if (itemEraser_[kind]->GetMoveFlg())
		{
			//移動計算する
			itemEraser_[kind]->Move();
			//移動処理がされているなら描画フラグを立てる
			pr_itemFlg_[FLG_ERASER] = true;
		}
	}

	//鉛筆
	for (int kind = 0; kind < MAX_PENCIL; kind++)
	{
		//使用フラグが立っているかつそれが処理終了していないなら
		if (itemPencil_[kind]->GetMoveFlg())
		{
			//移動計算する
			itemPencil_[kind]->Move();
			//移動処理がされているなら描画フラグを立てる
			pr_itemFlg_[FLG_PENCIL] = true;
		}
	}
}

//オーバーライドしたアイテムの構造体の中身をnum番目まで回して参照、タイプによって処理を分ける
void CItemManager::MinimizeCall(CItemBase* item[], int maxNum, VOID_TYPE type)
{
	//-------------ここでやりたいこと----------------
	//  毎回for文を書いて関数を呼ばないといけないものはもうまとめて呼べるように関数作ってしまおう
	// ---------------------------------------------- 

	for (int kind = 0; kind < maxNum; kind++)
	{
		switch (type)
		{
		case VOID_INIT:
			item[kind]->Init();break;

		case VOID_LOAD:
			item[kind]->Load();break;

		case VOID_SET:
			item[kind]->Set();break;

		case VOID_STEP:
			item[kind]->Step();break;

		case VOID_UPDATE:
			item[kind]->Update();break;

		case VOID_DRAW:
			item[kind]->Draw();break;

		case VOID_DELETE:
			item[kind]->Delete();break;

		case VOID_FIN:
			item[kind]->Fin();break;

		//どれにも属さない場合
		default:
			CError::VoidError();
			break;
		}
	}
}

//当たり判定更新
void CItemManager::HitUpdate()
{
	//-------------ここでやりたいこと----------------
	//  当たり判定チェックするために必要な情報を当たり判定管理クラスに渡してる
	// ---------------------------------------------- 

	VECTOR* eraserPos = (VECTOR*)malloc(sizeof(VECTOR) * MAX_ERASER);
	bool* eraserFlg = (bool*)malloc(sizeof(bool) * MAX_ERASER);

	//現在の状態に構造体の中身を更新する
	//(直接引数として使えないので構造体に入れてポインタとして渡すために必要)
	for (int item_num = 0; item_num < MAX_ERASER; item_num++)
	{
		eraserPos[item_num] = itemEraser_[item_num]->GetPosition();
		eraserFlg[item_num] = itemEraser_[item_num]->GetMoveFlg();
	}
	//当たり判定クラスに必要な情報を渡す
	CCollisionManager::GetInstance()->SetItemCollision(eraserPos, itemEraser_[0]->GetSimpleHit(), eraserFlg, ERASER);
	free(eraserPos);
	free(eraserFlg);
		
	VECTOR* pencilPos = (VECTOR*)malloc(sizeof(VECTOR) * MAX_PENCIL);
	bool* pencilFlg = (bool*)malloc(sizeof(bool) * MAX_PENCIL);
	//現在の状態に構造体の中身を更新する
	//(直接引数として使えないので構造体に入れてポインタとして渡すために必要)
	for (int item_num = 0; item_num < MAX_PENCIL; item_num++)
	{
		pencilPos[item_num] = itemPencil_[item_num]->GetPosition();
		pencilFlg[item_num] = itemPencil_[item_num]->GetMoveFlg();
	}
	//当たり判定クラスに必要な情報を渡す
	CCollisionManager::GetInstance()->SetItemCollision(pencilPos, itemPencil_[0]->GetSimpleHit(), pencilFlg, PENCIL);
	free(pencilPos); 
	free(pencilFlg);
}
	
//当たり判定処理（アイテムマネージャーによって行われた条件を通過したときに実行される
void CItemManager::DamageVanish(int num, ITEM_KIND kind)
{
	//-------------ここでやりたいこと----------------
	//  当たったアイテムを消して、当たったアイテムに設定されている分のダメージをボスに与える
	// ---------------------------------------------- 

	
	
	//受け取った引数のint型の数番目のアイテムのエンドフラグを立てることで使用終了する
	//ボスにダメージを与えるダメージ量を決める関数に今参照されているアイテムのダメージ数値を渡す
	switch (kind)
	{
	case ERASER:
		itemEraser_[num]->SetEndFlg(true);
		CEnemyManager::GetInstance()->GetBoss()->SetDmg(itemEraser_[num]->GetDmg());
		break;

	case PENCIL:
		itemPencil_[num]->SetEndFlg(true);
		CEnemyManager::GetInstance()->GetBoss()->SetDmg(itemPencil_[num]->GetDmg());
		break;
		
	default:
		break;
	}

	//ボスのダメージ処理が通るようにする
	CEnemyManager::GetInstance()->GetBoss()->SetColFlg(true);
	
}

//ボスのキャッチ時に起こるアイテム側の処理
void CItemManager::SetBossItemInfo(ITEM_KIND kind,int num)
{
	//-------------ここでやりたいこと----------------
	//  ボスが手にしたアイテムのボス取得フラグをtrueへ、
	// ボスの持つアイテムの種類とボスの持つアイテムの番号を構造体へ格納
	// ---------------------------------------------- 

	switch (kind)
	{
	case ERASER:
		itemEraser_[num]->SetBossFlg(true);
		bossItem_.kind_ = ERASER;
		bossItem_.num_ = num;
		break;

	case PENCIL:
		itemPencil_[num]->SetBossFlg(true);
		bossItem_.kind_ = PENCIL;
		bossItem_.num_ = num;
		break;

	default:
		break;
	}
}

//ボスにアイテムをとられたときに通る処理
void CItemManager::SetBossItemPos(VECTOR pos)
{
	//-------------ここでやりたいこと----------------
	//  ボスのものになったアイテムの位置情報更新
	// 引数で受け取った座標をボスアイテム情報構造体の格納情報と一致するアイテムに適用する
	// ---------------------------------------------- 

	switch(bossItem_.kind_)
	{
	case ERASER:
		itemEraser_[bossItem_.num_]->SetPosition(pos);
	
		break;
	case PENCIL:
		itemPencil_[bossItem_.num_]->SetPosition(pos);
		
		break;
	default:
		break;
	}
}

//ボスがアイテムを投げた時に通る処理
void CItemManager::SetBossItemThrow()
{
	//-------------ここでやりたいこと----------------
	//  ボスが投げたアイテムがボスアイテムとしての挙動を行うために必要なフラグをオンにする
	// ---------------------------------------------- 

	switch (bossItem_.kind_)
	{
	case ERASER:
		itemEraser_[bossItem_.num_]->SetBossThrowFlg(true);
		itemEraser_[bossItem_.num_]->SetScale(BOSS_ITEM_SCALE);
		break;
	case PENCIL:
		itemPencil_[bossItem_.num_]->SetBossThrowFlg(true);
		itemPencil_[bossItem_.num_]->SetScale(BOSS_ITEM_SCALE);
		break;
	default:
		break;
	}
}
	
	
