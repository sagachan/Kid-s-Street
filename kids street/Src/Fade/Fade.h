//Fade.h
//�t�F�[�h�C���E�t�F�[�h�A�E�g

#pragma once

//�t�F�[�h�N���X�i�t�F�[�h�C����t�F�[�h�A�E�g���邽�߂̃N���X�j
//class CFade
//{
//public:
//	//�t�F�[�h�^�C�v
//	enum FADE_TYPE
//	{
//		FADE_IN,	//�t�F�[�h�C��
//		FADE_OUT,	//�t�F�[�h�A�E�g
//	};
//
//	//�t�F�[�h�̐F�̎��
//	enum FADE_COLOR_KIND
//	{
//		FADE_COLOR_BLACK,	//��
//		FADE_COLOR_WHITE,	//��
//		FADE_COLOR_RED,		//��
//		FADE_COLOR_GREEN,	//��
//		FADE_COLOR_BLUE,	//��
//	};
//
//	//�O���F�̍\����
//	struct Color
//	{
//		int r;	//��
//		int g;	//��
//		int b;	//��
//	};
//
//public:
//	static void StepFade();	//�t�F�[�h�̃X�e�b�v
//	static void DrawFade();	//�t�F�[�h�̕`��
//
//	//�t�F�[�h�̊J�n�����i�����ɂ���āA�t�F�[�h�̎�ނƐF��ς�����j
//	static void StartFade(FADE_TYPE type, FADE_COLOR_KIND color_kind);
//
//	//�t�F�[�h�C���E�t�F�[�h�A�E�g���J�n�������ǂ���
//	static bool IsFadeStart() { return start_flg_; }
//
//	//�t�F�[�h�C���E�t�F�[�h�A�E�g���I���������ǂ���
//	static bool IsFadeEnd() { return end_flg_; }
//
//private:
//	static void StepFadeIn();	//�t�F�[�h�C�����s���֐�
//	static void StepFadeOut();	//�t�F�[�h�A�E�g���s���֐�
//
//
//private:
//	static int	blend_param_;	//�u�����h�̃p�����[�^
//	static bool start_flg_;		//�J�n�t���O
//	static bool end_flg_;		//�I���t���O
//	static FADE_TYPE type_;		//�t�F�[�h�^�C�v
//	static Color	color_;		//�t�F�[�h�̐F
//};