

#pragma once

#include "DxLib.h"
#include "../../Scene/PlayScene.h"
#include "../EnemyBase.h"
#include "../EnemyCommon.h"
#include "../../Field/FieldCommon.h"


class CWallKid : public CEnemyBase
{

private:
	enum KID_ANIM_NO
	{
		BIND,
		WALK
	};
	
public:
	CWallKid();		//�R���X�g���N�^
	~CWallKid();		//�f�X�g���N�^

public:
	void Init(){}
	void Load();		//�ǂݍ��݁i���[�h�j
	void Set();
	void Step(){}
	void Update(){}		//�X�V
	void Draw();		//�`��
	void Delete();		//�폜
	void Fin();			//�㏈��
	void Hit();

public:
	void	SetPos(VECTOR pos, CEnemyBase::MOVE_DIR dir);				//�����l�ݒ�

private:
	MOVE_DIR	dir_;								//�G�l�~�[����
};