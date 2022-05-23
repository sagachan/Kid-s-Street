#pragma once

#include "../InputBase.h"

//	入力コンフィグクラス
class CInputConfig
{
public:

	static const int KEY_LEN = 40;
	static const int MOUSE_LEN = 3;
	static const int PAD_LEN = 8;

private:

	//シングルトン
	static CInputConfig* m_Instance;

public:

	static CInputConfig* GetInstance();

private:

	int  *KeyConfHandle;	//キー画像
	int	 *PadConfHandle;	//パッド画像
	int  *MouseConfHandle;	//マウス画像
	int  NoneConfHandle;	//なにもないとき
	bool IsInputCheck;	//入力が終わったか
	bool IsStepCheck;	//開始用

	//	入力ビット情報構造体
	struct InputBit
	{
		int KeyBit;		//キーボード
		int PadBit;		//パッド
		int MouseBit;	//マウス
		int TrigerBit;	//パッドトリガー
	};

	//	入力情報
	InputBit Input_bit[INPUT_NUM];

	
private:
	CInputConfig()
		:Input_bit{0 },
		IsInputCheck(false),
		IsStepCheck(false)
	{};

public:
	//	各動作の入力
	//	引数	：入力した動作
	bool InputPush(const INPUT_CONF& kind);
	bool InputDown(const INPUT_CONF& kind);
	bool InputKeep(const INPUT_CONF& kind);
	bool InputRelease(const INPUT_CONF& kind);
	bool InputTriger(const INPUT_CONF& kind);

public:

	//	インプットコンフィグ初期化
	void InputConfigInit();

	//	入力キー、ボタン変更
	//	引数	：conf_kind	変更するキーまたはボタンの動作の種類
	//		：IsKey		変更する物がキーかどうか ( true = キー : false = パッド )
	void InputConfigStep(const INPUT_CONF& conf_kind, const bool& IsKey);

	//	現在登録されてあるキー、ボタンを描画（キーコンフィグ設定中のみ）
	void InputConfigDraw();

	//	削除
	void Delete();

	void SetInputCheck(const bool& check) { IsInputCheck = check; }
	bool GetInputCheck() { return IsInputCheck; }
};