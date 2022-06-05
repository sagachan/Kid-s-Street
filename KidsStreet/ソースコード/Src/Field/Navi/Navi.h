//Navi.h
//Navi�V�[��

#pragma once

#include "../../Library/Animation/Model/model.h"

//Navi�N���X
class CNavi : public CModel
{
private:
	enum NAVI_TYPE
	{
		NAVI_WALL,
		NAVI_HOUSE,
		NAVI_END
	};
public:
	CNavi();
	~CNavi();

	void Load();		//�ǂݍ���
	void Set();			//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Step();		//���t���[���Ăԏ���
	void Draw();		//�`��

private:
	void UpdateNaviRot();
	void CheckNaviType();

private:
	int type_;							//�i�r�^�C�v���i�[
};