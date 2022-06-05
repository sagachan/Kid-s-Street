//Navi.h
//Naviシーン

#pragma once

#include "../../Library/Animation/Model/model.h"

//Naviクラス
class CNavi : public CModel
{
private:
	enum NAVI_TYPE
	{
		NAVI_WALL,
		NAVI_HOUSE,
		NAVI_END
	};
public:
	CNavi();
	~CNavi();

	void Load();		//読み込み
	void Set();			//各変数などに初期値を設定（セット）
	void Step();		//毎フレーム呼ぶ処理
	void Draw();		//描画

private:
	void UpdateNaviRot();
	void CheckNaviType();

private:
	int type_;							//ナビタイプを格納
};