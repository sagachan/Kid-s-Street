#include "Pad.h"

#include "DxLib.h"

//インスタンスの実体宣言
CPad* CPad::pad_ = nullptr;

//コンストラクタ
CPad::CPad()
	:current_button_buf_()
	, pre_button_buf_()
	, current_trigger_buf_()
	, pre_trigger_buf_()
	, stick_buf_()
{
}

//デストラクタ
CPad::~CPad()
{
}

//初期化
void CPad::Init()
{
	//-----パッド情報初期化-----//
	//ボタン
	for (int button_index = 0; button_index < PAD_BUTTON_LEN; button_index++)
	{
		current_button_buf_[button_index] = '\0';
		pre_button_buf_[button_index] = '\0';
	}

	//トリガー
	for (int trigger_index = 0; trigger_index < TRIGGER_MAX; trigger_index++)
	{
		current_trigger_buf_[trigger_index] = '\0';
		pre_trigger_buf_[trigger_index] = '\0';
	}

	//スティック
	for (int stick_index = 0; stick_index < STICK_MAX; stick_index++)
	{
		stick_buf_[stick_index] = '\0';
	}
}

//ステップ
void CPad::Step()
{
	//-----パッド情報ステップ-----//
	XINPUT_STATE input_pad;

	//前フレームのボタン情報を記録しておく
	for (int button_index = 0; button_index < PAD_BUTTON_LEN; button_index++)
	{
		pre_button_buf_[button_index] = current_button_buf_[button_index];
	}

	//前フレームのトリガー情報を記録しておく
	for (int trigger_index = 0; trigger_index < TRIGGER_MAX; trigger_index++)
	{
		pre_trigger_buf_[trigger_index] = current_trigger_buf_[trigger_index];
	}

	//ゲームパッドの入力状態を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &input_pad);


	//入力情報を各メンバ変数に移す

	//ボタン
	for (int button_index = 0; button_index < PAD_BUTTON_LEN; button_index++)
	{
		current_button_buf_[button_index] = input_pad.Buttons[button_index];
	}
	
	//左右のトリガー
	//unsigned char型のサイズ分で割ることで、「0.0f～1.0f」の値を代入できる
	current_trigger_buf_[LEFT_TRIGGER] = (float)input_pad.LeftTrigger / UCHAR_MAX;
	current_trigger_buf_[RIGHT_TRIGGER] = (float)input_pad.RightTrigger / UCHAR_MAX;

	//左右のスティック
	//short型のサイズ分で割ることで、「-1.0f～1.0f」の値を代入できる
	stick_buf_[LEFT_STICK_X] = (float)input_pad.ThumbLX / SHRT_MAX;
	stick_buf_[LEFT_STICK_Y] = (float)input_pad.ThumbLY / SHRT_MAX;
	stick_buf_[RIGHT_STICK_X] = (float)input_pad.ThumbRX / SHRT_MAX;
	stick_buf_[RIGHT_STICK_Y] = (float)input_pad.ThumbRY / SHRT_MAX;
}


//今押されたか
bool CPad::IsPush(int button_code)
{
	//前フレで押されていない　かつ　現フレで押されている
	if (pre_button_buf_[button_code] == 0 && current_button_buf_[button_code] == 1)
		return true;

	return false;
}

//単純に押されたか
bool CPad::IsDown(int button_code)
{
	//現フレで押されている（前フレの状態は関係ない）
	if (current_button_buf_[button_code] == 1)
		return true;

	return false;
}

//押し続けられているか
bool CPad::IsKeep(int button_code)
{
	//前フレで押されている　かつ　現フレで押されている
	if (pre_button_buf_[button_code] == 1 && current_button_buf_[button_code] == 1)
		return true;

	return false;
}

//いま離されたか
bool CPad::IsRelease(int button_code)
{
	//前フレで押されている　かつ　現フレで押されていない
	if (pre_button_buf_[button_code] == 1 && current_button_buf_[button_code] == 0)
		return true;

	return false;
}

//トリガー値の取得
//※０に近づくほど弱い押し込み、１に近づくほど強い押し込み
float CPad::GetTriggerValue(PAD_TRIGGER trigger_kind)
{
	return current_trigger_buf_[trigger_kind];
}

//スティック値の取得
//※「－１以上０未満」なら左、または下
//　「０より大きく１以下」なら右、または上に傾けている
float CPad::GetStickValue(PAD_STICK stick_kind)
{
	return stick_buf_[stick_kind];
}