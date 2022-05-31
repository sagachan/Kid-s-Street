#pragma once


#include "DxLib.h"

enum ITEM_KIND
{
	ITEM_INIT = -1,

	ERASER,
	PENCIL,
	RULER,
	GLOVE,
	ITEM_MAX_KIND
};

enum ITEM_ID
{
	ITEM_ID_NONE = -1,

	ITEM_ID_BOX,
	ITEM_ID_ERASER,
	ITEM_ID_PENCIL,
	ITEM_ID_RULER,
	ITEM_ID_GLOVE,
	ITEM_ID_MAX
};



namespace
{
	const int		END_TIME = 210;				//�g�p�J�n����Ă���g�p�I���܂ł̎���

	const int		MAX_ERASER = 3;			//�����S���̍ő�l
	const int		MAX_PENCIL = 15;			//���M�̍ő�l
	const int		MAX_RULER = 5;
	const int		MAX_GLOVE = 1;
	const int		MAX_ITEM_NUM = MAX_ERASER + MAX_PENCIL + MAX_RULER+MAX_GLOVE;		//�A�C�e���̍��v�l
	const int		ERASER_DMG = 15;			//�����S���̃_���[�W��
	const int		PENCIL_DMG = 5;
	const int		RULER_DMG = 10;
	const int		GLOVE_DMG = 10;
	
	const float		ITEM_GATHER_AREA = 6.0f;	//�v���C���[���A�C�e�����Ƃ����ƔF�߂�G���A
	const float		ITEM_SCALE_F = 2.0f;		//�����Ă���A�C�e���̊g�k
	const float		ITEM_UI_Y = 600.0f;
	const float		ITEM_UI_ERASER = 20.0f;
	const float		ITEM_UI_PENCIL = 150.0f;
	const float		ITEM_UI_RULER = 280.0f;
	const float		ITEM_UI_GLOVE = 410.0f;

	const float		ITEM_UI_BW = 130.0f;		//��{�I�ȃA�C�e����UI�̋�����

	const VECTOR	ERASER_POS = VGet(-580.0f, 5.0f, 300.0f);
	const VECTOR	PENCIL_POS = VGet(-150.0f, 5.0f, 1075.0f);
	const VECTOR	RULER_POS = VGet(-640.0f, 5.0f, 1100.0f);
	const VECTOR	GLOVE_POS = VGet(860.0f, 5.0f, 1560.0f);
	const VECTOR	ITEM_SCALE = VGet(ITEM_SCALE_F, ITEM_SCALE_F, ITEM_SCALE_F);


}