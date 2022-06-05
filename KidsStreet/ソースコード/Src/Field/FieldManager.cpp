//FieldManager.cpp
//フィールド管理
//CFieldへのアクセスは必ずCFieldManagerを経由

#include "FieldManager.h"
//CFieldManagerの実体宣言、初期化
CFieldManager* CFieldManager::instance_ = nullptr;

//読み込み
void CFieldManager::Load()
{
	field_.Load();
	road_.Load();
	inter_.Load();
	pole_.Load();
	navi_.Load();
}

//セット
void CFieldManager::Set()
{
	field_.Set();
	road_.Set();
	inter_.Set();
	pole_.Set();
}

//ステップ
void CFieldManager::Step()
{
	inter_.InterManager();
	navi_.Step();
}

//更新
void CFieldManager::Update()
{
	field_.Update();
	road_.Update();
	pole_.Update();
}

//描画
void CFieldManager::Draw()
{
	field_.Draw();
	road_.Draw();
	pole_.Draw();
	navi_.Draw();
}


