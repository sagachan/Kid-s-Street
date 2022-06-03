//�A�C�e�����W�p���N���X

#include "../../../ItemCommon.h"
#include "../../../../UI/GameUI.h"
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
	void Update();					//�X�V
	void PropertyWindow();
	void SelectWindow();

public:
	enum PROPERTY_TYPE{
		PROPERTY_OPEN,
		PROPERTY_CLOSE
	};

protected:
	ITEM_KIND kind_;			//�h���N���X�ƂȂ���W�A�C�e���N���X���g�p�A�C�e���N���X�Ƃ̘A�g���s�����߂ɕK�v
	bool endFlg_;				//true�Ȃ�A�C�e�������łɏW�߂��Ă���
	bool propertyFlg_;			//�A�C�e���擾���Ɉ�x�����\������A�C�e�����UI�p�t���O
	int type_;					//��̃A�C�e���^�C�venum�ƕ��p���Ďg��
	int propertyhndl_;
	CGameUI* uiProperty_[PROPERTY_CLOSE];
};