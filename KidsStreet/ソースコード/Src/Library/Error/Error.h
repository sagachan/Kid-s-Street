//指定システムエラー摘出プログラム
#pragma once

class CError {
public:
	//Managerクラスのテンプレート関数、MinimizeCall関数の呼び出しが失敗したときに通る
	//ここを通る場合は基底ポインタ配列に新しく作られたクラスがnewされていない可能性が高い
	static void MinimizeVoidError();				
};