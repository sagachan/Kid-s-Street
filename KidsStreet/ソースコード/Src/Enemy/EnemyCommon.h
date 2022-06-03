//�G�l�~�[�֌W�ŋ��ʂɎg���\���̂������
#pragma once
#include "EnemyBase.h"
#include "../Library/LibraryCommon.h"
#include "DxLib.h"

enum ENEMY_UI_TYPE
{
	BOSS_HP,
	BOSS_FRAME_HP,
	KID_ASSERT,
	UI_MAX_NUM
};

enum DMG_TYPE
{
	DMG_INIT,
	DMG_WEAK = 1,
	DMG_NORMAL = 5,
	DMG_STRONG = 10,
	DMG_FINISHER = 100
};

struct EnemyInfo
{
	VECTOR					pos_;			//���݈ʒu
	CEnemyBase::MOVE_DIR	dir_;			//�Ԑ����
};

//�G�o���p�����[�^
namespace
{
	const int APPEAR_CAR_NUM = 10;				//�o��������Ԃ̑䐔
	const int APPEAR_KID_NUM = 5;				//�o��������q���̐�
	const int APPEAR_WALL_NUM = 13;				//�ǂƂ��ďo��������q���̐�
	const int APPEAR_BOSS_NUM = 2;				//�o������{�X�̐�
	const int APPEAR_ENEMY_MAX_NUM =			//�o������G�l�~�[�̑���
		APPEAR_CAR_NUM + APPEAR_KID_NUM + APPEAR_WALL_NUM + APPEAR_BOSS_NUM;


	const int	SET_WALL_NUM = 3;				//�ǂƂ��ďo��������q���̊�{��
}

//�G�o���p�����[�^
namespace
{
	const EnemyInfo CAR_DATA[APPEAR_CAR_NUM]
	{
		//���C���Ԑ�
		{VGet(-8.0f, 4.0f, 0.0f), CEnemyBase::BACK_MOVE},
		{VGet(-40.0f, 4.0f, 0.0f), CEnemyBase::FRONT_MOVE},
		{VGet(-40.0f, 4.0f, 0.0f), CEnemyBase::FRONT_MOVE},
		{VGet(-8.0f, 4.0f, 0.0f), CEnemyBase::BACK_MOVE},
		{VGet(-940.0f, 4.0f, 0.0f), CEnemyBase::FRONT_MOVE},

		//���ΎԐ�
		{VGet(-1640.0f, 4.0f, 0.0f), CEnemyBase::FRONT_MOVE},
		{VGet(860.0f, 4.0f, 0.0f), CEnemyBase::FRONT_MOVE},
		{VGet(-8.0f, 4.0f, 0.0f), CEnemyBase::BACK_MOVE},
		{VGet(-8.0f, 4.0f, 0.0f), CEnemyBase::BACK_MOVE},
		{VGet(-940.0f, 4.0f, 0.0f), CEnemyBase::FRONT_MOVE}

	};

	const EnemyInfo WALL_DATA[APPEAR_WALL_NUM]
	{
		{VGet(-60.0f, 8.0f, 1800.0f), CEnemyBase::BACK_MOVE},
		{VGet(-20.0f, 5.0f, 1800.0f), CEnemyBase::BACK_MOVE},
		{VGet(20.0f, 8.0f, 1800.0f), CEnemyBase::BACK_MOVE},

		{VGet(-1560.0f, 8.0f, 1760.0f), CEnemyBase::BACK_MOVE},
		{VGet(-1520.0f, 5.0f, 1760.0f), CEnemyBase::BACK_MOVE},
		{VGet(-1480.0f, 8.0f, 1760.0f), CEnemyBase::BACK_MOVE},

		{VGet(-1560.0f, 8.0f, 1650.0f), CEnemyBase::FRONT_MOVE},
		{VGet(-1520.0f, 5.0f, 1650.0f), CEnemyBase::FRONT_MOVE},
		{VGet(-1480.0f, 8.0f, 1650.0f), CEnemyBase::FRONT_MOVE},

		{VGet(-1450.0f, 8.0f, 1665.0f), CEnemyBase::LEFT_MOVE},
		{VGet(-1450.0f, 5.0f, 1705.0f), CEnemyBase::LEFT_MOVE},
		{VGet(-1450.0f, 8.0f, 1745.0f), CEnemyBase::LEFT_MOVE},

		{VGet(1570.0f, 5.0f, 1655.0f), CEnemyBase::RIGHT_MOVE}
	};

	const int KID_ROUTE_NUM[APPEAR_KID_NUM] = { 0,4,6,10,12};

}

//�GUI�p�����[�^
namespace
{
	const float BOSS_HP_UI_X = 10.0f;
	const float BOSS_HP_UI_Y = 20.0f;
	const VECTOR BOSS_HP_END_POS = VGet(2050.0f, 2000.0f, 0.0f);
	const VECTOR2 BOSS_HP_POS = { 10.0f, 25.0f };
}

//�G�̍ו��p�����[�^
namespace
{	
	const int	FRAME_MAX			= 27;			//�{�X
	const int	BOSS_RAGE_CHANCE	= 500;			//�{�X���\���m��
	const int	BOSS_SLASH_CHANCE	= 100;			//�{�X���ガ�����m��
	const int	BOSS_RARE_CHANCE	= 400;			//�{�X���p���`����m��
	const int	KID_ROUTE_FRM_MAX	= 17;
	const float SAFETY_CAR			= 50.0f;		//�Ԃ��{�X�ɂԂ���Ȃ��悤�Ƀu���[�L�𓥂ދ���
	const int	BOSS_THROW_TIME		= 1000;			//�{�X���������A�C�e���̗L������
	const float WALL_BW				= 40.0f;		//�Ǔ��m�̊Ԋu
	const int	BOSS_MAX_HP			= 100;			//�̗͂̍ő�l
	const int	BOSS_HP_LOW			= 50;			//�{�X�̗̑͂������艺�Ȃ�U���p�^�[���ω�

	//�֘A
	const VECTOR	ENEMY_ROT_FRONT = VGet(0.0f, 0.0f, 0.0f);				//�G�l�~�[�̉�]�l
	const VECTOR	ENEMY_ROT_BACK	= VGet(0.0f, -3.14f, 0.0f);				//�G�l�~�[�̉�]�l
	const VECTOR	ENEMY_ROT_RIGHT = VGet(0.0f, 1.6f, 0.0f);				//�G�l�~�[�̉�]�l
	const VECTOR	ENEMY_ROT_LEFT	= VGet(0.0f, -1.6f, 0.0f);				//�G�l�~�[�̉�]�l

	const float WALL_X_START = -1565.0f;
	const float WALL_X_END = -1450.0f;
	const float WALL_Z_START = 1650.0f;
	const float WALL_Z_END = 1760.0f;
}