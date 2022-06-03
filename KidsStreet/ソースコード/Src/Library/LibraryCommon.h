//LibraryCommon.h
//�v���W�F�N�g�S�̂ŋ��ʂɎg������

#pragma once
#include "DxLib.h"
enum VOID_TYPE
{
	VOID_INIT,
	VOID_LOAD,
	VOID_SET,
	VOID_STEP,
	VOID_UPDATE,
	VOID_HIT,
	VOID_DRAW,
	VOID_DELETE,
	VOID_FIN
};

//�K�v�ɉ����ĕύX
//�����蔻������I�u�W�F�N�g�̎�ސ�
enum COL_CHECK_LIST
{
	COL_NONE = -1,

	COL_CHECK_PLAYER,
	COL_CHECK_CAR,
	COL_CHECK_BOSS,
	COL_CHECK_ITEM,
	COL_CHECK_KID,
	COL_CHECK_MAX
};

//�����蔻��`�F�b�N�{�b�N�X
enum COL_CHECK_BOX {
	CHECK_BOX_NONE,		//�����������������Ȃ�
	CHECK_BOX_OVER,		//�����蔻����ɂ���Ƃ��ɒm�点��
	CHECK_BOX_HIT		//�����蔻��ɐG�ꂽ���ɒm�点��
};

//�I�u�W�F�N�g���g�̓����蔻����
enum OBJECT_TYPE {
	OBJECT_INIT,	//���������
	OBJECT_PAWN,	//���I�I�u�W�F�N�g
	OBJECT_STATIC,	//�ÓI�I�u�W�F�N�g
	OBJECT_DYNAMIC	//��Ԃɂ���Ă͒ʂ�Ȃ�
};

//�`�F�b�N�{�b�N�X��NONE�ȊO�̑Ώە�����������ʂ�
struct COLLISION_UNREAL_TYPE {
	COL_CHECK_BOX pawn_;
	COL_CHECK_BOX static_;
	COL_CHECK_BOX dynamic_;
};

//�����蔻��̌`��I��
enum COLLISION_SHAPE_TYPE {
	SHAPE_CUBE,
	SHAPE_SPHERE
};

//�����蔻��̃f�[�^
struct COL_DATA
{
	VECTOR	pos_;							//�ʒu���
	VECTOR	cubeRad_;						//���̓����蔻��
	float	sphereRad_;						//���̓����蔻��
	bool	useFlg_;						//�g�p�t���O�A���ꂪtrue�Ȃ画�肪�s����
	bool	hitFlg_;						//���T�t���O���܂���A���茋�ʂ��i�[
	int		colNum_;						//������g���Ċe�I�u�W�F�N�g�͎����̏����m�F����
	COL_CHECK_LIST			myList_;		//�����̃I�u�W�F�N�g���X�g�^�C�v�i�[�A��������-1�Ȃ̂ŋC��t����
	COL_CHECK_LIST			list_[COL_CHECK_MAX];	//�����蔻�肪���������ꍇ�ɐ擪���珇�ɑ���̃^�C�v���i�[
	COLLISION_UNREAL_TYPE	type_;			//�Q�Ƒ���Ƃ̓����蔻�肪�Ƃ�K�v������̂��i�[�A�^���`�F�b�N�{�b�N�X��p���Ă���
	OBJECT_TYPE				object_;		//�I�u�W�F�N�g���g�������
	COLLISION_SHAPE_TYPE	shapeCol_;		//�����蔻��̌`���i�[

	COL_DATA()
	{
		pos_ = { 0.0f };
		cubeRad_ = { 0.0f };
		sphereRad_ = 0.0f;
		useFlg_ = false;
		hitFlg_ = false;
		colNum_ = 0;
		myList_ = COL_NONE;
		for (int listNum = 0; listNum < COL_CHECK_MAX; listNum++)
			list_[listNum] = COL_NONE;
		type_.pawn_ = CHECK_BOX_NONE;
		type_.static_ = CHECK_BOX_NONE;
		type_.dynamic_ = CHECK_BOX_NONE;
		object_ = OBJECT_INIT;
		shapeCol_ = SHAPE_CUBE;
	}
};

//2D�̈ʒu���W�֌W�Ɏg����x�N�^�[
struct VECTOR2
{
	float x;
	float y;
};

namespace
{
	// ��`�֘A
	const VECTOR DEFAULT_SCALE = { 1.0f, 1.0f, 1.0f };	// �ʏ�X�P�[���̓I�[��1�Ȃ̂�
}
