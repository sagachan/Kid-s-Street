//エネミー関係で共通に使う可能性のあるもの
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
	VECTOR					pos_;			//現在位置
	CEnemyBase::MOVE_DIR	dir_;			//車線状態
};

//敵出現パラメータ
namespace
{
	const int APPEAR_CAR_NUM = 10;				//出現させる車の台数
	const int APPEAR_KID_NUM = 5;				//出現させる子供の数
	const int APPEAR_WALL_NUM = 13;				//壁として出現させる子供の数
	const int APPEAR_BOSS_NUM = 2;				//出現するボスの数
	const int APPEAR_ENEMY_MAX_NUM =			//出現するエネミーの総数
		APPEAR_CAR_NUM + APPEAR_KID_NUM + APPEAR_WALL_NUM + APPEAR_BOSS_NUM;


	const int	SET_WALL_NUM = 3;				//壁として出現させる子供の基本数
}

//敵出現パラメータ
namespace
{
	const EnemyInfo CAR_DATA[APPEAR_CAR_NUM]
	{
		//メイン車線
		{VGet(-8.0f, 4.0f, 0.0f), CEnemyBase::BACK_MOVE},
		{VGet(-40.0f, 4.0f, 0.0f), CEnemyBase::FRONT_MOVE},
		{VGet(-40.0f, 4.0f, 0.0f), CEnemyBase::FRONT_MOVE},
		{VGet(-8.0f, 4.0f, 0.0f), CEnemyBase::BACK_MOVE},
		{VGet(-940.0f, 4.0f, 0.0f), CEnemyBase::FRONT_MOVE},

		//反対車線
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

//敵UIパラメータ
namespace
{
	const float BOSS_HP_UI_X = 10.0f;
	const float BOSS_HP_UI_Y = 20.0f;
	const VECTOR BOSS_HP_END_POS = VGet(2050.0f, 2000.0f, 0.0f);
	const VECTOR2 BOSS_HP_POS = { 10.0f, 25.0f };
}

//敵の細部パラメータ
namespace
{	
	const int	FRAME_MAX			= 27;			//ボス
	const int	BOSS_RAGE_CHANCE	= 500;			//ボスが暴れる確率
	const int	BOSS_SLASH_CHANCE	= 100;			//ボスが薙ぎ払う確率
	const int	BOSS_RARE_CHANCE	= 400;			//ボスがパンチする確率
	const int	KID_ROUTE_FRM_MAX	= 17;
	const float SAFETY_CAR			= 50.0f;		//車がボスにぶつからないようにブレーキを踏む距離
	const int	BOSS_THROW_TIME		= 1000;			//ボスが投げたアイテムの有効時間
	const float WALL_BW				= 40.0f;		//壁同士の間隔
	const int	BOSS_MAX_HP			= 100;			//体力の最大値
	const int	BOSS_HP_LOW			= 50;			//ボスの体力がこれより下なら攻撃パターン変化

	//関連
	const VECTOR	ENEMY_ROT_FRONT = VGet(0.0f, 0.0f, 0.0f);				//エネミーの回転値
	const VECTOR	ENEMY_ROT_BACK	= VGet(0.0f, -3.14f, 0.0f);				//エネミーの回転値
	const VECTOR	ENEMY_ROT_RIGHT = VGet(0.0f, 1.6f, 0.0f);				//エネミーの回転値
	const VECTOR	ENEMY_ROT_LEFT	= VGet(0.0f, -1.6f, 0.0f);				//エネミーの回転値

	const float WALL_X_START = -1565.0f;
	const float WALL_X_END = -1450.0f;
	const float WALL_Z_START = 1650.0f;
	const float WALL_Z_END = 1760.0f;
}