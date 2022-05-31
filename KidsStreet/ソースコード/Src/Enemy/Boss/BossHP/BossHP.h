//BossHP.h
//BossHPシーン

#pragma once

#include "../../../UI/UIBase.h"
#include "../../../UI/GameUIManager.h"
//BossHPクラス
class CBossHP : public CUIBase
{
public:
	CBossHP();
	~CBossHP();

	//初期化
	void Init() override;

	//読み込み
	void Load() override;

	//各変数などに初期値を設定（セット）
	void Set() override;

	//毎フレーム呼ぶ処理
	void Step() override;

	//描画
	void Draw() override;

	//後処理
	void Fin() override;

private:
	CGameUI* hp_;
};