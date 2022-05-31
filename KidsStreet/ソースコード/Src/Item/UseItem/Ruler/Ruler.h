#pragma once

#include "DxLib.h"
#include "../ItemBase.h"


class CRuler : public CItemBase
{
public:
	CRuler(){}
	~CRuler(){}

public:
	void Init(){}
	void Load();
	void Set();
	void Step();
	void Update();
	void Draw();
	void Delete(){}
	void Fin();
	void Hit();
};