#pragma once

#include "InputBase.h"

//入力クラス
class CInput
{
public:

	//入力機器の種類
	enum INPUT_KIND
	{
		INPUT_KIND_KEY,
		INPUT_KIND_MOUSE,
		INPUT_KIND_PAD,

		INPUT_KIND_NUM,
	};

private:

	//	インスタンス
	static CInput* m_input;

	//	入力機器
	CInputBase* m_inputKind[INPUT_KIND_NUM];

	/*CInput() {};*/
public:

	//	インスタンス取得
	static CInput* GetInstance();

	//	インスタンス削除
	void DeleteInstance();

	//	今押されたか
	bool IsPush(INPUT_KIND input_kind, int key_code);

	//	単純に押されているか
	bool IsDown(INPUT_KIND input_kind, int key_code);

	//	押し続けられているか
	bool IsKeep(INPUT_KIND input_kind, int key_code);

	//	今はなされているか
	bool IsRelease(INPUT_KIND input_kind, int key_code);

	//============================================
	//	パッド関連
	//============================================

	//パッドのトリガー値
	float GetTriggerValue(PAD_TRIGGER trigger);

	//パッドのスティック値
	float GetStickValue(PAD_STICK stick);

	//============================================
	//	マウス関連
	//============================================

	//	マウス座標取得
	void GetMousePos(float& x, float& y);

	//	マウス座標セット
	void SetMousePos(float x, float y);

	void Init();
	void Step();
	static void Fin();

	~CInput() {};

public:
	//	コンフィグ関連

	//	コンフィグに登録してある動作の入力情報
	bool InputConf();

};