

#include "SagaLibrary.h"
#include "Error/Error.h"

CSagaLibrary* CSagaLibrary::instance_ = nullptr;

//�I�[�o�[���C�h�����A�C�e���̍\���̂̒��g��num�Ԗڂ܂ŉ񂵂ĎQ�ƁA�^�C�v�ɂ���ď����𕪂���
template <class Base>void CSagaLibrary::MinimizeCall(Base* base[], int maxNum, VOID_TYPE type)
{
	//-------------�����ł�肽������----------------
	//  ����for���������Ċ֐����Ă΂Ȃ��Ƃ����Ȃ����̂͂����܂Ƃ߂ČĂׂ�悤�Ɋ֐�����Ă��܂���
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

			//�ǂ�ɂ������Ȃ��ꍇ
		default:
			CError::MinimizeVoidError();
			break;
		}
	}
}

//�I�[�o�[���C�h�����A�C�e���̍\���̂̒��g��num�Ԗڂ܂ŉ񂵂ĎQ�ƁA�^�C�v�ɂ���ď����𕪂���
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

			//�ǂ�ɂ������Ȃ��ꍇ
		default:
			CError::MinimizeVoidError();
			break;
		}
	}
}