//Fade.cpp
//フェードクラス

#include "Fade.h"
//#include "DxLib.h"
//#include "../Common.h"
//
////フェード関連
//namespace
//{
//	int BLEND_MAX_PARAM = 255;	//ブレンドの最大パラメータ
//	int BLEND_MIN_PARAM = 0;	//ブレンドの最小パラメータ
//}
//
////メンバ変数の宣言、初期化
//int	 CFade::blend_param_ = 0;
//bool CFade::start_flg_ = false;
//bool CFade::end_flg_ = false;
//CFade::FADE_TYPE CFade::type_;
//CFade::Color CFade::color_;
//
//
////ステップ
//void CFade::StepFade()
//{
//	//フェードイン・フェードアウトが終了しているなら
//	if (end_flg_)
//		return;	//終了
//
//	//フェードのタイプによって処理を振り分ける
//	switch (type_)
//	{
//	//フェードイン処理
//	case FADE_IN:
//		StepFadeIn();
//		break;
//	//フェードアウト処理
//	case FADE_OUT:
//		StepFadeOut();
//		break;
//	}
//}
//
//
////描画
//void CFade::DrawFade()
//{
//	//加算ブレンドを設定（画面を明るくしたり、暗くしたり）
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend_param_);
//
//	//四角形を描画
//	DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(color_.r, color_.g, color_.b), true);
//
//	//他の描画対象に影響が出ないように
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, blend_param_);
//}
//
//
////フェードインさせる（画面が段々見えなくなる）
//void CFade::StepFadeIn()
//{
//	//開始フラグが立っていないなら終了
//	if (start_flg_ == false)
//		return;
//
//	//ブレンドパラメータが最大値になるまで（画面が見えなくなるまで）
//	if (blend_param_ < BLEND_MAX_PARAM)
//		blend_param_++;	//パラメータを加算
//
//	//画面が見えなくなったら
//	if (blend_param_ >= BLEND_MAX_PARAM)
//	{
//		blend_param_ = BLEND_MAX_PARAM;	//パラメータを最大値にする（最大値を超えている場合）
//		start_flg_ = false;
//		end_flg_ = true;
//	}
//}
//
//
////フェードアウトさせる（画面が段々見えるようになる）
//void CFade::StepFadeOut()
//{
//	//開始フラグが立っていないなら終了
//	if (start_flg_ == false)
//		return;
//
//	//ブレンドパラメータが最小値になるまで（画面が見えるようになるまで）
//	if (blend_param_ > BLEND_MIN_PARAM)
//		blend_param_--;	//パラメータを減算
//
//	//画面が真っ暗になったら
//	if (blend_param_ <= BLEND_MIN_PARAM)
//	{
//		blend_param_ = BLEND_MIN_PARAM;	//パラメータを最小値にする（最小値を下回っている場合）
//		start_flg_ = false;
//		end_flg_ = true;
//	}
//}
//
//
////フェードの開始処理（引数によって、フェードの種類と色を変えられる）
//void CFade::StartFade(FADE_TYPE type, FADE_COLOR_KIND color_kind)
//{
//	//フェードインなら
//	if (type == FADE_IN)
//	{
//		blend_param_ = BLEND_MIN_PARAM;
//		type_ = FADE_IN;
//	}
//	//フェードアウトなら
//	else if (type == FADE_OUT)
//	{
//		blend_param_ = BLEND_MAX_PARAM;
//		type_ = FADE_OUT;
//	}
//
//	//フェードの色の設定
//	switch (color_kind)
//	{
//	//黒
//	case FADE_COLOR_BLACK:
//		color_.r = 0;
//		color_.g = 0;
//		color_.b = 0;
//		break;
//	//白
//	case FADE_COLOR_WHITE:
//		color_.r = 255;
//		color_.g = 255;
//		color_.b = 255;
//		break;
//	//赤
//	case FADE_COLOR_RED:
//		color_.r = 255;
//		color_.g = 0;
//		color_.b = 0;
//		break;
//	//緑
//	case FADE_COLOR_GREEN:
//		color_.r = 0;
//		color_.g = 255;
//		color_.b = 0;
//		break;
//	//青
//	case FADE_COLOR_BLUE:
//		color_.r = 0;
//		color_.g = 0;
//		color_.b = 255;
//		break;
//	}
//
//	start_flg_ = true;	//開始フラグを立てる
//	end_flg_ = false;	//終了フラグを折る
//}