#pragma once

#include "../InputBase.h"

//----------- XInputボタン入力定義 -----------//
/*
	 XINPUT_BUTTON_DPAD_UP			(0)		// デジタル方向ボタン上
	 XINPUT_BUTTON_DPAD_DOWN		(1)		// デジタル方向ボタン下
	 XINPUT_BUTTON_DPAD_LEFT		(2)		// デジタル方向ボタン左
	 XINPUT_BUTTON_DPAD_RIGHT		(3)		// デジタル方向ボタン右
	 XINPUT_BUTTON_START			(4)		// STARTボタン
	 XINPUT_BUTTON_BACK				(5)		// BACKボタン
	 XINPUT_BUTTON_LEFT_THUMB		(6)		// 左スティック押し込み
	 XINPUT_BUTTON_RIGHT_THUMB		(7)		// 右スティック押し込み
	 XINPUT_BUTTON_LEFT_SHOULDER	(8)		// LBボタン
	 XINPUT_BUTTON_RIGHT_SHOULDER	(9)		// RBボタン
	 XINPUT_BUTTON_A				(12)	// Aボタン
	 XINPUT_BUTTON_B				(13)	// Bボタン
	 XINPUT_BUTTON_X				(14)	// Xボタン
	 XINPUT_BUTTON_Y				(15)	// Yボタン
*/

//----------- ゲームパッドの情報を代入する構造体の内容(XINPUT_STATE構造体) -----------//
/*
	struct XINPUT_STATE
	{
		unsigned char	Buttons[ 16 ] ;	// ボタン１６個( 添字には XINPUT_BUTTON_DPAD_UP 等を使用する、
						//			0:押されていない  1:押されている )
		unsigned char	LeftTrigger ;	// 左トリガー( 0～255 )
		unsigned char	RightTrigger ;	// 右トリガー( 0～255 )
		short		ThumbLX ;	// 左スティックの横軸値( -32768 ～ 32767 )
		short		ThumbLY ;	// 左スティックの縦軸値( -32768 ～ 32767 )
		short		ThumbRX ;	// 右スティックの横軸値( -32768 ～ 32767 )
		short		ThumbRY ;	// 右スティックの縦軸値( -32768 ～ 32767 )
	} ;
*/

//パッドのボタン入力の数
const int PAD_BUTTON_LEN = 16;

//パッド入力クラス
class CPad : public CInputBase
{
public:
	CPad();		//コンストラクタ
	~CPad();	//デストラクタ

public:
	/***シングルトン***/	//パッドは１つしか要らないから
	static void CreateInstance() { if (!pad_)pad_ = new CPad; }
	static CPad* GetInstance() { return pad_; }
	static void DeleteInstance() { if (pad_)delete pad_; pad_ = nullptr; }

public:
	//初期化
	void Init() override;

	//ステップ
	void Step() override;

	//今押されたか
	bool IsPush(int button_code) override;

	//単純に押されたか
	bool IsDown(int button_code) override;

	//押し続けられているか
	bool IsKeep(int button_code) override;

	//いま離されたか
	bool IsRelease(int button_code) override;

	//トリガー値の取得（0.0f～1.0fの値を返す）
	//※０に近づくほど弱い押し込み、１に近づくほど強い押し込み
	float GetTriggerValue(PAD_TRIGGER trigger_kind);

	//スティック値の取得（-1.0f～1.0fの値を返す）
	//※「－１以上０未満」なら左、または下
	//　「０より大きく１以下」なら右、または上に傾けている
	float GetStickValue(PAD_STICK stick_kind);

private:
	//インスタンス
	static CPad* pad_;

	//現在フレームのボタン情報
	unsigned char current_button_buf_[PAD_BUTTON_LEN];

	//前フレームのボタン情報
	unsigned char pre_button_buf_[PAD_BUTTON_LEN];

	//パッドのトリガー情報
	float current_trigger_buf_[TRIGGER_MAX];
	float pre_trigger_buf_[TRIGGER_MAX];

	//パッドのスティック情報
	float stick_buf_[STICK_MAX];
};