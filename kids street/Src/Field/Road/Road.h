//Road.h
//道クラス

#pragma once

#include "DxLib.h"
#include "../FieldCommon.h"
#include "../../Library/Animation/Model/model.h"

class CRoad : public CModel
{
public:
	
public:
	CRoad();
	~CRoad();

public:
	void Init();
	void Load();
	void Set();
	void Step();
	void Update();
	void Draw();
	void Delete();
	void Fin();

public:
	//ゲッター
	bool	Is_in_Air() { return air_flg_; }			//今現在空中にいるかどうか、当たっていないかどうかを返す
	MapInfo GetMapInfo() { return mapInfo_; }

	//セッター
	void	SetAirFlg(bool flg) { air_flg_ = flg; }

private:
	MapInfo					mapInfo_;
	bool					air_flg_;
};