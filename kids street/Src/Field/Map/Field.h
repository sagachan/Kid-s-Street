//Field.h
//フィールドクラス

#pragma once

#include "DxLib.h"


class CField
{
public:
	//モデルデータの種類管理
	enum
	{
		school,
		bill,
		house,
		sky,
		MAP_TYPE_NUM
	};

public:
	CField();
	~CField();

public:
	void Init();
	void Load();
	void Set();
	void Step();
	void Update();
	void Draw();
	void Delete();
	void Fin();
	

private:
	int		m_handle[MAP_TYPE_NUM];	//ハンドル
	VECTOR	m_pos[2];		//座標
	VECTOR	rot_;	//回転値
};