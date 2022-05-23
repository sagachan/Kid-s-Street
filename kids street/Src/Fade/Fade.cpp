//Fade.cpp
//�t�F�[�h�N���X

#include "Fade.h"
//#include "DxLib.h"
//#include "../Common.h"
//
////�t�F�[�h�֘A
//namespace
//{
//	int BLEND_MAX_PARAM = 255;	//�u�����h�̍ő�p�����[�^
//	int BLEND_MIN_PARAM = 0;	//�u�����h�̍ŏ��p�����[�^
//}
//
////�����o�ϐ��̐錾�A������
//int	 CFade::blend_param_ = 0;
//bool CFade::start_flg_ = false;
//bool CFade::end_flg_ = false;
//CFade::FADE_TYPE CFade::type_;
//CFade::Color CFade::color_;
//
//
////�X�e�b�v
//void CFade::StepFade()
//{
//	//�t�F�[�h�C���E�t�F�[�h�A�E�g���I�����Ă���Ȃ�
//	if (end_flg_)
//		return;	//�I��
//
//	//�t�F�[�h�̃^�C�v�ɂ���ď�����U�蕪����
//	switch (type_)
//	{
//	//�t�F�[�h�C������
//	case FADE_IN:
//		StepFadeIn();
//		break;
//	//�t�F�[�h�A�E�g����
//	case FADE_OUT:
//		StepFadeOut();
//		break;
//	}
//}
//
//
////�`��
//void CFade::DrawFade()
//{
//	//���Z�u�����h��ݒ�i��ʂ𖾂邭������A�Â�������j
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend_param_);
//
//	//�l�p�`��`��
//	DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(color_.r, color_.g, color_.b), true);
//
//	//���̕`��Ώۂɉe�����o�Ȃ��悤��
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, blend_param_);
//}
//
//
////�t�F�[�h�C��������i��ʂ��i�X�����Ȃ��Ȃ�j
//void CFade::StepFadeIn()
//{
//	//�J�n�t���O�������Ă��Ȃ��Ȃ�I��
//	if (start_flg_ == false)
//		return;
//
//	//�u�����h�p�����[�^���ő�l�ɂȂ�܂Łi��ʂ������Ȃ��Ȃ�܂Łj
//	if (blend_param_ < BLEND_MAX_PARAM)
//		blend_param_++;	//�p�����[�^�����Z
//
//	//��ʂ������Ȃ��Ȃ�����
//	if (blend_param_ >= BLEND_MAX_PARAM)
//	{
//		blend_param_ = BLEND_MAX_PARAM;	//�p�����[�^���ő�l�ɂ���i�ő�l�𒴂��Ă���ꍇ�j
//		start_flg_ = false;
//		end_flg_ = true;
//	}
//}
//
//
////�t�F�[�h�A�E�g������i��ʂ��i�X������悤�ɂȂ�j
//void CFade::StepFadeOut()
//{
//	//�J�n�t���O�������Ă��Ȃ��Ȃ�I��
//	if (start_flg_ == false)
//		return;
//
//	//�u�����h�p�����[�^���ŏ��l�ɂȂ�܂Łi��ʂ�������悤�ɂȂ�܂Łj
//	if (blend_param_ > BLEND_MIN_PARAM)
//		blend_param_--;	//�p�����[�^�����Z
//
//	//��ʂ��^���ÂɂȂ�����
//	if (blend_param_ <= BLEND_MIN_PARAM)
//	{
//		blend_param_ = BLEND_MIN_PARAM;	//�p�����[�^���ŏ��l�ɂ���i�ŏ��l��������Ă���ꍇ�j
//		start_flg_ = false;
//		end_flg_ = true;
//	}
//}
//
//
////�t�F�[�h�̊J�n�����i�����ɂ���āA�t�F�[�h�̎�ނƐF��ς�����j
//void CFade::StartFade(FADE_TYPE type, FADE_COLOR_KIND color_kind)
//{
//	//�t�F�[�h�C���Ȃ�
//	if (type == FADE_IN)
//	{
//		blend_param_ = BLEND_MIN_PARAM;
//		type_ = FADE_IN;
//	}
//	//�t�F�[�h�A�E�g�Ȃ�
//	else if (type == FADE_OUT)
//	{
//		blend_param_ = BLEND_MAX_PARAM;
//		type_ = FADE_OUT;
//	}
//
//	//�t�F�[�h�̐F�̐ݒ�
//	switch (color_kind)
//	{
//	//��
//	case FADE_COLOR_BLACK:
//		color_.r = 0;
//		color_.g = 0;
//		color_.b = 0;
//		break;
//	//��
//	case FADE_COLOR_WHITE:
//		color_.r = 255;
//		color_.g = 255;
//		color_.b = 255;
//		break;
//	//��
//	case FADE_COLOR_RED:
//		color_.r = 255;
//		color_.g = 0;
//		color_.b = 0;
//		break;
//	//��
//	case FADE_COLOR_GREEN:
//		color_.r = 0;
//		color_.g = 255;
//		color_.b = 0;
//		break;
//	//��
//	case FADE_COLOR_BLUE:
//		color_.r = 0;
//		color_.g = 0;
//		color_.b = 255;
//		break;
//	}
//
//	start_flg_ = true;	//�J�n�t���O�𗧂Ă�
//	end_flg_ = false;	//�I���t���O��܂�
//}