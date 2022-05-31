//GatherItem.h
//�A�C�e���̑�{�̊��N���X
//�A�C�e���^�C�v���쐬����Ƃ��Ɏg��
//��:Gather
#pragma once
#include "DxLib.h"

class CGatherItem
{
public:
	CGatherItem();
	virtual ~CGatherItem();

public:
	virtual void Init(VECTOR pos) = 0;	//������
	virtual void Load(const char* file_path) = 0;		//�ǂݍ���
	virtual void Step() = 0;							//�X�e�b�v
	virtual void Draw() = 0;							//�`��
	virtual void Delete() = 0;							//�폜
	virtual void Fin() = 0;								//�㏈��

	//�Z�b�^�[
	void SetPos(VECTOR pos) { itemPos_ = pos; }	//���W�ݒ�

	//�Q�b�^�[
	VECTOR GetPos() { return itemPos_; }
	

protected:
	VECTOR itemPos_;
};