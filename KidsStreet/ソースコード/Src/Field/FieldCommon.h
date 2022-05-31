//�t�B�[���h�֌W�ŋ��ʂɎg���\���̂������
#pragma once
#include "Dxlib.h"

//�}�b�v���
struct MapInfo
{
	int handle;						//�摜�n���h��
	int col_handle;					//�����蔻��p���f���n���h��
	VECTOR pos;						//���W

	MapInfo()
		:handle(0)
		,col_handle(0)
		,pos({0.0f}){}
};

struct InterInfo					//�����_���\����
{
	bool	front;					//�O�ɐi�߂邩�ǂ���
	bool	back;					//��
	bool	right;					//�E
	bool	left;					//��
};



namespace 
{
	const int		FRONT = 0, BACK = 1, RIGHT = 2, LEFT = 3;		//�����_�Ƃ��Ă̊p�x�𐔒l�Ƃ��Ĉ����ꍇ�Ɏg��
	const int		INTER_MAX_NUM = 17;								//�����_�̐�
	const int		INTER_BONE_MAX_NUM = 34;						//�����_�{�[���̍ő�l
	const int		INTER_DIR_NUM = 4;								//�����_�̋Ȃ���p�̕�
	const int		INTER_BW = 2;									//�����_�ԍ��̔z��m�F�p
	const int		POLE_BONE_START = 2;							//�|�[���̍����̃{�[���ԍ�
	const int		POLE_BONE_END = 3;									//�|�[���̐�[�̃{�[���ԍ�
}
