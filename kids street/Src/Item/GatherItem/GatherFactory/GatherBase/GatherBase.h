//�A�C�e�����W�p���N���X

#include "../../../ItemCommon.h"
#pragma once

class CGatherBase
{
public:
	CGatherBase();
	virtual ~CGatherBase();

	virtual void Init() = 0;		//������
	virtual void Load() = 0;		//�ǂݍ���
	virtual void Set() = 0;			//�ݒ�
	virtual void Step() = 0;		//���t���[���Ăԏ���
	virtual void Draw() = 0;		//�`��
	virtual void Fin() = 0;			//�㏈��

public:
	ITEM_KIND kind_;			//�h���N���X�ƂȂ���W�A�C�e���N���X���g�p�A�C�e���N���X�Ƃ̘A�g���s�����߂ɕK�v
};