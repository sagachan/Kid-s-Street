//PlayerManager.h
//�v���C���[�Ǘ�
//CPlayer�ւ̃A�N�Z�X�͕K��CPlayerManager���o�R

#pragma once

#include "Player.h"
#include "HP/PlayerHP.h"
#include "HP/FrameHP.h"
#include "../UI/UIBase.h"

class CPlayerManager
{
public:

	CPlayerManager();	//�R���X�g���N�^
	~CPlayerManager();	//�f�X�g���N�^

public:
	//�C���X�^���X����
	static void CreateInstance() { if (!instance_) instance_ = new CPlayerManager; }
	//�C���X�^���X�擾
	static CPlayerManager* GetInstance() { return instance_; }
	//�C���X�^���X�폜
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	//������
	void Init();

	//�ǂݍ���
	void Load();

	//�Z�b�g
	void Set();

	//�X�e�b�v
	void Step();

	//���f
	void Update();

	//�`��
	void Draw();

	//�폜
	void Delete();

	//�㏈��
	void Fin();

	//�v���C���[�N���X���擾
	CPlayer* GetPlayer() { return &player_; }

private:
	static CPlayerManager* instance_;	//�C���X�^���X

	CPlayer		player_;	//�v���C���[�N���X
	CPlayerHP	hp_;		//�v���C���[��HPUI
	CFrameHP	hpFrame_;

	//�V�KUI�����ꂽ�炱���ɒǉ�
	enum UI_Type
	{
		PLAYER_HP,
		FRAME_HP,
		UI_MAX_NUM
	};

	CUIBase* ui_[UI_MAX_NUM];
};