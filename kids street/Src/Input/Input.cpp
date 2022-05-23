#include "Input.h"
#include "Key/Key.h"
#include "Mouse/Mouse.h"
#include "Pad/Pad.h"

/*		static宣言		*/

CInput* CInput::m_input;	//インプット

//	インスタンス取得
CInput* CInput::GetInstance()
{
	if (!m_input)
		m_input = _NEW(CInput);

	return m_input;
}

//	インスタンス削除
void CInput::DeleteInstance()
{
	if (m_input)
		_DELETE(m_input);

	m_input = nullptr;
}


//	初期化
void CInput::Init()
{

	//入力機器情報取得
	CKey::CreateInstance();
	CMouse::CreateInstance();
	CPad::CreateInstance();
	
	m_inputKind[INPUT_KIND_KEY] = CKey::GetInstance();
	m_inputKind[INPUT_KIND_MOUSE] = CMouse::GetInstance();
	m_inputKind[INPUT_KIND_PAD] = CPad::GetInstance();
	

	//	各入力機器初期化
	for (int input_index = 0; input_index < INPUT_KIND_NUM; input_index++)
	{
		m_inputKind[input_index]->Init();
	}

	
}

//ステップ
void CInput::Step()
{
	for (int input_index = 0; input_index < INPUT_KIND_NUM; input_index++)
		m_inputKind[input_index]->Step();
}

//	今押されたか
bool CInput::IsPush(INPUT_KIND input_kind, int key_code)
{
	return m_inputKind[input_kind]->IsPush(key_code);
}

//	単純に押されているか
bool CInput::IsDown(INPUT_KIND input_kind, int key_code)
{
	return m_inputKind[input_kind]->IsDown(key_code);
}

//	押し続けられているか
bool CInput::IsKeep(INPUT_KIND input_kind, int key_code)
{
	return m_inputKind[input_kind]->IsKeep(key_code);
}

//	今はなされたか
bool CInput::IsRelease(INPUT_KIND input_kind, int key_code)
{
	return m_inputKind[input_kind]->IsRelease(key_code);
}

//	トリガー値取得
float CInput::GetTriggerValue(PAD_TRIGGER trigger)
{
	return CPad::GetInstance()->GetTriggerValue(trigger);
}

//	スティック値取得
float CInput::GetStickValue(PAD_STICK stick)
{
	return CPad::GetInstance()->GetStickValue(stick);
}

//	マウス座標取得
void CInput::GetMousePos(float &x, float &y)
{
	CMouse::GetInstance()->GetMousePos(x, y);
}

//	マウス座標セット
void CInput::SetMousePos(float x, float y)
{
	CMouse::GetInstance()->SetMousePos(x, y);
}


//後処理
void CInput::Fin()
{
	//	入力情報削除
	CKey::GetInstance()->DeleteInstance();
	CPad::GetInstance()->DeleteInstance();
	CMouse::GetInstance()->DeleteInstance();

	
}