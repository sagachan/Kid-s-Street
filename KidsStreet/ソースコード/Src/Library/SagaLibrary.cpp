

#include "SagaLibrary.h"
#include "Error/Error.h"

CSagaLibrary* CSagaLibrary::instance_ = nullptr;

//オーバーライドしたアイテムの構造体の中身をnum番目まで回して参照、タイプによって処理を分ける
template <class Base>void CSagaLibrary::MinimizeCall(Base* base[], int maxNum, VOID_TYPE type)
{
	//-------------ここでやりたいこと----------------
	//  毎回for文を書いて関数を呼ばないといけないものはもうまとめて呼べるように関数作ってしまおう
	// ---------------------------------------------- 

	for (int kind = 0; kind < maxNum; kind++) {
		switch (type) {
		case VOID_INIT:		base[kind]->Init();		break;
		case VOID_LOAD:		base[kind]->Load();		break;
		case VOID_SET:		base[kind]->Set();		break;
		case VOID_STEP:		base[kind]->Step();		break;
		case VOID_UPDATE:	base[kind]->Update();	break;
		case VOID_DRAW:		base[kind]->Draw();		break;
		case VOID_DELETE:	base[kind]->Delete();	break;
		case VOID_FIN:		base[kind]->Fin();		break;

			//どれにも属さない場合
		default:
			CError::MinimizeVoidError();
			break;
		}
	}
}

//オーバーライドしたアイテムの構造体の中身をnum番目まで回して参照、タイプによって処理を分ける
template <class Base>void CSagaLibrary::MinimizePointCall(Base* base[], int maxNum, VOID_TYPE type)
{
	for (int kind = 0; kind < maxNum; kind++) {
		switch (type) {
		case VOID_INIT:	base[kind]->Init(); break;
		case VOID_LOAD:	base[kind]->Load(); break;
		case VOID_SET:	base[kind]->Set();	break;
		case VOID_STEP:	base[kind]->Step(); break;
		case VOID_DRAW:	base[kind]->Draw(); break;
		case VOID_FIN:	base[kind]->Fin();	break;

			//どれにも属さない場合
		default:
			CError::MinimizeVoidError();
			break;
		}
	}
}