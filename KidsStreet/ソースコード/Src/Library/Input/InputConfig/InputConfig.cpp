#include "InputConfig.h"
#include "../Input.h"

#include "DxLib.h"

CInputConfig* CInputConfig::m_Instance;

namespace {

	//キーボード
	const int KEY_INPUT[CInputConfig::KEY_LEN] = {
		KEY_INPUT_A,KEY_INPUT_B,
		KEY_INPUT_C,KEY_INPUT_D,
		KEY_INPUT_E,KEY_INPUT_F,
		KEY_INPUT_G,KEY_INPUT_H,
		KEY_INPUT_I,KEY_INPUT_J,
		KEY_INPUT_K,KEY_INPUT_L,
		KEY_INPUT_M,KEY_INPUT_N,
		KEY_INPUT_O,KEY_INPUT_P,
		KEY_INPUT_Q,KEY_INPUT_R,
		KEY_INPUT_S,KEY_INPUT_T,
		KEY_INPUT_U,KEY_INPUT_V,
		KEY_INPUT_W,KEY_INPUT_X,
		KEY_INPUT_Y,KEY_INPUT_Z,
		KEY_INPUT_0,KEY_INPUT_1,
		KEY_INPUT_2,KEY_INPUT_3,
		KEY_INPUT_4,KEY_INPUT_5,
		KEY_INPUT_6,KEY_INPUT_7,
		KEY_INPUT_8,KEY_INPUT_9,
		KEY_INPUT_LSHIFT,KEY_INPUT_LCONTROL,
		KEY_INPUT_RETURN,KEY_INPUT_SPACE,
	};

	//パッド
	const int PAD_INPUT[CInputConfig::PAD_LEN] = {
		XINPUT_BUTTON_A, XINPUT_BUTTON_B,
		XINPUT_BUTTON_X, XINPUT_BUTTON_Y,
		XINPUT_BUTTON_LEFT_SHOULDER,
		XINPUT_BUTTON_RIGHT_SHOULDER,
		LEFT_TRIGGER, RIGHT_TRIGGER
	};

	//マウス
	const int MOUSE_INPUT[CInputConfig::MOUSE_LEN] = {
		MOUSE_INPUT_LEFT,
		MOUSE_INPUT_RIGHT,
		MOUSE_INPUT_MIDDLE,
	};

	//初期座標
	const float KEY_CONF_LEFT_KEY_POS_X = 459.0f;
	const float KEY_CONF_RIGHT_KEY_POS_X = 879.0f;
	const float KEY_CONF_TOP_POS_Y = 273.0f;
}

//==================================
//	初期化処理
//==================================
void CInputConfig::InputConfigInit()
{
	//マイナス1に
	memset(&Input_bit, -1, sizeof(InputBit) * INPUT_NUM);

	//	初期ボタン設定
	Input_bit[CONF_ATTACK].PadBit				= XINPUT_BUTTON_Y;
	Input_bit[CONF_ATTACK].MouseBit				= MOUSE_INPUT_RIGHT;
	Input_bit[CONF_ROLLING].PadBit				= XINPUT_BUTTON_A;
	Input_bit[CONF_ROLLING].KeyBit				= KEY_INPUT_LSHIFT;
	Input_bit[CONF_RUN].PadBit					= XINPUT_BUTTON_RIGHT_SHOULDER;
	Input_bit[CONF_RUN].KeyBit					= KEY_INPUT_SPACE;
	Input_bit[CONF_ITEM].PadBit					= XINPUT_BUTTON_X;
	Input_bit[CONF_ITEM].KeyBit					= KEY_INPUT_T;
	Input_bit[CONF_ITEM_CHANGE].PadBit			= XINPUT_BUTTON_LEFT_SHOULDER;
	Input_bit[CONF_ITEM_CHANGE].KeyBit			= KEY_INPUT_G;
	Input_bit[CONF_DECISION].PadBit				= XINPUT_BUTTON_B;
	Input_bit[CONF_DECISION].KeyBit				= KEY_INPUT_RETURN;
	Input_bit[CONF_WEAPON_CHANGE].TrigerBit		= LEFT_TRIGGER;
	Input_bit[CONF_WEAPON_CHANGE].KeyBit		= KEY_INPUT_1;
	Input_bit[CONF_SPECIAL_TECHNIQUE].TrigerBit	= RIGHT_TRIGGER;
	Input_bit[CONF_SPECIAL_TECHNIQUE].KeyBit	= KEY_INPUT_2;

	//ハンドル
	KeyConfHandle = new int[KEY_LEN];
	PadConfHandle = new int[PAD_LEN];
	MouseConfHandle = new int[MOUSE_LEN];

	////ロード
	LoadDivGraph("Data/InputConfig/Key.png", 40, 10, 4, 64, 64, KeyConfHandle);
	LoadDivGraph("Data/InputConfig/Pad.png", 8, 4, 2, 64, 64, PadConfHandle);
	LoadDivGraph("Data/InputConfig/Mouse.png", 3, 3, 1, 64, 64, MouseConfHandle);

	NoneConfHandle = LoadGraph("Data/InputConfig/None.png");
}

//==================================
//	変更処理
//==================================
void CInputConfig::InputConfigStep(const INPUT_CONF& conf_kind, const bool& IsKey)
{
	if (!IsInputCheck)return;

	//	入力情報
	CInput* input = CInput::GetInstance();

	//キーボードかマウス
	if (IsKey) {

		//初め
		if (!IsStepCheck) {

			//	キーボード
			if (input->IsPush(CInput::INPUT_KIND_KEY, Input_bit[CONF_DECISION].KeyBit)) {
				IsStepCheck = true;
				return;
			}

			//	マウス
			if (input->IsPush(CInput::INPUT_KIND_MOUSE, Input_bit[CONF_DECISION].MouseBit)) {
				IsStepCheck = true;
				return;
			}
		}

		//キーボードの入力数分回る
		for (int index = 0; index < KEY_LEN; index++) {

			//キーボードの何かが押された
			if(input->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT[index])) {
				Input_bit[conf_kind].KeyBit = -1;
				Input_bit[conf_kind].MouseBit = -1;

				//同じキーを使ってないか調べる
				for (int input_index = 0; input_index < INPUT_NUM; input_index++) {
					if (Input_bit[input_index].KeyBit == KEY_INPUT[index]) {
						Input_bit[input_index].KeyBit = -1;
					}
				}
				
				/*		ここに追加		*/


				IsInputCheck = false;
				IsStepCheck = false;
				break;
			}
		}

		//マウスの入力数分回す
		for (int index = 0; index < MOUSE_LEN; index++) {

			//マウスの何かが押された
			if (input->IsPush(CInput::INPUT_KIND_MOUSE, MOUSE_INPUT[index])) {
				Input_bit[conf_kind].KeyBit = -1;
				Input_bit[conf_kind].MouseBit = -1;

				//同じボタンを使ってないか調べる
				for (int input_index = 0; input_index < INPUT_NUM; input_index++) {
					if (Input_bit[input_index].MouseBit == MOUSE_INPUT[index]) {
						Input_bit[input_index].MouseBit = -1;
					}
				}

				/*		ここに追加		*/


				IsInputCheck = false;
				IsStepCheck = false;
				break;
			}
		}
	}
	//パッド
	else {
		
		//初め
		if (!IsStepCheck) {

			if (input->IsPush(CInput::INPUT_KIND_PAD, Input_bit[CONF_DECISION].PadBit)) {
				IsStepCheck = true;
				return;
			}

			if (input->GetTriggerValue(static_cast<PAD_TRIGGER>(Input_bit[CONF_DECISION].TrigerBit)) >= 0.8f) {
				IsStepCheck = true;
				return;
			}
		}

		//パッドの入力数分回る
		for (int index = 0; index < PAD_LEN; index++) {

			//トリガー
			if (index >= 6) {

				if (input->GetTriggerValue(static_cast<PAD_TRIGGER>(PAD_INPUT[index])) >= 0.8f) {
					Input_bit[conf_kind].PadBit = -1;
					Input_bit[conf_kind].TrigerBit = -1;

					//同じキーを使ってないか調べる
					for (int input_index = 0; input_index < INPUT_NUM; input_index++) {
						if (Input_bit[input_index].TrigerBit == PAD_INPUT[index]) {
							Input_bit[input_index].TrigerBit = -1;
						}
					}

					Input_bit[conf_kind].TrigerBit = PAD_INPUT[index];

					IsInputCheck = false;
					IsStepCheck = false;
					break;
				}
			}
			//パッド
			else {

				//パッドの何かが押された
				if (input->IsPush(CInput::INPUT_KIND_PAD, PAD_INPUT[index])) {
					Input_bit[conf_kind].PadBit = -1;
					Input_bit[conf_kind].TrigerBit = -1;

					//同じボタンを使ってないか調べる
					for (int input_index = 0; input_index < INPUT_NUM; input_index++) {
						if (Input_bit[input_index].PadBit == PAD_INPUT[index]) {
							Input_bit[input_index].PadBit = -1;
						}
					}

					/*		ここに追加		*/


					IsInputCheck = false;
					IsStepCheck = false;
					break;
				}
			}
		}
	}
}

//==================================
//　描画処理
//==================================
void CInputConfig::InputConfigDraw()
{
	//key
	for (int input_index = 0; input_index < INPUT_NUM; input_index++) {

		VECTOR pos;

		//座標設定
		if (input_index < 5) {
			pos.y = KEY_CONF_TOP_POS_Y + (input_index * 63);
			pos.x = KEY_CONF_LEFT_KEY_POS_X;
		}
		else {
			pos.y = KEY_CONF_TOP_POS_Y + ((input_index - 5) * 63);
			pos.x = KEY_CONF_RIGHT_KEY_POS_X;
		}

		//キー
		if (Input_bit[input_index].KeyBit != -1) {
			
			int handle_index = 0;

			//キーボードの入力数分回る
			for (int index = 0; index < KEY_LEN; index++) {

				if (Input_bit[input_index].KeyBit == KEY_INPUT[index]) {
					handle_index = index;
					break;
				}
			}
				
			DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), 1.0f, .0f, KeyConfHandle[handle_index], true);
		}
		//マウス
		else
		{
			int handle_index = 0;

			//キーボードの入力数分回る
			for (int index = 0; index < MOUSE_LEN; index++) {

				if (Input_bit[input_index].MouseBit == MOUSE_INPUT[index]) {
					handle_index = index;
					break;
				}
			}

			//どちらも設定してなかったら
			if (Input_bit[input_index].MouseBit == -1 && Input_bit[input_index].KeyBit == -1) {
				DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), 1.0f, .0f, NoneConfHandle, true);
			}
			else
				DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), 1.0f, .0f, MouseConfHandle[handle_index], true);
		}
	}

	//pad
	for (int input_index = 0; input_index < INPUT_NUM; input_index++) {

		VECTOR pos;

		//座標設定
		if (input_index < 5) {
			pos.y = KEY_CONF_TOP_POS_Y + (input_index * 63);
			pos.x = KEY_CONF_LEFT_KEY_POS_X;
		}
		else {
			pos.y = KEY_CONF_TOP_POS_Y + ((input_index - 5) * 63);
			pos.x = KEY_CONF_RIGHT_KEY_POS_X;
		}

		pos.x += 88;
	
		int handle_index = 0;

		//キーボードの入力数分回る
		for (int index = 0; index < PAD_LEN; index++) {

			if (Input_bit[input_index].PadBit == PAD_INPUT[index]) {
				handle_index = index;
				break;
			}

			if (Input_bit[input_index].TrigerBit == PAD_INPUT[index]) {
				handle_index = index;
				break;
			}
		}

		//どちらも設定してなかったら
		if (Input_bit[input_index].PadBit == -1 && Input_bit[input_index].TrigerBit == -1) {
			DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), 1.0f, .0f, NoneConfHandle, true);
		}
		else
			DrawRotaGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), 0.8f, .0f, PadConfHandle[handle_index], true);
	}
}

//==================================
//	今押されたか
//==================================
bool CInputConfig::InputPush(const INPUT_CONF& kind)
{
	CInput* input = CInput::GetInstance();

	//キーボード
	if (Input_bit[kind].KeyBit != -1) 
	{
		if (input->IsPush(CInput::INPUT_KIND_KEY, Input_bit[kind].KeyBit))
			return true;
	}

	//パッド
	if (Input_bit[kind].PadBit != -1) 
	{
		if (input->IsPush(CInput::INPUT_KIND_PAD, Input_bit[kind].PadBit))
			return true;
	}
	
	//マウス
	if (Input_bit[kind].MouseBit != -1) 
	{
		if (input->IsPush(CInput::INPUT_KIND_MOUSE, Input_bit[kind].MouseBit))
			return true;
	}

	return false;
}

//==================================
//	単純に押されているか
//==================================
bool CInputConfig::InputDown(const INPUT_CONF& kind)
{
	CInput* input = CInput::GetInstance();

	//キーボード
	if (Input_bit[kind].KeyBit != -1)
	{
		if (input->IsDown(CInput::INPUT_KIND_KEY, Input_bit[kind].KeyBit))
			return true;
	}

	//パッド
	if (Input_bit[kind].PadBit != -1)
	{
		if (input->IsDown(CInput::INPUT_KIND_PAD, Input_bit[kind].PadBit))
			return true;
	}

	//マウス
	if (Input_bit[kind].MouseBit != -1)
	{
		if (input->IsDown(CInput::INPUT_KIND_MOUSE, Input_bit[kind].MouseBit))
			return true;
	}

	return false;
}

//==================================
//	押され続けているか
//==================================
bool CInputConfig::InputKeep(const INPUT_CONF& kind)
{
	CInput* input = CInput::GetInstance();

	//キーボード
	if (Input_bit[kind].KeyBit != -1)
	{
		if (input->IsKeep(CInput::INPUT_KIND_KEY, Input_bit[kind].KeyBit))
			return true;
	}

	//パッド
	if (Input_bit[kind].PadBit != -1)
	{
		if (input->IsKeep(CInput::INPUT_KIND_PAD, Input_bit[kind].PadBit))
			return true;
	}

	//マウス
	if (Input_bit[kind].MouseBit != -1)
	{
		if (input->IsKeep(CInput::INPUT_KIND_MOUSE, Input_bit[kind].MouseBit))
			return true;
	}

	return false;
}

//==================================
//	押され続けているか
//==================================
bool CInputConfig::InputRelease(const INPUT_CONF& kind)
{
	CInput* input = CInput::GetInstance();

	//キーボード
	if (Input_bit[kind].KeyBit != -1)
	{
		if (input->IsRelease(CInput::INPUT_KIND_KEY, Input_bit[kind].KeyBit))
			return true;
	}

	//パッド
	if (Input_bit[kind].PadBit != -1)
	{
		if (input->IsRelease(CInput::INPUT_KIND_PAD, Input_bit[kind].PadBit))
			return true;
	}

	//マウス
	if (Input_bit[kind].MouseBit != -1)
	{
		if (input->IsRelease(CInput::INPUT_KIND_MOUSE, Input_bit[kind].MouseBit))
			return true;
	}

	return false;
}

bool CInputConfig::InputTriger(const INPUT_CONF& kind)
{
	if (Input_bit[kind].TrigerBit == -1)return false;

	float trig;

	trig = CInput::GetInstance()->GetTriggerValue(static_cast<PAD_TRIGGER>(Input_bit[kind].TrigerBit));

	if (trig > 0.9f) {
		return true;
	}

	return false;
}

//=================================
//	インスタンスを取得
//=================================
CInputConfig* CInputConfig::GetInstance()
{
	if (!m_Instance)
		m_Instance = new CInputConfig;

	return m_Instance;
}

//================================
//	インスタンス削除
//================================
void CInputConfig::Delete()
{
	for (int index = 0; index < KEY_LEN; index++) {
		DeleteGraph(KeyConfHandle[index]);
	}

	for (int index = 0; index < PAD_LEN; index++) {
		DeleteGraph(PadConfHandle[index]);
	}

	for (int index = 0; index < MOUSE_LEN; index++) {
		DeleteGraph(MouseConfHandle[index]);
	}

	delete [] KeyConfHandle;
	delete [] PadConfHandle;
	delete [] MouseConfHandle;

	KeyConfHandle = nullptr;
	PadConfHandle = nullptr;
	MouseConfHandle = nullptr;

	delete m_Instance;
	m_Instance = nullptr;
}