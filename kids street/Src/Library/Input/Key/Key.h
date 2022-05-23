#pragma once

#include "../InputBase.h"

const int KEY_BUF_LEN = 256;

class CKey : public CInputBase
{
private:
	CKey() {};

	//	インスタンス
	static CKey* m_key;

	//現在フレームのキー情報
	char currentKeyBuf[KEY_BUF_LEN];

	//前フレームのキー情報
	char preKeyBuf[KEY_BUF_LEN];
public:

	static void CreateInstance() { if (!m_key)m_key = new CKey; }
	static CKey* GetInstance() { return m_key; }
	static void DeleteInstance() { if (m_key)delete m_key; m_key = nullptr; }

	//今押されたか
	bool IsPush(int key_code);

	//単純に押されたか
	bool IsDown(int key_code);

	//押し続けられているか
	bool IsKeep(int key_code);

	//いま離されたか
	bool IsRelease(int key_code);

	void Init();
	void Step();

	~CKey() {};

};