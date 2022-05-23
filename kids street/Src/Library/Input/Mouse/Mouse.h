#pragma once

#include "../InputBase.h"

const int MOUSE_BUF_LEN = 3;

class CMouse : public CInputBase
{
private:

	//	インスタンス
	static CMouse* m_mouse;

	CMouse() {};

	//現在のフレームのパッドボタン情報
	char m_current_mouse_buf[MOUSE_BUF_LEN];

	//前フレームのパッドのボタン情報
	char m_pre_mouse_buf[MOUSE_BUF_LEN];

	//	座標
	float m_posX, m_posY;

public:
	~CMouse() {};

	static void CreateInstance() { if (!m_mouse)m_mouse = new CMouse; }
	static CMouse* GetInstance() { return m_mouse; }
	static void DeleteInstance() { if (m_mouse)delete m_mouse; m_mouse = nullptr; }

	//今押されたか
	bool IsPush(int mouse_code);

	//単純に押されたか
	bool IsDown(int mouse_code);

	//押し続けられているか
	bool IsKeep(int mouse_code);

	//いま離されたか
	bool IsRelease(int mouse_code);

	//	マウス座標取得
	void GetMousePos(float& x, float& y) { x = m_posX; y = m_posY; }

	//	マウス座標セット
	void SetMousePos(float x, float y) { m_posX = x; m_posY = y; }

	void Init();
	void Step();

};