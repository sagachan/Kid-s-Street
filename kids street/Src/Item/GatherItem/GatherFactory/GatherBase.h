//収集アイテム用基底クラス
//すでに存在するタイプに適用されたアイテムの基底クラス
//例:消しゴムGatherクラスなど

#pragma once

class CGatherBase
{
public:
	CGatherBase();
	virtual ~CGatherBase();


	//初期化
	virtual void Init() = 0;
	//読み込み
	virtual void Load() = 0;
	//設定
	virtual void Set() = 0;
	//毎フレーム呼ぶ処理
	virtual void Step() = 0;
	//描画
	virtual void Draw() = 0;
	//後処理
	virtual void Fin() = 0;
};