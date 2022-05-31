//GatherItem.h

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

	//ゲッター
	VECTOR GetPos()			{ return itemPos_; }

	//セッター
	void SetPos(VECTOR pos) { itemPos_ = pos; }

protected:
	VECTOR	itemPos_;

};