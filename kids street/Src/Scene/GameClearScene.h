//GameClearScene.h
//ゲームクリアシーン

#pragma once

#include "SceneBase.h"

//ゲームクリアクラス
class CGameClearScene :public CSceneBase
{
public:
	CGameClearScene();
	~CGameClearScene();

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
	//文字情報構造体
	struct TextInfo
	{
		int handle;
		float pos_x;
		float pos_y;
		float base_pos_y;
		float size;
		float wave_angle;
	};

	TextInfo text_info_;	//文字情報
};