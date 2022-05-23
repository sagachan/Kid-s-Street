//BossFrameHP.h
//BossFrameHPシーン

#pragma once

#include "../../../UI/UIBase.h"

//BossFrameHPクラス
class CBossFrameHP : public CUIBase
{
public:
	CBossFrameHP();
	~CBossFrameHP();

	
	void Init() override;			//初期化
	void Load() override;			//読み込み
	void Set() override;			//各変数などに初期値を設定（セット）
	void Step() override;			//毎フレーム呼ぶ処理
	void Draw() override;			//描画
	void Fin() override;			//後処理


};