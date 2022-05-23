//GameUIItem.h
//IDとフラグによって自分の描画を管理する
#pragma once

#include "../GameUI.h"
#include "DxLib.h"
#include "../../Item/ItemCommon.h"
#include "../../Item/GatherItem/GatherFactory/GatherManager.h"

class CGameUIItem :public CGameUI
{
public:
	CGameUIItem();
	~CGameUIItem();

public:
	void Init(float posX, float posY) override;	//初期化
	void Load(const char* file_path) override;		//読み込み
	void Step() override;							//ステップ
	void Draw() override;							//描画
	void Delete() override;							//削除
	void Fin() override;							//後処理


private:
	int handle_;	//画像ハンドル
	ITEM_ID id_;
};