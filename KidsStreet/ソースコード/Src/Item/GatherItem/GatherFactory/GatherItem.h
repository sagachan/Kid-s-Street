//GatherItem.h
//アイテムの大本の基底クラス
//アイテムタイプを作成するときに使う
//例:Gather
#pragma once
#include "DxLib.h"

class CGatherItem
{
public:
	CGatherItem();
	virtual ~CGatherItem();

public:
	virtual void Init(VECTOR pos) = 0;	//初期化
	virtual void Load(const char* file_path) = 0;		//読み込み
	virtual void Step() = 0;							//ステップ
	virtual void Draw() = 0;							//描画
	virtual void Delete() = 0;							//削除
	virtual void Fin() = 0;								//後処理

	//セッター
	void SetPos(VECTOR pos) { itemPos_ = pos; }	//座標設定

	//ゲッター
	VECTOR GetPos() { return itemPos_; }
	

protected:
	VECTOR itemPos_;
};