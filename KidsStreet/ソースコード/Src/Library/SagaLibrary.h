//�֗��֐��N���X
#include "LibraryCommon.h"

#pragma once

class CSagaLibrary {
public:
	CSagaLibrary(){}
	~CSagaLibrary() {}

public:
	//Manager�N���X�̃e���v���[�g�֐�
	//�e���v�������Ƃ��ē���Ă����̂͊��N���X�̃|�C���^�z��̂�
	//�I�[�o�[���C�h�����A�C�e���̍\���̂̒��g��num�Ԗڂ܂ŉ񂵂ĎQ�ƁA�^�C�v�ɂ���ď����𕪂���
	template <class Base>void MinimizeCall(Base* base[], int maxNum, VOID_TYPE type);

	//�I�[�o�[���C�h�����A�C�e���̍\���̂̒��g��num�Ԗڂ܂ŉ񂵂ĎQ�ƁA�^�C�v�ɂ���ď����𕪂���
	template <class Base>void MinimizePointCall(Base* base[], int maxNum, VOID_TYPE type);

public:
	//�C���X�^���X����
	static void CreateInstance() { if (!instance_) instance_ = new CSagaLibrary; }
	//�C���X�^���X�擾
	static CSagaLibrary* GetInstance() { return instance_; }
	//�C���X�^���X�폜
	static void DeleteInstance() { if (instance_) delete instance_; instance_ = nullptr; }


private:
	static CSagaLibrary* instance_;	//�C���X�^���X
};