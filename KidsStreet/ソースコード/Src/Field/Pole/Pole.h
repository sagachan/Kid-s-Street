//Pole.h
//�t�B�[���h�N���X

#pragma once

#include "DxLib.h"
#include "../../Library/Animation/Model/model.h"


class CPole : public CModel
{
public:
	CPole();
	~CPole();

public:
	void Load();
	void Set();
	void Step(){}
	void Update();
	void Draw();
	void Delete();
	void Fin();

public:
	void SetPosFlg(bool flg) { posFlg_ = flg; }

public:
	bool posFlg_;			//���̃t���O��true�̎��͈ʒu���������n�ɍX�V��������
};