//Field.h
//�t�B�[���h�N���X

#pragma once

#include "DxLib.h"


class CField
{
public:
	//���f���f�[�^�̎�ފǗ�
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
	int		m_handle[MAP_TYPE_NUM];	//�n���h��
	VECTOR	m_pos[2];		//���W
	VECTOR	rot_;	//��]�l
};