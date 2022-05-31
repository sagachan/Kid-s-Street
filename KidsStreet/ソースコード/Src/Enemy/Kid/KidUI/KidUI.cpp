//KidUI.cpp

#include "KidUI.h"
#include "DxLib.h"
#include "../../../Library/Input/Input.h"

namespace
{
	
}


CKidUI::CKidUI()
{
	Init();
}

CKidUI::~CKidUI()
{

}

//初期化
void CKidUI::Init()
{
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//生成
	uiAssert_[ASSERT_START] = ui_manager->CreateUI(CGameUIManager::UI_TYPE_ASSERT);
	uiAssert_[ASSERT_START]->Init(60.0f, 20.0f);
	uiAssert_[ASSERT_START]->Load("Data/UI/KidUI/KidAssertStart.png");

	//生成
	uiAssert_[ASSERT_END] = ui_manager->CreateUI(CGameUIManager::UI_TYPE_ASSERT);
	uiAssert_[ASSERT_END]->Init(60.0f, 20.0f);
	uiAssert_[ASSERT_END]->Load("Data/UI/KidUI/KidAssertEnd.png");

	kidFlg_ = false;
	type_ = 0;
}

//読み込み
void CKidUI::Load()
{

}

//各変数などに初期値を設定（セット）
void CKidUI::Set()
{
	
}

//毎フレーム呼ぶ処理
void CKidUI::Step()
{
	if (kidFlg_)
	{
		CInput* input = CInput::GetInstance();
		if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_RETURN))
		{
			type_++;
		}

		switch (type_) {
		case ASSERT_START:	uiAssert_[ASSERT_START]->SetDrawFlg(true);	break;
		case ASSERT_END:	uiAssert_[ASSERT_END]->SetDrawFlg(true);
							uiAssert_[ASSERT_START]->SetDrawFlg(false); break;
		case ASSERT_FINISH: 
			kidFlg_ = false; 
			uiAssert_[ASSERT_END]->SetDrawFlg(false);
			CGameUIManager::GetInstance()->SetInputFlg(false); 
			type_ = 0;
			break;
		}
		
	}
}


//描画
void CKidUI::Draw()
{
	
}


//後処理
void CKidUI::Fin()
{
	//UI管理後処理
	CGameUIManager::GetInstance()->DeleteAll();

}