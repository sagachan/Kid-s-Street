//Eraser.h
//Á‚µƒSƒ€ƒNƒ‰ƒX

#pragma once

#include "DxLib.h"
#include "../ItemBase.h"


class CEraser : public CItemBase
{ 
public:
	CEraser(){}
	~CEraser(){}

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