//ChaseBoss.h
//�`�F�C�X�{�X�N���X

#pragma once

#include "DxLib.h"
#include "../EnemyBase.h"
#include "../../AI/AIBase.h"
#include "../EnemyCommon.h"


class CChaseBoss : public CEnemyBase
{
private:
	enum CHASE_ANIM_NO
	{
		APPEAR,
		FINISHER,
		PUNCH,
		ROLL,
		RUN,
		WALK
	};

	//����������v���C���[��T���Ƃ��Ɏg�����\����
	struct SerchInfo
	{
		VECTOR	useInterPos_;				//���G���邽�߂Ɏg�������_�̈ʒu���
		bool	flg_;					//�������Ă��邩�ǂ������m�F����t���O

	};

public:
	CChaseBoss();			//�R���X�g���N�^
	~CChaseBoss();			//�f�X�g���N�^

	//------override-------
public:
	void Init();			//������
	void Load();			//�ǂݍ��݁i���[�h�j
	void Set();
	void Step();			//���t���[���Ăԏ����i����j
	void Update();			//�X�V
	void Draw();			//�`��
	void Delete();			//�폜
	void Fin();				//�㏈��
	void Hit();
	
	//----------���̃N���X�ȊO�Ŏg���Ȃ��֐�-----------
private:
	void Target(bool flg);					//������true�Ȃ�v���C���[�̕�������������
	bool CheckFirstTarget();				//�ŏ��Ɍ�����Ƃ��̔���
	void CheckChase();						//�ǂ������Ă��鎞�ɒʂ锻��
	void ReturnRoute();						//���炩���ߌ��߂Ă���������H�ɖ߂鏈��
	void LoopRoute();						//���߂�ꂽ���H���{�X���p�j���鏈��
	void SerchChase();						//�v���C���[���������Ă����莞�ԍ��G�����鏈��
	void StopStreet();						//�����_�ɂ��鎩���̎��ӂ̎Ԃ̈ړ����~�߂邱�ƂŌ�ʎ��̂�h������
	
//-----------��ԑJ�ڃA�j���[�V�����Ǘ�------------
	void StepAI();
	void StepAppear();						//�o���ԍX�V
	void StepWalk();						//���s��ԍX�V
	void StepRun();							//���s��ԍX�V
	void StepRoll();						//��]��ԍX�V
	void StepPunch();						//���ŏ�ԍX�V
	void StepFinisher();					//�m�E��ԍX�V

public:
	//�Z�b�^�[
	void SetChangeFlg() {changeFlg_ = true;}					//��ԑJ�ڂ��s��ꂽ�Ƃ���true��
	
private:
	//AI�֌W�ϐ�
	bool		changeFlg_;
	SerchInfo	serchInfo_;
	int			colMapHndl_;
	bool		routeFlg_;				//���߂�ꂽ�������ݒʂ��Ă��邩�ǂ������`�F�b�N����t���O(true�Ȃ�ʂ��Ă���)
	bool		attackFlg_;				//�U���\���ǂ���
	AIBase*		enemy_ai_;
};