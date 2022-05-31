//UI用基底クラス

#pragma once

class CUIBase
{
public:
	CUIBase();
	virtual ~CUIBase();

	virtual void Init() = 0;			//初期化
	virtual void Load() = 0;			//読み込み
	virtual void Set() = 0;				//設定
	virtual void Step() = 0;			//毎フレーム呼ぶ処理
	virtual void Draw() = 0;			//描画
	virtual void Fin() = 0;				//後処理
};