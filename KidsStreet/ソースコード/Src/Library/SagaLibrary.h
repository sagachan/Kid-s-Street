//便利関数クラス
#include "LibraryCommon.h"

#pragma once

class CSagaLibrary {
public:
	CSagaLibrary(){}
	~CSagaLibrary() {}

public:
	//Managerクラスのテンプレート関数
	//テンプレ引数として入れていいのは基底クラスのポインタ配列のみ
	//オーバーライドしたアイテムの構造体の中身をnum番目まで回して参照、タイプによって処理を分ける
	template <class Base>void MinimizeCall(Base* base[], int maxNum, VOID_TYPE type);

	//オーバーライドしたアイテムの構造体の中身をnum番目まで回して参照、タイプによって処理を分ける
	template <class Base>void MinimizePointCall(Base* base[], int maxNum, VOID_TYPE type);

public:
	//インスタンス生成
	static void CreateInstance() { if (!instance_) instance_ = new CSagaLibrary; }
	//インスタンス取得
	static CSagaLibrary* GetInstance() { return instance_; }
	//インスタンス削除
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }


private:
	static CSagaLibrary* instance_;	//インスタンス
};