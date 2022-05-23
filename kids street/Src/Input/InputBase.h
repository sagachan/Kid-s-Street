#pragma once

#include "../Common.h"

enum PAD_TRIGGER
{
	LEFT_TRIGGER,		//左トリガー
	RIGHT_TRIGGER,		//右トリガー

	TRIGGER_MAX,		//トリガー最大数
};

enum PAD_STICK
{
	LEFT_STICK_X,		//左スティックのX
	LEFT_STICK_Y,		//左スティックのY


	RIGHT_STICK_X,		//右スティックのX
	RIGHT_STICK_Y,		//右スティックのY

	STICK_MAX,			//スティックの最大数
};


//入力用基底クラス
class CInputBase
{
public:
	//==================================================
	//入力機器によって操作が変わるので純粋仮想関数で宣言
	//==================================================

	//今押されたか
	virtual bool IsPush(int Key_code) = 0;

	//単純に押されたか
	virtual bool IsDown(int Key_code) = 0;

	//押し続けられているか
	virtual bool IsKeep(int Key_code) = 0;

	//いま離されたか
	virtual bool IsRelease(int Key_code) = 0;

	//初期化
	virtual void Init() = 0;

	//ステップ
	virtual void Step() = 0;
};
