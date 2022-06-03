//アイテム収集用基底クラス

#include "../../../ItemCommon.h"
#include "../../../../UI/GameUI.h"
#pragma once

class CGatherBase
{
public:
	CGatherBase();
	virtual ~CGatherBase();

	virtual void Init() = 0;		//初期化
	virtual void Load() = 0;		//読み込み
	virtual void Set() = 0;			//設定
	virtual void Step() = 0;		//毎フレーム呼ぶ処理
	virtual void Draw() = 0;		//描画
	virtual void Fin() = 0;			//後処理

public:
	void Update();					//更新
	void PropertyWindow();
	void SelectWindow();

public:
	enum PROPERTY_TYPE{
		PROPERTY_OPEN,
		PROPERTY_CLOSE
	};

protected:
	ITEM_KIND kind_;			//派生クラスとなる収集アイテムクラスが使用アイテムクラスとの連携を行うために必要
	bool endFlg_;				//trueならアイテムがすでに集められている
	bool propertyFlg_;			//アイテム取得時に一度だけ表示するアイテム情報UI用フラグ
	int type_;					//上のアイテムタイプenumと併用して使う
	int propertyhndl_;
	CGameUI* uiProperty_[PROPERTY_CLOSE];
};