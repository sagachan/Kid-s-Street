//FieldManager.h
//フィールド管理
//CFieldへのアクセスは必ずCFieldManagerを経由

#pragma once

#include "Map/Field.h"
#include "Inter/Inter.h"
#include "Road/Road.h"
#include "FieldCommon.h"
#include "Pole/Pole.h"
#include "Umbrella/Umbrella.h"
#include "Navi/Navi.h"

class CFieldManager
{
public:
	CFieldManager(){}
	~CFieldManager(){}
	
public:
	static void CreateInstance() { if (!instance_)instance_ = new CFieldManager; }
	static CFieldManager* GetInstance() { return instance_; }
	static void DeleteInstance() { if (instance_)delete instance_; instance_ = nullptr; }

public:
	void Init(){}
	void Load();
	void Set();
	void Step();
	void Update();
	void Draw();
	void Delete(){}
	void Fin(){}
	
	
public:
	//クラス取得関連関数
	CInter* GetInter()		{ return &inter_; }
	CRoad* GetRoad()		{ return &road_; }
	CPole* GetPole()		{ return &pole_; }
	CUmbrella* GetUmbrella() { return &umbrella_; }

private:
	static CFieldManager*	instance_;
	CField					field_;								//フィールドクラス
	CInter					inter_;								//交差点クラス
	CRoad					road_;								//道クラス
	CPole					pole_;								//電柱クラス
	CUmbrella				umbrella_;							//傘クラス
	CNavi					navi_;								//道案内クラス
};