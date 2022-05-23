//FieldManager.cpp
//フィールド管理
//CFieldへのアクセスは必ずCFieldManagerを経由

#include "FieldManager.h"
//CFieldManagerの実体宣言、初期化
CFieldManager* CFieldManager::instance_ = nullptr;

//コンストラクタ
CFieldManager::CFieldManager()
{
}

//デストラクタ
CFieldManager::~CFieldManager()
{
}

void CFieldManager::Init()
{
	field_.Init();
	road_.Init();
	inter_.Init();
	
}


//読み込み
void CFieldManager::Load()
{
	field_.Load();
	road_.Load();
	inter_.Load();
}



//セット
void CFieldManager::Set()
{
	field_.Set();
	road_.Set();
	inter_.Set();
}


//ステップ
void CFieldManager::Step()
{
	field_.Step();
	road_.Step();
	inter_.InterManager();
}


//更新
void CFieldManager::Update()
{
	field_.Update();
	road_.Update();
	
}


//描画
void CFieldManager::Draw()
{
	field_.Draw();
	road_.Draw();
	
}


//削除
void CFieldManager::Delete()
{
	field_.Delete();
	road_.Delete();
	inter_.Delete();
}


//後処理
void CFieldManager::Fin()
{
	field_.Fin();
	road_.Fin();
	inter_.Fin();
	
}

