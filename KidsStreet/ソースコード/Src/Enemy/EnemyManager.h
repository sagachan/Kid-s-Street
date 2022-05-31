//EnemyManager.h
//�G�l�~�[�Ǘ�
//CEnemy�ւ̃A�N�Z�X�͕K��CEnemyManager���o�R

#pragma once

#include "EnemyBase.h"
#include "Car/Enemy.h"
#include "Kid/EnemyKid.h"
#include "Boss/EnemyBoss.h"
#include "DxLib.h"
#include "../Scene/PlayScene.h"
#include "EnemyBase.h"
#include "../Scene/PlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Library/Input/Input.h"
#include "../Collision/CollisionManager.h"
#include "Chase/ChaseBoss.h"
#include "../Library/LibraryCommon.h"
#include "../UI/UIBase.h"
#include "Kid/EnemyWallKid.h"
#include "Kid/KidUI/KidUI.h"


class CEnemyManager
{
public:

	CEnemyManager();	//�R���X�g���N�^
	~CEnemyManager();	//�f�X�g���N�^

public:
	//�C���X�^���X����
	static void CreateInstance() { if (!instance_) instance_ = new CEnemyManager; }
	//�C���X�^���X�擾
	static CEnemyManager* GetInstance() { return instance_; }
	//�C���X�^���X�폜
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }

public:
	void Init();					//������
	void Load();					//�ǂݍ���
	void Set();
	void Step();					//�X�e�b�v
	void Update();					//���f
	void Draw();					//�`��
	void Delete();					//�폜
	void Fin();						//�㏈��

public:
	CEnemy* GetEnemy(int enemyNum) { return car_[enemyNum]; }			//�G�l�~�[�N���X���擾
	CBoss* GetBoss() { return boss_; }									//�{�X�N���X���擾
	CKid* GetKid(int enemyNum) { return kid_[enemyNum]; }
	CKidUI* GetKidUI() { return kidUI_; }
	bool GetSceneFlg() { return Sceneflg_; }
	void SetSceneFlg(bool flg) { Sceneflg_ = flg; }

private:
	void MinimizeCall(CEnemyBase* enemy[], int maxNum, VOID_TYPE type);//�\���̎Q�Ə����Z�k
	void WallCage();

private:
	static CEnemyManager* instance_;			//�C���X�^���X

	//�N���X�֌W�ϐ�
	CEnemyBase* enemy_[APPEAR_ENEMY_MAX_NUM];
	

	CEnemyBase* carInfo_[APPEAR_CAR_NUM];
	CEnemy* car_[APPEAR_CAR_NUM];

	CEnemyBase* kidInfo_[APPEAR_KID_NUM];
	CKid* kid_[APPEAR_KID_NUM];

	CEnemyBase* wallInfo_[APPEAR_WALL_NUM];
	CWallKid* wall_[APPEAR_WALL_NUM];

	CEnemyBase* bossInfo_;
	CBoss* boss_;

	CEnemyBase* chaseInfo_;
	CChaseBoss* chase_;

	
	//UI�֌W�N���X
	CUIBase* ui_[UI_MAX_NUM];
	CKidUI* kidUI_;



	//�ʏ�ϐ�
	VECTOR pos_plus_;							//�ԓ��m�̊Ԋu��
	bool Sceneflg_;								//�V�[������

	

	bool bossflg_;
};
