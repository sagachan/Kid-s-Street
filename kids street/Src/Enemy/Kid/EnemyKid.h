//Enemy.h
//�G�l�~�[�N���X

#pragma once

#include "DxLib.h"
#include "../../Scene/PlayScene.h"
#include "../EnemyBase.h"
#include "../EnemyCommon.h"
#include "../../Field/FieldCommon.h"
#include "../../AI/AIBase.h"


class CKid : public CEnemyBase
{

private:
	enum KID_ANIM_NO
	{
		BIND,
		WALK
	};
	
public:
	CKid();		//�R���X�g���N�^
	~CKid();		//�f�X�g���N�^

public:
	void Init();			//������
	void Load();			//�ǂݍ��݁i���[�h�j
	void Set();
	void Step();			//���t���[���Ăԏ����i����j
	void Update();			//�X�V
	void Draw();			//�`��
	void Delete();			//�폜
	void Fin();				//�㏈��
	CKid* Clone();			//�N���[��
	void Hit();


public:
	void Move(int dir);											//�G�̈ړ�����
	void RouteSelect();

public:
	//�Z�b�^�[
	void SetRoute(int boneNum) { initRouteNum_ = boneNum; }		//�q���̏����o�����W
	void SetKidNum(int enemyNum) { kidNum_ = enemyNum; }		//�q���ԍ���ݒ�

	//�Q�b�^�[
	

private:
	void Rotation();									//1����鏈��
	void StartEnd();									//START����END�܂�KID���s������
	void Target(bool flg);								//true�Ȃ�v���C���[�̕�����Ɍ���
	//-----------��ԑJ�ڃA�j���[�V�����Ǘ�------------
	void StepAI();
	void StepWalk();				//���s��ԍX�V
	void StepBind();				//�ߔ���ԍX�V
	
private:

	enum
	{
		NONE = 0,
		START,
		END,
		ROTATION
	};

	enum WALK_TYPE
	{
		WALK_START_END,
		WALK_ROTATION
	};

	enum SELECT_TYPE
	{
		START_FROM_MOVE,							//START����n�܂������I��
		END_FROM_MOVE								//END����n�܂������I��
	};

	MOVE_DIR	dir_;								//�G�l�~�[����
	int			kidRoute_[INTER_MAX_NUM];		//�q�����ʂ�Ƃ��Ɏg����
	int			initRouteNum_;						//���̎q���N���X�̏������[�g�ԍ�
	int			currentRoute_;						//���݂̃{�[���̔ԍ�
	SELECT_TYPE	selectType_;							//���I����@
	WALK_TYPE walkType_;						//�q���̕����^�C�v�I��
	VECTOR      frmPosArray_[INTER_MAX_NUM];	//�{�[���̈ʒu
	float       enemySpd_;						//�G�̈ړ����x		
	int			kidNum_;						//�����̍\���̔ԍ����m��
	bool		moveFlg_;
	AIBase*		enemy_ai_;
};