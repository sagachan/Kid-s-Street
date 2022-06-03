//KidUI.h
//KidUIシーン

#pragma once

#include "../../../UI/GameUIManager.h"
#include "../../../UI/UIBase.h"
#include "../../EnemyCommon.h"

//KidUIクラス
class CKidUI : public CUIBase
{
public:
	CKidUI();
	~CKidUI();
private:
	enum ASSERT_TYPE
	{
		ASSERT_INIT = -1,

		ASSERT_START,
		ASSERT_END,
		ASSERT_FINISH
	};

public:
	
	void Init() override;			//初期化
	void Load() override;			//読み込み
	void Set() override;			//各変数などに初期値を設定（セット）
	void Step() override;			//毎フレーム呼ぶ処理
	void Draw() override;			//描画
	void Fin() override;			//後処理

public:
	void SetKidFlg(bool flg) { kidFlg_ = flg; }

private:
	bool kidFlg_;
	CGameUI* uiAssert_[ASSERT_FINISH];
	int type_;
};