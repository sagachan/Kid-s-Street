//指定システムエラー摘出プログラム
#include "DxLib.h"

class CError {
public:
	
	static void ErrorManager();				//エラーチェック管理関数

	static void EnemyError();				//エネミー関係のエラーチェック
	static void PlayerError();
	static void VoidError();				//Managerクラスのテンプレート関数、MinimizeCall関数の呼び出しが失敗したときに通る
};