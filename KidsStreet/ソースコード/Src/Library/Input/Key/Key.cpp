#include "Key.h"
#include "DxLib.h"

/*		static 宣言		*/

CKey* CKey::m_key;


//今押されたか
bool CKey::IsPush(int key_code)
{
	//前フレで押されてない かつ 現フレで押されている
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
		return true;

	//押されてないので false
	return false;
}

//単純に押されたか
bool CKey::IsDown(int key_code)
{
	//前フレでおされている かつ 現フレで押されている
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
		return true;

	return false;
}

//押し続けられているか
bool CKey::IsKeep(int key_code)
{
	//前フレで押されていた かつ 現フレで押されていない
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
		return true;

	return false;
}

//いま離されたか
bool CKey::IsRelease(int key_code)
{
	//現フレで押されている（前フレの状態は関係なし）
	if (currentKeyBuf[key_code] == 1)
		return true;

	return false;
}

void CKey::Init()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}
}

void CKey::Step()
{
	//前フレームのキー情報変数に記録しておく
	for (int index = 0; index < KEY_BUF_LEN; index++)
		preKeyBuf[index] = currentKeyBuf[index];

	//現在のキー情報を取得
	GetHitKeyStateAll(currentKeyBuf);
}