//SceneBase.h
//シーン用基底クラス

#pragma once

class CSceneBase
{

public:
	CSceneBase();
	virtual ~CSceneBase();

	//初期化
	virtual void Init() = 0;

	//読み込み
	virtual void Load() = 0;

	//各変数などに値をセット
	virtual void Set() = 0;

	//毎フレーム呼ぶ処理
	virtual void Step() = 0;

	//描画
	virtual void Draw() = 0;

	//後処理
	virtual void Fin() = 0;
};