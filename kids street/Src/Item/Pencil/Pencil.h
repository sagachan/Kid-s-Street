#pragma once

#include "DxLib.h"
#include "../ItemBase.h"


class CPencil : public CItemBase
{
public:
	CPencil();
	~CPencil();

public:
	void Init();
	void Load();
	void Set();
	void Step();
	void Move();
	void Update();
	void Draw();
	void Delete();
	void Fin();



public:
	VECTOR GetHit() { return hit_radius_; }
	float	GetSimpleHit() { return radius_; }
private:
	
};