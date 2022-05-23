#pragma once

#include "DxLib.h"
#include "../ItemBase.h"


class CPencil : public CItemBase
{
public:
	CPencil(){}
	~CPencil(){}

public:
	void Init(){}
	void Load();
	void Set();
	void Step();
	void Update(){}
	void Draw();
	void Delete(){}
	void Fin();
};